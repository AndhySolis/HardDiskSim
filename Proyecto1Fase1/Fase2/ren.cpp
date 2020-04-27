#include "ren.h"

REN::REN(int Comienzo, std::string PathVirtual, const char *PathReal,std::string Renombre,IUG Permiso)
{    
    this->Permiso=Permiso;
    CambiarNombre(Comienzo,PathVirtual,PathReal,Renombre);
}
//CambiarNombre
bool REN::CambiarNombre(int Comienzo, std::string PathVirtual, const char *PathReal,std::string Renombre){
    int Padre=BuscarPadre(Comienzo,PathVirtual,PathReal);
    if(Padre==-1){
        std::cout<<"No Se Encontro Una Carpeta O Archivo En "<<PathVirtual<<" No Se Pudo CambiarPermiso"<<std::endl;
        return false ;
    }
    RenombrarInodo(Padre,PathReal,Renombre,PathVirtual);

    return  true;
}
bool REN::RenombrarDirectos(int Comienzo, const char *PathReal,std::string  Info,std::string  Busqueda){
    FILE *f;
    f=fopen(PathReal,"r+");
    BCA Carpeta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);
    std::string Concatenar="";
    for(int i=0;i<4;i++){
        CON Contenido=Carpeta.content[i];

        if(Contenido.b_inodo!=-1){
            std::string Nama=NombreACrear(Busqueda.data());
            if(IF(Contenido.b_name,Nama)){




                if(TienePermiso(Contenido.b_inodo,PathReal,"010",Permiso)==false){
                    std::cout<<"No Se Pudo ESCRIBIR El Archivo Ubicado En '"<<Info<<"' La Sesion Actual No Tiene Los Permisos Necesarios "<<std::endl;
                    return true;
                }


                f=fopen(PathReal,"r+");
                BCA Carpeta;
                fseek(f,Comienzo,SEEK_SET);
                fread(&Carpeta,sizeof(Carpeta),1,f);
                strcpy(Carpeta.content[i].b_name,(Info).substr(0,12).c_str());
                fseek(f,Comienzo,SEEK_SET);
                fwrite(&Carpeta,sizeof(Carpeta),1,f);
                fclose(f);
                return true;
            }

        }
    }
    return false;
}
bool REN::RenombrarIndirectos(int Nivel, int NivelActual, int Comienzo,  const char *PathReal,std::string  Info,std::string  Busqueda){
    if(Nivel==NivelActual){
        return PermisoDirectos(Comienzo,PathReal,Permiso);
    }
    FILE *f;
    f=fopen(PathReal,"r+");
    BAP Apunta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Apunta,sizeof(Apunta),1,f);
    fclose(f);
    bool Com=false;
    for(int i=0;i<16;i++){
        int Valor=Apunta.b_pointers[i];
        if(Valor!=-1){
            Com=RenombrarIndirectos(Nivel,NivelActual+1,Valor,PathReal,Info,Busqueda);
            if(Com==true)
                return true;
        }
    }

    return false;
}
bool REN::RenombrarInodo(int Comienzo, const char *PathReal,std::string  Info,std::string  Busqueda){
    FILE *f;
    f=fopen(PathReal,"r+");
    INO Carpeta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);

    bool Comp=false;
    for(int i=0;i<12;i++){
        int Apuntador=Carpeta.i_block[i];
        if(Apuntador!=-1){
            Comp=RenombrarIndirectos(0,0,Apuntador,PathReal,Info,Busqueda);
            if(Comp==true)
                return true;
        }
    }

    for(int i=0;i<3;i++){
        int Apuntador=Carpeta.i_block[i+12];
        if(Apuntador!=-1){
            Comp=RenombrarIndirectos(1+i,0,Apuntador,PathReal,Info,Busqueda);
            if(Comp==true)
                return true;
        }
    }
    return false;
}
