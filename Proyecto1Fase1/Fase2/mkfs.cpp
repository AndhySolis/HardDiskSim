#include "mkfs.h"
#include "mkfile_mkdir.h"
#include "recuperacion.h"
MKFS::MKFS(int ComienzoParticion,int TamanioParticion,int TamanioStruct,std::string Direcc,int Tipo,int Ext,IUG Permiso)
{    
    this->Permiso=Permiso;
    EstructurarFormatoEXT3(ComienzoParticion,TamanioParticion,TamanioStruct,Direcc,Tipo,Ext);
}
void MKFS::EstructurarFormatoEXT3(int ComienzoParticion, int TamanioParticion, int TamanioStruct, std::string Direcc,int Tipo,int Ext){
    const char*Path =Direcc.data();
    int Cantidad=CalcularCantidad(TamanioParticion,Ext);
    int ComienzoEscritura=ComienzoParticion+TamanioStruct;
    //Ext 0 EXT2
    // Tipo=0
    Tipo=0;
    SPB Super=LlenarSuperBloque(Ext+Tipo,ComienzoEscritura,Cantidad);

    FILE *f;
    f=fopen(Path,"r+");
    fseek(f,ComienzoEscritura,SEEK_SET);
    //Escribir El Super Bloque
    fwrite(&Super,sizeof (SPB),1,f);    
    fclose(f);
    //Llenar BitmapInodo
    LlenarVacio(Super.s_bm_inode_start,Cantidad,'0',Path);
    //Llenar BitmapBloque
    LlenarVacio(Super.s_bm_block_start,Cantidad*3,'0',Path);
    //Llenar Inodo
    LlenarVacio(Super.s_inode_start,Cantidad*int(sizeof (INO)),'I',Path);
    //Llenar Bloque
    LlenarVacio(Super.s_block_start,Cantidad*3*int(sizeof (BAP)),'B',Path);
    /*fread(&r,sizeof(MBR),1,f);*/
    int PrimerInodo=InodoLibre(&Super,Path);
    int PrimerBloque=BloqueLibre(&Super,Path);
    f=fopen(Path,"r+");
    //Escribir El Primer Inodo
    fseek(f,PrimerInodo,SEEK_SET);
    INO Inodo;
    int i_uid=1;
    int i_gid=1;
    int i_size= 0;
    IniciarInodo(&Inodo,i_uid,i_gid,i_size,PrimerBloque,'0',111111);
    fwrite(&Inodo,sizeof (Inodo),1,f);
    //Escribir EL Primer Bloque
    fseek(f,PrimerBloque,SEEK_SET);
    BCA Bloque;
    IniciarBloqueCarpeta(&Bloque);
    fwrite(&Bloque,sizeof (Bloque),1,f);
    fclose(f);

    new MKFILE_MKDIR(&Super,PrimerInodo,"/users.txt",Path,"1,G,root\n1,U,root,root,123\n",false,false,Permiso);
    Recuperacion *Recu= new Recuperacion();

    if(Ext==1)//ext3
        Recu->IniciarJOUR(ComienzoEscritura,Path);
}

