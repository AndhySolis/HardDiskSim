#include "edit.h"

EDIT::EDIT(SPB *Super,int Comienzo,const char *PathVirtual,const char *PathReal,std::string Contenido,IUG Permiso)
{
    this->Permiso=Permiso;
    ExpandirArchivo(Super,Comienzo,PathVirtual,PathReal,Contenido);
}
//Expandir Archivos
void EDIT::ExpandirArchivo(SPB *Super, int Comienzo, const char *PathVirtual, const char *PathReal, std::string Contenido){
    int PosArchivo=0;
    PosArchivo=BuscarActual(Comienzo,PathVirtual,PathReal);
    if(PosArchivo==-1){
        std::cout<<"No Se Pudo Agregar Contenido Al Archivo  en"<<PathVirtual<<" En El Disco  Virtual Ubicado En"<<PathReal<<std::endl;
        return ;
    }

    if(TienePermiso(PosArchivo,PathReal,"110",Permiso)==false){
        std::cout<<"No Se Pudo LEER El Archivo Ubicado En '"<<PathVirtual<<"' La Sesion Actual No Tiene Los Permisos Necesarios "<<std::endl;
        return ;
    }

    FILE *f;
    f=fopen(PathReal,"r+");
    INO Inodo;
    fseek(f,PosArchivo,SEEK_SET);
    fread(&Inodo,sizeof(Inodo),1,f);
    fclose(f);


    std::string Retor=ContenidoArchivoDirectos(&Inodo,Super,PosArchivo,PathReal,Contenido);
    if(IF(Retor,"")){
        std::cout<<"Se Modifico El Archivo "<<PathVirtual<<std::endl;
        return ;
    }else{
        std::string Retor=ContenidoArchivoInDirectos(&Inodo,Super,PosArchivo,PathReal,"",Contenido);
    }

    if(IF(Retor,"")){
        std::cout<<"Se Modifico El Archivo "<<PathVirtual<<std::endl;
        return ;
    }

    std::cout<<" El Archivo Llego A Su Limite"<<std::endl;
}
