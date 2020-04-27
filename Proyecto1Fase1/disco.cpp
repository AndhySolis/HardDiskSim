#include "disco.h"
#include "reports.h"
#include "ext.h"
#include "recuperacion.h"
#include "queue"
#include "Fase2/cat.h"
#include "Fase2/chmod_chown.h"
#include "Fase2/cp.h"
#include "Fase2/edit.h"
#include "Fase2/find.h"
#include "Fase2/mkfile_mkdir.h"
#include "Fase2/mkfs.h"
#include "Fase2/mv.h"
#include "Fase2/rem.h"
#include "Fase2/ren.h"
//CHOWN
void Disco::PropietarioArchivoParticion(const char *Nombre, const char *Path, int Tipo, int Perm, IUG Permiso,const char *NameUsr){
    Disco *Tempo=this;
    while (Tempo!=nullptr) {

        for (int i=0;i<Tempo->Lista.count();i++) {
            MOU Te= Lista.at(i);
            std::string NombreParti=Tempo->Apodo+std::to_string(Te.Numero);
            if(Fun->IF(NombreParti,Nombre)){
                const char* Real=Tempo->Path.data();
                int Comienzo;
                //Es Logica
                if(Te.EsLogica){
                    Comienzo=Te.Logica.part_start+int(sizeof(EBR));
                }else{
                    //TamanioStruct=int(sizeof(EBR));
                    Comienzo=Te.Particion.part_start;
                }

                //Tipo De Formato

                FILE *f;
                f=fopen(Real,"r+");
                SPB Super;
                fseek(f,Comienzo,SEEK_SET);
                fread(&Super,sizeof(Super),1,f);
                fclose(f);

                if(Super.s_magic==-1){
                    std::cout<<"Anomalias En La Particion, Cancelando Operacion"<<std::endl;
                    return;
                }
                new CHMOD_CHOWN(Super.s_first_ino,Path,Tempo->Path.data(),Perm,Tipo,Permiso,true);

                FunctionsExt *Fe= new FunctionsExt();
                if(Fe->BuscarActual(Super.s_first_ino,Path,Real)!=-1){
                    Recuperacion *Jo = new Recuperacion();
                    bool Recur=false;
                    if(Tipo==1)
                        Recur=true;
                    Jo->RecuCHOWN(Comienzo,Tempo->Path.data(),Path,NameUsr,Recur,Permiso);
                }

                //E->CambiarPropietarioNormalRecursivo(Super.s_first_ino,Path,Tempo->Path.data(),Perm,Tipo);
                return ;
            }
        }
        Tempo=Tempo->Siguiente;
    }

    std::cout<<"No Se Encontro La Particion "<<Nombre<<" Para Poder Modificar Permisos"<<std::endl;
    return ;
}
//Recovery
std::queue<JOR>  Disco::Recuperar(int Comienzo,const char *Path){
    std::cout<<"Se Esta Iniciando La Recuperacion De La Unidad"<<std::endl;
    Recuperacion *Recuva  = new Recuperacion();
    std::queue<JOR>  Cola=Recuva->ListaDeOperaciones(Comienzo,Path);
    int Longitud=Cola.size();
    std::cout<<"Se Han Detectado "<<Longitud<<" Operaciones"<<std::endl;


    return Cola;
}
std::queue<JOR> Disco::RecuperarInformacion(const char *Nombre){
    Disco *Tempo=this;
    while (Tempo!=nullptr) {

        for (int i=0;i<Tempo->Lista.count();i++) {
            MOU Te= Lista.at(i);
            std::string NombreParti=Tempo->Apodo+std::to_string(Te.Numero);
            if(Fun->IF(NombreParti,Nombre)){

                const char* Real=Tempo->Path.data();
                int Comienzo;
                int Tamanio;
                //Es Logica
                if(Te.EsLogica){
                    Comienzo=Te.Logica.part_start+int(sizeof(EBR));
                    Tamanio=Te.Logica.part_size;
                }else{
                    //TamanioStruct=int(sizeof(EBR));
                    Comienzo=Te.Particion.part_start;
                    Tamanio=Te.Particion.part_size;
                }

                //Tipo De Formato

                FILE *f;
                f=fopen(Real,"r+");
                SPB Super;
                fseek(f,Comienzo,SEEK_SET);
                fread(&Super,sizeof(Super),1,f);
                fclose(f);
                return Recuperar(Comienzo,Tempo->Path.data());

            }
        }
        Tempo=Tempo->Siguiente;
    }

    std::cout<<"No Se Encontro La Particion "<<Nombre<<" Para Poder Perder Informacion"<<std::endl;
    std::queue<JOR> Vacia;
    return Vacia;
}
//LOSS
void Disco::PerderInformacion(const char *Nombre){
    Disco *Tempo=this;
    while (Tempo!=nullptr) {

        for (int i=0;i<Tempo->Lista.count();i++) {
            MOU Te= Lista.at(i);
            std::string NombreParti=Tempo->Apodo+std::to_string(Te.Numero);
            if(Fun->IF(NombreParti,Nombre)){

                const char* Real=Tempo->Path.data();
                int Comienzo;
                int Tamanio;
                //Es Logica
                if(Te.EsLogica){
                    Comienzo=Te.Logica.part_start+int(sizeof(EBR));
                    Tamanio=Te.Logica.part_size;
                }else{
                    //TamanioStruct=int(sizeof(EBR));
                    Comienzo=Te.Particion.part_start;
                    Tamanio=Te.Particion.part_size;
                }

                //Tipo De Formato

                FILE *f;
                f=fopen(Real,"r+");
                SPB Super;
                fseek(f,Comienzo,SEEK_SET);
                fread(&Super,sizeof(Super),1,f);
                //Indicar Al Super Que Ya No Sirve
                Super.s_magic=-1;
                fseek(f,Comienzo,SEEK_SET);
                fwrite(&Super,sizeof(Super),1,f);

                fclose(f);

                FillDisk(Super.s_bm_inode_start,Super.s_block_start,'\0',Tempo->Path.data());
                std::cout<<" Se Ha Provocado Una Perdida De La Informacion, Se Necesita Recuperar "<<std::endl;
                return ;
            }
        }
        Tempo=Tempo->Siguiente;
    }

    std::cout<<"No Se Encontro La Particion "<<Nombre<<" Para Poder Perder Informacion"<<std::endl;
    return ;

}
void Disco::FillDisk(int Begin, int Size, char Character,const char *Path){
    FILE *f;
    f=fopen(Path,"r+");
    int Kilo=Size/1024;
    if(Kilo>0){
        char Buffi[1024];
        for (int i=0;i<1024;i++) {
            Buffi[i]=Character;
        }

        fseek(f,Begin,SEEK_SET);
        for(int i=0;i<Kilo;i++){

            fwrite(&Buffi,sizeof (Buffi),1,f);
        }

    }
    Size=Size-Kilo*1024;
    Begin=Begin+(Kilo*1024);
    fseek(f,Begin,SEEK_SET);
    for(int i=0;i<Size;i++){

        fwrite(&Character,sizeof (Character),1,f);
    }
    fclose(f);
}
//-
//MOV
void Disco::MoverArchivoParticion(const char *Nombre, const char *PathOrigen, const char *PathDestino, IUG Permiso){
    Disco *Tempo=this;
    while (Tempo!=nullptr) {

        for (int i=0;i<Tempo->Lista.count();i++) {
            MOU Te= Lista.at(i);
            std::string NombreParti=Tempo->Apodo+std::to_string(Te.Numero);
            if(Fun->IF(NombreParti,Nombre)){
                const char* Real=Tempo->Path.data();
                int Comienzo;
                //Es Logica
                if(Te.EsLogica){
                    Comienzo=Te.Logica.part_start+int(sizeof(EBR));
                }else{
                    //TamanioStruct=int(sizeof(EBR));
                    Comienzo=Te.Particion.part_start;
                }

                //Tipo De Formato

                FILE *f;
                f=fopen(Real,"r+");
                SPB Super;
                fseek(f,Comienzo,SEEK_SET);
                fread(&Super,sizeof(Super),1,f);
                fclose(f);
                if(Super.s_magic==-1){
                    std::cout<<"Anomalias En La Particion, Cancelando Operacion"<<std::endl;
                    return;
                }
                new MV(Permiso,&Super,Super.s_first_ino,PathOrigen,Tempo->Path.data(),PathDestino);

                FunctionsExt *Fe= new FunctionsExt();
                if(Fe->BuscarActual(Super.s_first_ino,PathDestino,Real)!=-1){
                    Recuperacion *Jo = new Recuperacion();
                    Jo->RecuMV(Comienzo,Real,PathOrigen,PathDestino,Permiso);
                }

                return ;
            }
        }
        Tempo=Tempo->Siguiente;
    }

    std::cout<<"No Se Encontro La Particion "<<Nombre<<" Para Poder MOVER"<<std::endl;
    return ;
}
//CP
void Disco::CopiarArchivoParticion(const char *Nombre, const char *PathOrigen, const char *PathDestino, IUG Permiso){
    Disco *Tempo=this;
    while (Tempo!=nullptr) {

        for (int i=0;i<Tempo->Lista.count();i++) {
            MOU Te= Lista.at(i);
            std::string NombreParti=Tempo->Apodo+std::to_string(Te.Numero);
            if(Fun->IF(NombreParti,Nombre)){
                //EXT *E = new EXT(Permiso);
                const char* Real=Tempo->Path.data();
                int Comienzo;
                //Es Logica
                if(Te.EsLogica){
                    Comienzo=Te.Logica.part_start+int(sizeof(EBR));
                }else{
                    //TamanioStruct=int(sizeof(EBR));
                    Comienzo=Te.Particion.part_start;
                }

                //Tipo De Formato

                FILE *f;
                f=fopen(Real,"r+");
                SPB Super;
                fseek(f,Comienzo,SEEK_SET);
                fread(&Super,sizeof(Super),1,f);
                fclose(f);
                if(Super.s_magic==-1){
                    std::cout<<"Anomalias En La Particion, Cancelando Operacion"<<std::endl;
                    return;
                }
                new CP(&Super,Super.s_first_ino,PathOrigen,Tempo->Path.data(),PathDestino,Permiso);
                //E->CopiarCarpetaArchivo(&Super,Super.s_first_ino,PathOrigen,Tempo->Path.data(),PathDestino);
                FunctionsExt *Fe= new FunctionsExt();
                if(Fe->BuscarActual(Super.s_first_ino,PathDestino,Real)!=-1){
                    Recuperacion *Jo = new Recuperacion();
                    Jo->RecuCP(Comienzo,Real,PathOrigen,PathDestino,Permiso);
                }

                return ;
            }
        }
        Tempo=Tempo->Siguiente;
    }

    std::cout<<"No Se Encontro La Particion "<<Nombre<<" Para Poder COPIAR "<<std::endl;
    return ;
}
//FIND
void Disco::BuscarArchivoParticion(const char *Nombre, const char *PathBase, const char *NombreBusqueda, IUG Permiso){
    Disco *Tempo=this;
    while (Tempo!=nullptr) {

        for (int i=0;i<Tempo->Lista.count();i++) {
            MOU Te= Lista.at(i);
            std::string NombreParti=Tempo->Apodo+std::to_string(Te.Numero);
            if(Fun->IF(NombreParti,Nombre)){
                //EXT *E = new EXT(Permiso);
                const char* Real=Tempo->Path.data();
                int Comienzo;
                //Es Logica
                if(Te.EsLogica){
                    Comienzo=Te.Logica.part_start+int(sizeof(EBR));
                }else{
                    //TamanioStruct=int(sizeof(EBR));
                    Comienzo=Te.Particion.part_start;
                }

                //Tipo De Formato

                FILE *f;
                f=fopen(Real,"r+");
                SPB Super;
                fseek(f,Comienzo,SEEK_SET);
                fread(&Super,sizeof(Super),1,f);
                fclose(f);

                if(Super.s_magic==-1){
                    std::cout<<"Anomalias En La Particion, Cancelando Operacion"<<std::endl;
                    return;
                }
                //E->FIND(Super.s_first_ino,PathBase,Tempo->Path.data());
                new FIND(Super.s_first_ino,PathBase,Tempo->Path.data(),Permiso);

                return ;
            }
        }
        Tempo=Tempo->Siguiente;
    }

    std::cout<<"No Se Encontro La Particion "<<Nombre<<" Para Poder FIND "<<std::endl;
    return ;
}
//REN
void Disco::RenombrarArchivoParticion(const char *Nombre, const char *NuevoNombre, const char *Path, IUG Permiso){
    Disco *Tempo=this;
    while (Tempo!=nullptr) {

        for (int i=0;i<Tempo->Lista.count();i++) {
            MOU Te= Lista.at(i);
            std::string NombreParti=Tempo->Apodo+std::to_string(Te.Numero);
            if(Fun->IF(NombreParti,Nombre)){
                //EXT *E = new EXT(Permiso);
                const char* Real=Tempo->Path.data();
                int Comienzo;
                //Es Logica
                if(Te.EsLogica){
                    Comienzo=Te.Logica.part_start+int(sizeof(EBR));
                }else{
                    //TamanioStruct=int(sizeof(EBR));
                    Comienzo=Te.Particion.part_start;
                }

                //Tipo De Formato

                FILE *f;
                f=fopen(Real,"r+");
                SPB Super;
                fseek(f,Comienzo,SEEK_SET);
                fread(&Super,sizeof(Super),1,f);
                fclose(f);

                if(Super.s_magic==-1){
                    std::cout<<"Anomalias En La Particion, Cancelando Operacion"<<std::endl;
                    return;
                }
                //E->CambiarNombre(Super.s_first_ino,Path,Tempo->Path.data(),NuevoNombre);
                new REN(Super.s_first_ino,Path,Tempo->Path.data(),NuevoNombre,Permiso);


                    Recuperacion *Jo = new Recuperacion();
                    Jo->RecuREN(Comienzo,Real,Path,NuevoNombre,Permiso);


                return ;
            }
        }
        Tempo=Tempo->Siguiente;
    }

    std::cout<<"No Se Encontro La Particion "<<Nombre<<" Para Poder CAMBIAR Nombre"<<std::endl;
    return ;
}
//CHMOD
void Disco::PermisoArchivoParticion(const char *Nombre,const char *Path,int Tipo,int Perm,IUG Permiso,const char *NameUsr){
    Disco *Tempo=this;
    while (Tempo!=nullptr) {

        for (int i=0;i<Tempo->Lista.count();i++) {
            MOU Te= Lista.at(i);
            std::string NombreParti=Tempo->Apodo+std::to_string(Te.Numero);
            if(Fun->IF(NombreParti,Nombre)){
                //EXT *E = new EXT(Permiso);
                const char* Real=Tempo->Path.data();
                int Comienzo;
                //Es Logica
                if(Te.EsLogica){
                    Comienzo=Te.Logica.part_start+int(sizeof(EBR));
                }else{
                    //TamanioStruct=int(sizeof(EBR));
                    Comienzo=Te.Particion.part_start;
                }

                //Tipo De Formato

                FILE *f;
                f=fopen(Real,"r+");
                SPB Super;
                fseek(f,Comienzo,SEEK_SET);
                fread(&Super,sizeof(Super),1,f);
                fclose(f);



                if(Super.s_magic==-1){
                    std::cout<<"Anomalias En La Particion, Cancelando Operacion"<<std::endl;
                    return;
                }
                //E->CambiarPermisosNormalRecursivo(Super.s_first_ino,Path,Tempo->Path.data(),Tipo,Perm);
                new CHMOD_CHOWN(Super.s_first_ino,Path,Tempo->Path.data(),Tipo,Perm,Permiso,false);
                FunctionsExt *Fe= new FunctionsExt();

                if(Fe->BuscarActual(Super.s_first_ino,Path,Real)!=-1){
                    Recuperacion *Jo = new Recuperacion();
                    bool Recur=false;
                    if(Tipo==1)
                        Recur=true;
                    Jo->RecuCHMOD(Comienzo,Tempo->Path.data(),Path,std::to_string(Perm).data(),Recur,Permiso);
                }

                return ;
            }
        }
        Tempo=Tempo->Siguiente;
    }

    std::cout<<"No Se Encontro La Particion "<<Nombre<<" Para Poder Modificar Permisos"<<std::endl;
    return ;
}
//REM
void Disco::BorrarArchivoParticion(const char *Nombre, const char *Path,IUG Permiso){
    Disco *Tempo=this;
    while (Tempo!=nullptr) {

        for (int i=0;i<Tempo->Lista.count();i++) {
            MOU Te= Lista.at(i);
            std::string NombreParti=Tempo->Apodo+std::to_string(Te.Numero);
            if(Fun->IF(NombreParti,Nombre)){
                //EXT *E = new EXT(Permiso);
                const char* Real=Tempo->Path.data();
                int Comienzo;
                //Es Logica
                if(Te.EsLogica){
                    Comienzo=Te.Logica.part_start+int(sizeof(EBR));
                }else{
                    //TamanioStruct=int(sizeof(EBR));
                    Comienzo=Te.Particion.part_start;
                }

                //Tipo De Formato

                FILE *f;
                f=fopen(Real,"r+");
                SPB Super;
                fseek(f,Comienzo,SEEK_SET);
                fread(&Super,sizeof(Super),1,f);
                fclose(f);
                //std::cout<<Super.s_block_start<<std::endl;


                if(Super.s_magic==-1){
                    std::cout<<"Anomalias En La Particion, Cancelando Operacion"<<std::endl;
                    return;
                }
                //E->EliminarArchivoCarpeta(&Super,Super.s_first_ino,Path,Tempo->Path.data());
                new REM(&Super,Super.s_first_ino,Path,Tempo->Path.data(),Permiso);

                Recuperacion *Jo = new Recuperacion();
                Jo->RecuREM(Comienzo,Real,Path,Permiso);

                return ;
            }
        }
        Tempo=Tempo->Siguiente;
    }

    std::cout<<"No Se Encontro La Particion "<<Nombre<<" Para Poder Leerla"<<std::endl;
    return ;
}
//CAT
std::string Disco::LeerArchivoParticion(const char *Nombre, const char *Path,IUG Permiso){
    Disco *Tempo=this;
    while (Tempo!=nullptr) {

        for (int i=0;i<Tempo->Lista.count();i++) {
            MOU Te= Lista.at(i);
            std::string NombreParti=Tempo->Apodo+std::to_string(Te.Numero);
            if(Fun->IF(NombreParti,Nombre)){
                //EXT *E = new EXT(Permiso);
                const char* Real=Tempo->Path.data();
                int Comienzo;
                //Es Logica
                if(Te.EsLogica){
                    Comienzo=Te.Logica.part_start+int(sizeof(EBR));
                }else{
                    //TamanioStruct=int(sizeof(EBR));
                    Comienzo=Te.Particion.part_start;
                }

                //Tipo De Formato

                FILE *f;
                f=fopen(Real,"r+");
                SPB Super;
                fseek(f,Comienzo,SEEK_SET);
                fread(&Super,sizeof(Super),1,f);
                fclose(f);

                if(Super.s_magic==-1){
                    std::cout<<"Anomalias En La Particion, Cancelando Operacion"<<std::endl;
                    return "";
                }
                //std::cout<<Super.s_block_start<<std::endl;
                //std::string Lectura=E->LeerArchivo(Super.s_first_ino,Tempo->Path.data(),Path);
                CAT *Archivo=new CAT(Permiso);;

                return Archivo->LeerArchivo(Super.s_first_ino,Tempo->Path.data(),Path);
            }
        }
        Tempo=Tempo->Siguiente;
    }

    std::cout<<"No Se Encontro La Particion "<<Nombre<<" Para Poder Leerla"<<std::endl;
    return "";
}
//EDIT
void Disco::ExpandirArchivoParticion(const char *Nombre, const char *Path,  std::string Contenido,IUG Permiso){
    Disco *Tempo=this;
    while (Tempo!=nullptr) {

        for (int i=0;i<Tempo->Lista.count();i++) {
            MOU Te= Lista.at(i);
            std::string NombreParti=Tempo->Apodo+std::to_string(Te.Numero);
            if(Fun->IF(NombreParti,Nombre)){
                //EXT *E = new EXT(Permiso);
                const char* Real=Tempo->Path.data();
                int Comienzo;
                //Es Logica
                if(Te.EsLogica){
                    Comienzo=Te.Logica.part_start+int(sizeof(EBR));
                }else{
                    //TamanioStruct=int(sizeof(EBR));
                    Comienzo=Te.Particion.part_start;
                }

                //Tipo De Formato

                FILE *f;
                f=fopen(Real,"r+");
                SPB Super;
                fseek(f,Comienzo,SEEK_SET);
                fread(&Super,sizeof(Super),1,f);
                fclose(f);

                if(Super.s_magic==-1){
                    std::cout<<"Anomalias En La Particion, Cancelando Operacion"<<std::endl;
                    return;
                }
                //std::cout<<Super.s_block_start<<std::endl;
                new EDIT(&Super,Super.s_first_ino,Path,Real,Contenido,Permiso);
                //E->ExpandirArchivo(&Super,Super.s_first_ino,Path,Real,Contenido);

                if(Contenido.length()>128)
                Contenido=Contenido.substr(0,128);

                FunctionsExt *Fe= new FunctionsExt();
                if(Fe->BuscarActual(Super.s_first_ino,Path,Real)!=-1){
                    Recuperacion *Jo = new Recuperacion();
                    Jo->RecuEDIT(Comienzo,Real,Path,Contenido.data(),false,0,0,Permiso);
                }

                return;
            }
        }
        Tempo=Tempo->Siguiente;
    }

    std::cout<<"No Se Encontro La Particion "<<Nombre<<" Para Crear Carpeta"<<std::endl;
}

