#include "recuperacion.h"
void Recuperacion::RecuCHGRP(int Comienzo, const char *Path, const char *Grp, const char *Usr,IUG Inf){
    JOR Nuevo;
    Nuevo.Tipo=18;
    Nuevo.Info=Inf;
    strcpy(Nuevo.Direccion,Grp);
    strcpy(Nuevo.Contenido,Usr);
    NuevoRegistro(Comienzo,Path,Nuevo);
}
void Recuperacion::RecuCHOWN(int Comienzo, const char *Path, const char *PathVirtual, const char *Usr, bool Recursivo,IUG Inf){
    JOR Nuevo;
    Nuevo.Tipo=17;
    Nuevo.Info=Inf;
    strcpy(Nuevo.Direccion,PathVirtual);
    strcpy(Nuevo.Contenido,Usr);
    Nuevo.Recursivo=Recursivo;
    NuevoRegistro(Comienzo,Path,Nuevo);
}
void Recuperacion::RecuMV(int Comienzo, const char *Path, const char *PathOrigen, const char *PathDestino,IUG Inf){
    JOR Nuevo;
    Nuevo.Tipo=16;
    Nuevo.Info=Inf;
    strcpy(Nuevo.Direccion,PathOrigen);
    strcpy(Nuevo.Contenido,PathDestino);
    NuevoRegistro(Comienzo,Path,Nuevo);
}
void Recuperacion::RecuCP(int Comienzo, const char *Path, const char *PathOrigen, const char *PathDestino,IUG Inf){
    JOR Nuevo;
    Nuevo.Tipo=15;
    Nuevo.Info=Inf;
    strcpy(Nuevo.Direccion,PathOrigen);
    strcpy(Nuevo.Contenido,PathDestino);
    NuevoRegistro(Comienzo,Path,Nuevo);
}
void Recuperacion::RecuMKDIR(int Comienzo, const char *Path, const char *PathVirtual, bool Recursivo,IUG Inf){
    JOR Nuevo;
    Nuevo.Tipo=14;
    Nuevo.Info=Inf;
    strcpy(Nuevo.Direccion,PathVirtual);
    Nuevo.Recursivo=Recursivo;
    NuevoRegistro(Comienzo,Path,Nuevo);
}
void Recuperacion::RecuREN(int Comienzo, const char *Path, const char *PathVirtual, const char *NuevoNombre,IUG Inf){
    JOR Nuevo;
    Nuevo.Tipo=13;
    Nuevo.Info=Inf;
    strcpy(Nuevo.Direccion,PathVirtual);
    strcpy(Nuevo.Contenido,NuevoNombre);
    NuevoRegistro(Comienzo,Path,Nuevo);
}
void Recuperacion::RecuEDIT(int Comienzo, const char *Path, const char *PathVirtual,const char *Cont, bool Recursivo, int Tamanio, int PosiArchivo,IUG Inf){
    JOR Nuevo;
    Nuevo.Tipo=12;
    Nuevo.Info=Inf;
    strcpy(Nuevo.Direccion,PathVirtual);
    Nuevo.TamanioArchivo=Tamanio;
    strcpy(Nuevo.Contenido,Cont);
    Nuevo.Recursivo=Recursivo;
    NuevoRegistro(Comienzo,Path,Nuevo);
}
void Recuperacion::RecuREM(int Comienzo, const char *Path, const char *PathVirtual,IUG Inf){
    JOR Nuevo;
    Nuevo.Tipo=11;
    strcpy(Nuevo.Direccion,PathVirtual);
    NuevoRegistro(Comienzo,Path,Nuevo);
    Nuevo.Info=Inf;
}
void Recuperacion::RecuMKFILE(int Comienzo, const char *Path, const char *PathVirtual, const char *Cont, bool Recursivo, int Tamanio, int PosiArchivo,IUG Inf){
    JOR Nuevo;
    Nuevo.Tipo=9;
    strcpy(Nuevo.Direccion,PathVirtual);
    Nuevo.TamanioArchivo=Tamanio;

    strcpy(Nuevo.Contenido,Cont);


    Nuevo.Recursivo=Recursivo;
    Nuevo.Info=Inf;
    NuevoRegistro(Comienzo,Path,Nuevo);
}
void Recuperacion::RecuCHMOD(int Comienzo, const char *Path, const char *PathVirtual, const char *Ugo, bool Recursivo,IUG Inf){
    JOR Nuevo;
    Nuevo.Tipo=8;
    strcpy(Nuevo.Direccion,PathVirtual);
    strcpy(Nuevo.Contenido,Ugo);
    Nuevo.Recursivo=Recursivo;
    Nuevo.Info=Inf;
    NuevoRegistro(Comienzo,Path,Nuevo);
}
void Recuperacion::RecuRMUSR(int Comienzo, const char *Path, const char *Usr,IUG Inf){
    JOR Nuevo;
    Nuevo.Tipo=7;
    strcpy(Nuevo.Contenido,Usr);
    Nuevo.Info=Inf;
    NuevoRegistro(Comienzo,Path,Nuevo);
}
void Recuperacion::RecuMKUSR(int Comienzo, const char *Path, const char *Usr, const char *Pwd, const char *Grp,IUG Inf){
    JOR Nuevo;
    Nuevo.Tipo=6;
    std::string Concatenar="";
    Concatenar=Concatenar+Usr+"|"+Pwd+"|"+Grp+"|";
    strcpy(Nuevo.Contenido,Concatenar.c_str());
    Nuevo.Info=Inf;
    NuevoRegistro(Comienzo,Path,Nuevo);
}
void Recuperacion::RecuRMGRP(int Comienzo, const char *Path,const char *Nombre,IUG Inf){
    JOR Nuevo;
    Nuevo.Tipo=5;
    strcpy(Nuevo.Contenido,Nombre);
    Nuevo.Info=Inf;
    NuevoRegistro(Comienzo,Path,Nuevo);
}
void Recuperacion::RecuMKGRP(int Comienzo, const char *Path,const char *Nombre,IUG Inf){
    JOR Nuevo;
    Nuevo.Tipo=4;
    strcpy(Nuevo.Contenido,Nombre);
    Nuevo.Info=Inf;
    NuevoRegistro(Comienzo,Path,Nuevo);
}
void Recuperacion::NuevoRegistro(int Comienzo, const char *Path, JOR Recu){

    FILE *f;
    f=fopen(Path,"r+");
    SPB Super;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Super,sizeof (Super),1,f);
    fclose(f);


    int Numero=Comienzo+int(sizeof (SPB));
    if(Numero>=Super.s_bm_inode_start)
        Numero=-1;

     if(Numero==-1){
        std::cout<<"Sin Opcion A Recuperacion"<<std::endl;
        return;
    }

    //Recu Siguiente
     f=fopen(Path,"r+");
    JOR Leido;
    //Llenar Recu
    for(int i=0;i<Super.s_inodes_count;i++){
        //Escribir Recu
        fseek(f,Numero+i*sizeof (JOR),SEEK_SET);
        fread(&Leido,sizeof (Leido),1,f);

        //Leer
        if(Leido.Tipo==-1){//Esta Vacio     
            fseek(f,Numero+i*sizeof (JOR),SEEK_SET);
            fwrite(&Recu,sizeof (Recu),1,f);
            break;
        }
    }
    fclose(f);
}
void Recuperacion::IniciarJOUR(int Comienzo, const char *Path){
    std::cout<<"Sistema De Archivos EXT3 Iniciando Journaling"<<std::endl;

    FILE *f;
    f=fopen(Path,"r+");
    SPB Super;
    //Leer El Super Bloque
    fseek(f,Comienzo,SEEK_SET);
    fread(&Super,sizeof (Super),1,f);
    //GenerarNumeroParaColocarJour
    int Numero=Comienzo+int(sizeof (SPB));
    if(Numero>=Super.s_bm_inode_start)
        Numero=-1;



    if(Numero==-1){
        std::cout<<"Sin Opcion A Recuperacion"<<std::endl;
        return;
    }

    //Recu Siguiente
    JOR Tope;
    //Llenar Recu
    for(int i=0;i<Super.s_inodes_count;i++){
        Tope.Tipo=-1;
        strcpy(Tope.Direccion,"....");
        strcpy(Tope.Contenido,"....");
        //Escribir Recu
        fseek(f,Numero+i*sizeof (JOR),SEEK_SET);
        fwrite(&Tope,sizeof (Tope),1,f);

    }
    fclose(f);
}
Recuperacion::Recuperacion()
{

}
std::queue<JOR> Recuperacion::ListaDeOperaciones(int Comienzo, const char *Path){
    FILE *f;
    f=fopen(Path,"r+");
    SPB Super;
    //Leer El Super Bloque
    fseek(f,Comienzo,SEEK_SET);
    fread(&Super,sizeof (Super),1,f);
    //IniciarPuntero
    int Puntero=Comienzo+int(sizeof (Super));
    fclose(f);

    std::queue<JOR> Cola;
    if(Puntero==-1 || Super.s_filesystem_type==0){
        std::cout<<"Sin Opcion A Recuperacion, Es Ext2 "<<std::endl;
        return Cola;
    }
    JOR Actual;
    Actual.Tipo=-1;
    f=fopen(Path,"r+");
    for (int i=0;i<Super.s_inodes_count;i++) {
        //Leer El JOR

        fseek(f,Puntero+i*sizeof (JOR),SEEK_SET);
        fread(&Actual,sizeof(Actual),1,f);
        //Meter Si Es Valido
        if(Actual.Tipo!=-1)
        {

            Cola.push(Actual);
        }

    }

    fclose(f);
    return Cola;
}
