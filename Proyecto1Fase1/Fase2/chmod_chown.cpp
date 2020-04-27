#include "chmod_chown.h"

CHMOD_CHOWN::CHMOD_CHOWN(int Comienzo, const char *PathVirtual, const char *PathReal, int NuevoDuenio,int OPE,IUG Permiso,bool Propietario)
{
    this->Permiso=Permiso;
    if(Propietario){
        CambiarPropietarioNormalRecursivo(Comienzo,PathVirtual,PathReal,NuevoDuenio,OPE);
    }else{
        CambiarPermisosNormalRecursivo(Comienzo,PathVirtual,PathReal,NuevoDuenio,OPE);
    }
}
//Cambiar Propietario
void CHMOD_CHOWN::CambiarPropietarioNormalRecursivo(int Comienzo, const char *PathVirtual, const char *PathReal, int NuevoDuenio,int OPE){
    int Actual=BuscarActual(Comienzo,PathVirtual,PathReal);
    if(Actual==-1){
        std::cout<<"No Se Encontro Una Carpeta O Archivo En "<<PathVirtual<<" No Se Pudo CambiarPermiso"<<std::endl;
        return ;
    }


    FILE *f;
    f=fopen(PathReal,"r+");
    INO Carpeta;
    fseek(f,Actual,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);

    //Si Es Root o Dueño De la Carpeta
    if(Permiso.Uid==1 ||Permiso.Gid==1 || Permiso.Uid==Carpeta.i_uid){
        Carpeta.i_uid=NuevoDuenio;
        //Carpeta.i_gid=Permiso.Gid;
        fseek(f,Actual,SEEK_SET);
        fwrite(&Carpeta,sizeof(Carpeta),1,f);

    }else{
        std::cout<<"No Se Pueden Cambiar El Propietario De La Carpeta, El Usuario Con Codigo "<<Permiso.Uid<<" No Es El Propietario"<<std::endl;
        return ;
    }

    fclose(f);


    //Cambiar De Manera Normal
    if(OPE==0){
        std::cout<<"Se Cambiaron El Propietario A Solo Una Carpeta O Archivo De '"<<PathVirtual<<"' Cod Nuevo Duenoi: "<<std::to_string(Permiso.Uid)<<std::endl;
        return ;

    }

    //Es Carpeta
    if(Carpeta.i_type=='1')
        return;

    for(int i=0;i<12;i++){
        int Apuntador=Carpeta.i_block[i];
        if(Apuntador!=-1){
            ModificarIndirectos(0,0,Apuntador,PathReal,2,NuevoDuenio);
        }
    }

    for(int i=0;i<3;i++){
        int Apuntador=Carpeta.i_block[i+12];
        if(Apuntador!=-1){
            ModificarIndirectos(1+i,0,Apuntador,PathReal,2,NuevoDuenio);
        }
    }

    std::cout<<"Se Cambio El Propietario De Manera Recursiva De '"<<PathVirtual<<"' El Nuevo Propietario Codigo: "<<std::to_string(NuevoDuenio)<<std::endl;


}
//Busqueda De Carpetas O Archivos  CHMOD
void CHMOD_CHOWN::CambiarPermisosNormalRecursivo(int Comienzo, const char *PathVirtual, const char *PathReal,int Ope,int Perm){
    int Actual=BuscarActual(Comienzo,PathVirtual,PathReal);
    if(Actual==-1){
        std::cout<<"No Se Encontro Una Carpeta O Archivo En "<<PathVirtual<<" No Se Pudo CambiarPermiso"<<std::endl;
        return ;
    }


    FILE *f;
    f=fopen(PathReal,"r+");
    INO Carpeta;
    fseek(f,Actual,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);

    //Si Es Root o Dueño De la Carpeta
    if(Permiso.Uid==1 ||Permiso.Gid==1 || Permiso.Uid==Carpeta.i_uid){
        Carpeta.i_perm=Perm;
        fseek(f,Actual,SEEK_SET);
        fwrite(&Carpeta,sizeof(Carpeta),1,f);

    }else{
        std::cout<<"No Se Pueden Cambiar Los Permisos El Usuario Con Codigo "<<Permiso.Uid<<" No Es El Propietario Ni root"<<std::endl;
        return ;
    }

    fclose(f);


    //Cambiar De Manera Normal
    if(Ope==0){
        std::cout<<"Se Cambiaron Los Permisos A Solo Una Carpeta De '"<<PathVirtual<<"' Al Tipo De Permisos: "<<std::to_string(Perm).substr(1)<<std::endl;
        return ;

    }

    //Es Archivo
    if(Carpeta.i_type=='1')
        return;

    for(int i=0;i<12;i++){
        int Apuntador=Carpeta.i_block[i];
        if(Apuntador!=-1){
            ModificarIndirectos(0,0,Apuntador,PathReal,1,Perm);
        }
    }

    for(int i=0;i<3;i++){
        int Apuntador=Carpeta.i_block[i+12];
        if(Apuntador!=-1){
            ModificarIndirectos(1+i,0,Apuntador,PathReal,1,Perm);
        }
    }

    std::cout<<"Se Cambiaron Los Permisos De Manera Recursiva De '"<<PathVirtual<<"' Al Tipo De Permisos: "<<std::to_string(Perm).substr(1)<<std::endl;
}
//Modificar CHMOD
void CHMOD_CHOWN::ModificarDirectos(int Comienzo, const char *PathReal, int Tipo,int Perm){
    FILE *f;
    f=fopen(PathReal,"r+");
    BCA Carpeta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);
    for(int i=0;i<4;i++){
        CON Contenido=Carpeta.content[i];

        if(Contenido.b_inodo!=-1){
            ModificarInodo(Contenido.b_inodo,PathReal,Tipo,Perm);
        }
    }
}
void CHMOD_CHOWN::ModificarIndirectos(int Nivel, int NivelActual, int Comienzo,  const char *PathReal, int Tipo,int Perm){
    if(Nivel==NivelActual){
        return ModificarDirectos(Comienzo,PathReal,Tipo,Perm);
    }
    FILE *f;
    f=fopen(PathReal,"r+");
    BAP Apunta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Apunta,sizeof(Apunta),1,f);
    fclose(f);
    for(int i=0;i<16;i++){
        int Valor=Apunta.b_pointers[i];
        if(Valor!=-1){
            ModificarIndirectos(Nivel,NivelActual+1,Valor,PathReal,Tipo,Perm);
        }
    }

}
//Tipo==1 CHMOD Recursivo   Tipo==2 CHOWN Recursivo
void CHMOD_CHOWN::ModificarInodo(int Comienzo, const char *PathReal,int Tipo,int Perm){
    FILE *f;
    f=fopen(PathReal,"r+");
    INO Carpeta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);


    if(Tipo==1){
        Carpeta.i_perm=Perm;
    }else if(Tipo==2){
        Carpeta.i_uid=Perm;
    }

    fseek(f,Comienzo,SEEK_SET);
    fwrite(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);

    if(Carpeta.i_type=='1')//Es Carpeta No Hay Mas
        return;

    for(int i=0;i<12;i++){
        int Apuntador=Carpeta.i_block[i];
        if(Apuntador!=-1){
            ModificarIndirectos(0,0,Apuntador,PathReal,Tipo,Perm);
        }
    }

    for(int i=0;i<3;i++){
        int Apuntador=Carpeta.i_block[i+12];
        if(Apuntador!=-1){
            ModificarIndirectos(1+i,0,Apuntador,PathReal,Tipo,Perm);
        }
    }
}