//MKFILE
void Disco::CrearArchivoParticion(const char *Nombre, const char *Path, char Padre, std::string Contenido,IUG Permiso){
    Disco *Tempo=this;
    while (Tempo!=nullptr) {

        for (int i=0;i<Tempo->Lista.count();i++) {
            MOU Te= Lista.at(i);
            std::string NombreParti=Tempo->Apodo+std::to_string(Te.Numero);
            if(Fun->IF(NombreParti,Nombre)){
                //EXT *E = new EXT(Permiso);
                const char* Real=Tempo->Path.data();
                int Comienzo;
                //Es Logica
                if(Te.EsLogica){
                    Comienzo=Te.Logica.part_start+int(sizeof(EBR));
                }else{
                    //TamanioStruct=int(sizeof(EBR));
                    Comienzo=Te.Particion.part_start;
                }

                //Tipo De Formato

                FILE *f;
                f=fopen(Real,"r+");
                SPB Super;
                fseek(f,Comienzo,SEEK_SET);
                fread(&Super,sizeof(Super),1,f);
                fclose(f);

                if(Super.s_magic==-1){
                    std::cout<<"Anomalias En La Particion, Cancelando Operacion"<<std::endl;
                    return;
                }
                //std::cout<<Super.s_block_start<<std::endl;
                if(Padre=='0'){
                    new MKFILE_MKDIR(&Super,Super.s_first_ino,Path,Real,Contenido,false,false,Permiso);
                    //E->CrearArchivoSimple(&Super,Super.s_first_ino,Path,Real,Contenido);
                }else{
                    new MKFILE_MKDIR(&Super,Super.s_first_ino,Path,Real,Contenido,false,true,Permiso);
                    //E->CrearArchivoCompleto(&Super,Super.s_first_ino,Path,Real,Contenido);
                }

                FunctionsExt *Fe= new FunctionsExt();
                if(Fe->BuscarActual(Super.s_first_ino,Path,Real)!=-1){
                    Recuperacion *Jo = new Recuperacion();
                    if(Contenido.length()>128)
                    Contenido=Contenido.substr(0,128);
                    Jo->RecuMKFILE(Comienzo,Real,Path,Contenido.data(),false,0,0,Permiso);
                }

                return;
            }
        }
        Tempo=Tempo->Siguiente;
    }

    std::cout<<"No Se Encontro La Particion "<<Nombre<<" Para Crear Carpeta"<<std::endl;
}
//MKDIR
void Disco::CrearCarpetaParticion(const char *Nombre, const char *Path, char Padre,IUG Permiso){
    Disco *Tempo=this;
    while (Tempo!=nullptr) {

        for (int i=0;i<Tempo->Lista.count();i++) {
            MOU Te= Lista.at(i);
            std::string NombreParti=Tempo->Apodo+std::to_string(Te.Numero);
            if(Fun->IF(NombreParti,Nombre)){
                //EXT *E = new EXT(Permiso);
                const char* Real=Tempo->Path.data();
                int Comienzo;
                //Es Logica
                if(Te.EsLogica){
                    Comienzo=Te.Logica.part_start+int(sizeof(EBR));
                }else{
                    //TamanioStruct=int(sizeof(EBR));
                    Comienzo=Te.Particion.part_start;
                }

                //Tipo De Formato

                FILE *f;
                f=fopen(Real,"r+");
                SPB Super;
                fseek(f,Comienzo,SEEK_SET);
                fread(&Super,sizeof(Super),1,f);
                fclose(f);

                if(Super.s_magic==-1){
                    std::cout<<"Anomalias En La Particion, Cancelando Operacion"<<std::endl;
                    return;
                }
                //std::cout<<Super.s_block_start<<std::endl;
                bool R=false;
                if(Padre=='0'){
                    //E->CrearCarpetaSimple(&Super,Super.s_first_ino,Path,Real);
                    new MKFILE_MKDIR(&Super,Super.s_first_ino,Path,Real,"",true,false,Permiso);
                }else{
                    R=true;
                    //E->CrearCarpetaCompleto(&Super,Super.s_first_ino,Path,Real);
                    new MKFILE_MKDIR(&Super,Super.s_first_ino,Path,Real,"",true,true,Permiso);
                }



                FunctionsExt *Fe= new FunctionsExt();
                if(Fe->BuscarActual(Super.s_first_ino,Path,Real)!=-1){
                    Recuperacion *Jo = new Recuperacion();
                    Jo->RecuMKDIR(Comienzo,Real,Path,R,Permiso);                                        
                }



                return;
            }
        }
        Tempo=Tempo->Siguiente;
    }

    std::cout<<"No Se Encontro La Particion "<<Nombre<<" Para Crear Carpeta"<<std::endl;

}
//MKFS
void Disco::FormatearParticion(const char *Nombre,IUG Permiso,int Tipo,int Ext){
    Disco *Tempo=this;
    while (Tempo!=nullptr) {

        for (int i=0;i<Tempo->Lista.count();i++) {
            MOU Te= Lista.at(i);
            std::string NombreParti=Tempo->Apodo+std::to_string(Te.Numero);
            if(Fun->IF(NombreParti,Nombre)){
                //EXT *E = new EXT(Permiso);
                std::string Path=Tempo->Path;
                int TamanioStruct;
                int TamanioParticion;
                int Comienzo;
                //Es Logica
                if(Te.EsLogica){
                    TamanioStruct=int(sizeof(EBR));
                    TamanioParticion=Te.Logica.part_size;
                    Comienzo=Te.Logica.part_start;
                }else{
                    //TamanioStruct=int(sizeof(EBR));
                    TamanioStruct=0;
                    TamanioParticion=Te.Particion.part_size;
                    Comienzo=Te.Particion.part_start;
                }

                //Tipo De Formato
                new MKFS(Comienzo,TamanioParticion,TamanioStruct,Path,Tipo,Ext,Permiso);
                //E->EstructurarFormatoEXT3(Comienzo,TamanioParticion,TamanioStruct,Path,Tipo);
                std::string Form="Ext2";
                if(Ext==1)
                    Form="Ext3";
                std::cout<<"Se Formateo La Particion "<<Nombre<<" Con El Formato "<<Form<<" Del Disco Ubicado En "<<Tempo->Path<<std::endl;


                return;
            }
        }
        Tempo=Tempo->Siguiente;
    }

    std::cout<<"No Se Encontro La Particion Para Formatear "<<Nombre<<std::endl;
}

