#include "rem.h"

REM::REM(SPB *Super,int Comienzo,const char *PathVirtual,const char *PathReal,IUG Permiso)
{
    this->Permiso=Permiso;
    EliminarArchivoCarpeta(Super,Comienzo,PathVirtual,PathReal);
}

bool REM::EliminarArchivoCarpeta(SPB *Super, int Comienzo, const char *PathVirtual, const char *PathReal){
    std::string Conserva=PathVirtual;
    int Actual=BuscarActual(Comienzo,PathVirtual,PathReal);
    if(Actual==-1){
        std::cout<<"No Se Encontro Una Carpeta O Archivo En "<<PathVirtual<<" No Se Pudo Borrar"<<std::endl;
        return false;
    }

    bool Permitido=PermisoInodo(Actual,PathReal,Permiso);
    if(Permitido==false){
        std::cout<<"No Tiene Permiso En Todos Los Archivos Y SubCarpetas, No Se Puede Borrar "<<std::endl;
        return false;
    }
    FILE *f;
    f=fopen(PathReal,"r+");
    INO Carpeta;
    fseek(f,Actual,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);
    int Tipo=0;
    if(Carpeta.i_type=='1')
        Tipo=1;
    for(int i=0;i<12;i++){
        int Apuntador=Carpeta.i_block[i];
        if(Apuntador!=-1){
            EliminarIndirectos(Super,0,0,Apuntador,PathReal,Tipo,10);
        }
    }

    for(int i=0;i<3;i++){
        int Apuntador=Carpeta.i_block[i+12];
        if(Apuntador!=-1){
            EliminarIndirectos(Super,1+i,0,Apuntador,PathReal,Tipo,10);
        }
    }

    if(EliminarArchivoCarpetaPadre(Super,Comienzo,Conserva.data(),PathReal,Actual)){
        std::cout<<"Se Elimino La Ruta O Archivo: "<<PathVirtual<<std::endl;
        LiberarInodo(Super,PathReal,Actual);
        return true;
    }else{
        std::cout<<"No Se Pudo Eliminar"<<PathVirtual<<std::endl;
        return  false;
    }

}



