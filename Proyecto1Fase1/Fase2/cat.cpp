#include "cat.h"

CAT::CAT(IUG Permiso)
{
    this->Permiso=Permiso;
    //LeerArchivo(Inicio,Disco,Path);
}
//LeerArchivo
std::string CAT::LeerDirectos(int Comienzo,const char *PathReal){
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
            Concatenar=Concatenar+LeerBloqueContenido(Contenido.b_inodo,PathReal);
        }
    }
    return Concatenar;
}
std::string CAT::LeerBloqueContenido(int Comienzo, const char *PathReal){
    FILE *f;
    f=fopen(PathReal,"r+");
    BAR Dato;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Dato,sizeof(Dato),1,f);
    fclose(f);
    std::string Salida;
    Salida=Dato.b_content;
    Salida=Salida.substr(0,64);
    return Salida;
}
std::string CAT::LeerIndirectos(int Nivel, int NivelActual, int Comienzo,  const char *PathReal){
    if(Nivel==NivelActual){
        return LeerDirectos(Comienzo,PathReal);
    }
    FILE *f;
    f=fopen(PathReal,"r+");
    BAP Apunta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Apunta,sizeof(Apunta),1,f);
    fclose(f);
    std::string Concatenar="";
    for(int i=0;i<16;i++){
        int Valor=Apunta.b_pointers[i];
        if(Valor!=-1){
            Concatenar=Concatenar+LeerIndirectos(Nivel,NivelActual+1,Valor,PathReal);
        }
    }
    return Concatenar;
}

std::string CAT::LeerArchivo(int Inicio, const char *Disco, const char *Path){

    int Busqueda=BuscarActual(Inicio,Path,Disco);
    std::string Contenido="";


    //std::cout<<"---     "<<BuscarPadre(Inicio,Path,Disco)<<std::endl;

    if(Busqueda==-1){
        std::cout<<"No Se Encontro El Archivo"<<std::endl;
        return "";
    }else{

        if(TienePermiso(Busqueda,Disco,"100",Permiso)==false){
            std::cout<<"No Se Pudo LEER El Archivo Ubicado En '"<<Path<<"' La Sesion Actual No Tiene Los Permisos Necesarios "<<std::endl;
            return "";
        }

        //Busqueda El Inodo Del Archivo
        FILE *f;
        f=fopen(Disco,"r+");
        INO Carpeta;
        fseek(f,Busqueda,SEEK_SET);
        fread(&Carpeta,sizeof(Carpeta),1,f);
        fclose(f);


        if(Carpeta.i_type=='0'){
            std::cout<<"Solo Se Puede Obtener Contenido De Carpetas"<<std::endl;
            return "";
        }

        for(int i=0;i<12;i++){
            int Apuntador=Carpeta.i_block[i];
            if(Apuntador!=-1){

             Contenido=Contenido+LeerIndirectos(0,0,Apuntador,Disco);
            }
        }

        for(int i=0;i<3;i++){
            int Apuntador=Carpeta.i_block[i+12];
            if(Apuntador!=-1){
            Contenido=Contenido+LeerIndirectos(1+i,0,Apuntador,Disco);
            }
        }
    }

    return Contenido;
}