//Contar
void Disco::Contar(const char *Nombre,bool Montar){
    Disco *Tempo=this;


    while (Tempo!=nullptr) {

        for (int i=0;i<Tempo->Lista.count();i++) {
            MOU Te= Lista.at(i);
            std::string NombreParti=Tempo->Apodo+std::to_string(Te.Numero);
            if(Fun->IF(NombreParti,Nombre)){
                //EXT *E = new EXT(Permiso);
                const char* Real=Tempo->Path.data();
                int Comienzo;
                //Es Logica
                if(Te.EsLogica){
                    Comienzo=Te.Logica.part_start+int(sizeof(EBR));
                }else{
                    //TamanioStruct=int(sizeof(EBR));
                    Comienzo=Te.Particion.part_start;
                }



                FILE *f;
                f=fopen(Real,"r+");
                SPB Super;
                fseek(f,Comienzo,SEEK_SET);
                fread(&Super,sizeof(Super),1,f);

                if(Montar){
                    Fun->Fecha(&Super.s_mtime);

                    Super.s_mnt_count++;
                }
                else{
                    Fun->Fecha(&Super.s_umtime);


                }
                fseek(f,Comienzo,SEEK_SET);
                fwrite(&Super,sizeof(Super),1,f);

                fclose(f);


                return;
            }
        }
        Tempo=Tempo->Siguiente;
    }


}
//Fase1
Disco::Disco(std::string Path,Disco *Nuevo)
{
    this->Path=Path;
    this->Siguiente=Nuevo;
    this->Apodo="vd"+this->GenerarApodo();
}
std::string Disco::GenerarApodo(){
    if(Siguiente==nullptr){
        this->Num=0;
        return this->NumeroAString(0);
    }else{
        this->Num=Siguiente->Num+1;
        if(Num/26>0){
            return this->NumeroAString(Num/26)+this->NumeroAString(Num%26);
        }else {
            return this->NumeroAString(Num%26);
        }
    }
}
void Disco::AgregarParticion(const char *Nombre){
    MOU Mont;
    if(Fun->ExisteArchivo(Path.data())){
        FILE *f;
        MBR Main;
        f=fopen(Path.data(),"r+");
        if (!f){
            return;
        }
        fread(&Main,sizeof(MBR),1,f);
        fclose(f);
        int ParIndex=Fun->SearchPAR(Nombre,Path.data());

        if(ParIndex==-1){
            EBR Logic=Fun->SearchEBR(Nombre,Path.data());
            if(Logic.part_status=='\0'){
                std::cout<<"No Se Encontro La Particion '"<<Nombre<<"' Para Montar En El Disco De  "<<this->Path<<std::endl;
                return;
            }else{//Es Logica
                Mont.EsLogica=true;
                Mont.Logica=Logic;
            }
        }else{
            //Es Primario O Extendida
            Mont.EsLogica=false;
            PAR Part=Main.mbr_partition[ParIndex];
            Mont.Particion=Part;
        }
        for (int i=0;i<Lista.count();i++) {
            MOU Compro =this->Lista.at(i);
            if(Fun->IF(Compro.Nombre,Nombre)){
                std::cout<<"Error Esa Particion Ya Fue Montada   "<<Nombre<<std::endl;
                return;
            }
        }
        Mont.Numero=this->Lista.count()+1;
        Mont.Nombre=Nombre;
        this->Lista<<Mont;
        std::cout<<"Se monto la particion:'"<<Nombre << "'  con el alias:'"<<this->Apodo<<Mont.Numero<<"' En El Disco De  "<<this->Path<<std::endl ;
    }
    else
    {
        std::cout<<"No Se Encontro Un Archivo En La Ubicación "<<Path<<std::endl;
    }

}
std::string Disco::NumeroAString(int Num){
    std::string Salida(1, char(97+Num));
    return Salida;
}
void Disco::BorrarParticion(const char *Nombre){
    Disco *Tempo=this;
    while (Tempo!=nullptr) {

        for (int i=0;i<Tempo->Lista.count();i++) {
            MOU Te= Lista.at(i);
            std::string NombreParti=Tempo->Apodo+std::to_string(Te.Numero);
            if(Fun->IF(NombreParti,Nombre)){
                this->Lista.removeAt(i);
                std::cout<<"Se Borro La Particion "<<Nombre<<" De Memoria Del Disco En Ubicacion "<<Tempo->Path<<std::endl;
                return;
            }
        }
        Tempo=Tempo->Siguiente;
    }

    std::cout<<"No Se Encontro La Particion "<<Nombre<<std::endl;
}

bool Disco::ExisteParticionMontada(const char *Nombre){
    Disco *Tempo=this;
    while (Tempo!=nullptr) {

        for (int i=0;i<Tempo->Lista.count();i++) {
            MOU Te= Lista.at(i);
            std::string NombreParti=Tempo->Apodo+std::to_string(Te.Numero);
            if(Fun->IF(NombreParti,Nombre)){
                return true;
            }
        }
        Tempo=Tempo->Siguiente;
    }
    return false;

}
void Disco::BuscarDisco(const char *Nombre){
    Disco *Tempo=this;
    while (Tempo!=nullptr) {

        for (int i=0;i<Tempo->Lista.count();i++) {
            MOU Te= Lista.at(i);
            std::string NombreParti=Tempo->Apodo+std::to_string(Te.Numero);
            if(Fun->IF(NombreParti,Nombre)){


            }
        }
        Tempo=Tempo->Siguiente;
    }

    std::cout<<"No Se Encontro La Particion "<<Nombre<<std::endl;
}
bool Disco::DiscoLibreParaBorrar(const char *Nombre){
    Disco *Tempo=this;
    while (Tempo!=nullptr) {
        if(Fun->IF(Tempo->Path,Nombre)){
            return false;
        }
        Tempo=Tempo->Siguiente;
    }
    return true;
}
bool Disco::ParticionLibreParaBorrar(const char *Nombre){
    Disco *Tempo=this;
    while (Tempo!=nullptr) {

        for (int i=0;i<Tempo->Lista.count();i++) {
            MOU Te= Lista.at(i);
            std::string NombreParti=Tempo->Apodo+std::to_string(Te.Numero);
            if(Fun->IF(NombreParti,Nombre)){
                return false;
            }
        }
        Tempo=Tempo->Siguiente;
    }
    return true;
}
void Disco::Reporte(const char *ID, const char *Path, const char *Tipo,const char*Ruta){
    Disco *Tempo=this;
    while (Tempo!=nullptr) {
        for (int i=0;i<Tempo->Lista.count();i++) {
            MOU Te= Lista.at(i);
            std::string NombreParti=Tempo->Apodo+std::to_string(Te.Numero);
            if(Fun->IF(NombreParti,ID)){
                int InicioParti=0;
                if(!Te.EsLogica){
                    InicioParti=Te.Particion.part_start;
                }else{
                    InicioParti=Te.Logica.part_start+int(sizeof(EBR));
                }



                Reports *R= new Reports();
                if(Fun->IF(Tipo,"disk")){
                    R->Graphviz(Tempo->Path.data(),Path);
                }else if(Fun->IF(Tipo,"mbr")){
                    R->ReporteTablaMBR(Tempo->Path.data(),Path,Te.Numero);
                //FASE2
                }




                FILE *f;
                f=fopen(Tempo->Path.data(),"r+");
                SPB Super;
                fseek(f,InicioParti,SEEK_SET);
                fread(&Super,sizeof(Super),1,f);
                fclose(f);


                if(Super.s_magic==-1){
                    std::cout<<"Anomalias En La Particion, Cancelando Operacion"<<std::endl;
                    return;
                }

                if(Fun->IF(Tipo,"bm_inode")){
                    R->Reportebm_Inodo(InicioParti,Tempo->Path.data(),Path);
                }else if(Fun->IF(Tipo,"bm_block")){
                    R->Reportebm_Bloque(InicioParti,Tempo->Path.data(),Path);
                }else if(Fun->IF(Tipo,"tree")){
                    R->ReporteArbol(InicioParti,Tempo->Path.data(),Path);
                }else if(Fun->IF(Tipo,"inode")){
                    R->ReporteInode(InicioParti,Tempo->Path.data(),Path);
                }else if(Fun->IF(Tipo,"block")){
                    R->ReporteBlock(InicioParti,Tempo->Path.data(),Path);
                }else if(Fun->IF(Tipo,"sb")){
                    R->ReporteSB(InicioParti,Tempo->Path.data(),Path);
                }else if(Fun->IF(Tipo,"file")){
                    if(Fun->IF(Ruta,""))
                    {
                        std::cout<<"Para Un Reporte FILE se necesita poner la Ruta"<<std::endl;
                        return ;
                    }

                    std::string Contenido;
                    IUG PermisoFalso;
                    PermisoFalso.Gid=1;
                    PermisoFalso.Uid=1;
                    Contenido=LeerArchivoParticion(ID,Ruta,PermisoFalso);


                    R->ReporteFile(Path,Contenido.data());

                }else if(Fun->IF(Tipo,"ls")){
                    if(Fun->IF(Ruta,""))
                    {
                        std::cout<<"Para Un Reporte LS se necesita poner la Ruta"<<std::endl;
                        return ;
                    }

                    FunctionsExt *Ex=new FunctionsExt();

                    FILE *f;
                    f=fopen(Tempo->Path.data(),"r+");
                    SPB Leer;
                    //Leer Super Bloque De La Particion
                    fseek(f,InicioParti,SEEK_SET);
                    fread(&Leer,sizeof(Leer),1,f);
                    fclose(f);

                    int Busqueda=Ex->BuscarActual(Leer.s_first_ino,Path,Tempo->Path.data());
                    R->ReporteLS(Busqueda,Tempo->Path.data(),Ruta,Ex->NombreACrear(Path).data());
                }else if(Fun->IF(Tipo,"journaling")){
                    R->ReporteJournaling(InicioParti,Tempo->Path.data(),Path);
                }

                else{
                    std::cout<<"No Existe Un Reporte Con El Nombre:  "<<Tipo<<std::endl;
                    std::string Fail;
                    std::cin>>Fail;
                }
                delete(R);
                return;
            }
        }
        Tempo=Tempo->Siguiente;
    }
    std::cout<<"No Se Encontro La Particion "<<ID<<std::endl;


}
