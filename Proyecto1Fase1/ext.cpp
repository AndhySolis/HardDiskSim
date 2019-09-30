#include "ext.h"
#include "structsext.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

/*
 * Solo Contenido en los primeros 12
* AL COLOCAR ARCHIVOS,ARCHIVO CONTENIDO Y CARPETAS FALTA COMPROBACION SI SE ACABARON LOS ESOACIOS PARA BLOQUES INODOS
*El USAR LA CARPETA '/' CAusa Errores
*/

//Cambiar Propietario
void EXT::CambiarPropietarioNormalRecursivo(int Comienzo, const char *PathVirtual, const char *PathReal, int NuevoDuenio,int OPE){
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
    if(OPE==1){
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
//FIND Arbol
void EXT::FIND(int Comienzo, std::string PathVirtual, const char *PathReal){
    int Buscar=BuscarActual(Comienzo,PathVirtual,PathReal);
    if(Buscar==-1){
        std::cout<<"No Se Encontro El Archivo O Carpeta En "<<PathVirtual<<std::endl;
        return ;
    }
    if(TienePermiso(Buscar,PathReal,"100")==false){
        std::cout<<"No Tiene Permisos De Lectura Para "<<PathVirtual<<" No se puede aplicar comando Find"<<std::endl;
        return;
    }

    FindInodo(Comienzo,PathReal,"");

}
void EXT::FindDirectos(int Comienzo, const char *PathReal,int Tipo,std::string Expansion){
    FILE *f;
    f=fopen(PathReal,"r+");
    BCA Carpeta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);

    for(int i=0;i<4;i++){
        CON Contenido=Carpeta.content[i];
        if(Contenido.b_inodo!=-1){

            if(Tipo==0){//Carpeta
                std::cout<<Expansion<<"|_"<<Contenido.b_name<<std::endl;
                Expansion=Expansion+" ";
                FindInodo(Contenido.b_inodo,PathReal,Expansion);

            }else{
                std::cout<<Expansion<<"||_"<<Contenido.b_name<<std::endl;
            }
        }
    }

}
void EXT::FindIndirectos(int Nivel, int NivelActual, int Comienzo,  const char *PathReal,int Tipo,std::string Expansion){
    if(Nivel==NivelActual){
        FindDirectos(Comienzo,PathReal,Tipo,Expansion);
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
           FindIndirectos(Nivel,NivelActual+1,Valor,PathReal,Tipo,Expansion);
        }
    }
}
void EXT::FindInodo(int Comienzo, const char *PathReal,std::string Expansion){
    if(TienePermiso(Comienzo,PathReal,"100")==false){
        return ;
    }


    FILE *f;
    f=fopen(PathReal,"r+");
    INO Carpeta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);

    int Tipo=1;
    if(Carpeta.i_type=='0')
        Tipo=0;
    for(int i=0;i<12;i++){
        int Apuntador=Carpeta.i_block[i];
        if(Apuntador!=-1){
            FindIndirectos(0,0,Apuntador,PathReal,Tipo,Expansion);

        }
    }

    for(int i=0;i<3;i++){
        int Apuntador=Carpeta.i_block[i+12];
        if(Apuntador!=-1){
            FindIndirectos(1+i,0,Apuntador,PathReal,Tipo,Expansion);
        }
    }

}
//Mover
void EXT::MoverCarpetaArchivo(SPB *Super, int Comienzo, std::string PathVirtualOrigen, const char *PathReal, std::string PathVirtualDestino){
    int Existe=BuscarActual(Comienzo,PathVirtualOrigen,PathReal);
    //Buscar Que Exista
    if(Existe==-1){
        std::cout<<"El Archivo/Carpeta No Existe En La Ruta "<<PathVirtualOrigen<<std::endl;
        return;
    }
    //Leer informacion
    FILE *f;
    f=fopen(PathReal,"r+");
    INO Carpeta;//Leyendo Donde Se Coloco La Carpeta o Archivo Copia
    fseek(f,Existe,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);
    //Borrar Del Padre
    EliminarArchivoCarpetaPadre(Super,Comienzo,PathVirtualOrigen.data(),PathReal,Existe);
    //Crear Lugar En El Nuevo Padre
    //Ver El Tipo
    int Tipo=0;
    if(Carpeta.i_type=='1')
        Tipo=1;
    //Crear Ubicacion Dependiendo El Tipo
    if(Tipo==0)
        CrearCarpetaSimple(Super,Comienzo,PathVirtualDestino.data(),PathReal);
    else
        CrearArchivoSimple(Super,Comienzo,PathVirtualDestino.data(),PathReal,"Dummy");
    //Ver Si Se Pudo Crear
    int Colocado=BuscarActual(Comienzo,PathVirtualDestino,PathReal);
    if(Colocado==-1){
        std::cout<<"No Se Pudo Colocar La Carpeta O Archivo En Su Destino "<<PathVirtualDestino<<std::endl;
        return;
    }
    //Actualizar La Informacion De Lo Creado Con Lo SIMPLE
    f=fopen(PathReal,"r+");
    fseek(f,Colocado,SEEK_SET);
    fwrite(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);
}
//Copiar
void EXT::CopiarCarpetaArchivo(SPB *Super,int Comienzo, std::string PathVirtualOrigen, const char *PathReal, std::string PathVirtualDestino){
    int Actual=BuscarActual(Comienzo,PathVirtualOrigen,PathReal);
    if(Actual==-1){
        std::cout<<"No Se Puede Copiar, Porque No Se Encontro La Carpeta/Archivo De Origen  "<<PathVirtualOrigen<<std::endl;
        return;
    }
    //Copiando Archivo O Carpeta
    Actual=CopiarInodo(Super,Actual,PathReal);
    if(Actual==-1){
        std::cout<<"No Se Puede Copiar, Porque No Se Tienen Los Permisos Para Copiar  "<<PathVirtualOrigen<<std::endl;
        return;
    }
    FILE *f;
    f=fopen(PathReal,"r+");
    INO Carpeta;//Leyendo Donde Se Coloco La Carpeta o Archivo Copia
    fseek(f,Actual,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);
    //Libera Donde Estaba La Copia
    LiberarInodo(Super,PathReal,Actual);
    //Para Colocar En La Ubicacion Destino
    PathVirtualDestino=PathVirtualDestino+"/"+NombreACrear(PathVirtualOrigen.data());
    //Ver El Tipo
    int Tipo=0;
    if(Carpeta.i_type=='1')
        Tipo=1;
    //Crear Ubicacion Dependiendo El Tipo
    if(Tipo==0)
        CrearCarpetaSimple(Super,Comienzo,PathVirtualDestino.data(),PathReal);
    else
        CrearArchivoSimple(Super,Comienzo,PathVirtualDestino.data(),PathReal,"Dummy");
    //Ver Si Se Pudo Crear
    int Colocado=BuscarActual(Comienzo,PathVirtualDestino,PathReal);
    if(Colocado==-1){
        std::cout<<"No Se Pudo Colocar La Carpeta O Archivo En Su Destino "<<PathVirtualDestino<<std::endl;
        return;
    }
    //Actualizar La Informacion De Lo Creado Con Lo SIMPLE
    f=fopen(PathReal,"r+");
    fseek(f,Colocado,SEEK_SET);
    fwrite(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);
}
int EXT::CopiarContenido(SPB *Super,int Comienzo, const char *PathReal){
    FILE *f;
    f=fopen(PathReal,"r+");
    BAR Contenido;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Contenido,sizeof(Contenido),1,f);
    fclose(f);
    BAR CopiaConte;
    strcpy(CopiaConte.b_content,Contenido.b_content);
    int NuevaCopia=BloqueLibre(Super,PathReal);
    if(NuevaCopia==-1)
        return NuevaCopia;
    f=fopen(PathReal,"r+");
    fseek(f,NuevaCopia,SEEK_SET);
    fwrite(&CopiaConte,sizeof(CopiaConte),1,f);
    fclose(f);
    return NuevaCopia;
}
int EXT::CopiarDirectos(SPB *Super,int Comienzo, const char *PathReal,int Tipo){
    FILE *f;
    f=fopen(PathReal,"r+");
    BCA Carpeta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);

    BCA CopiaDir;
    for(int i=0;i<4;i++){
        CON Contenido=Carpeta.content[i];
        if(Contenido.b_inodo!=-1){
            if(Tipo==0){//Carpeta
                CopiaDir.content[i].b_inodo=CopiarInodo(Super,Contenido.b_inodo,PathReal);
                strcpy(CopiaDir.content[i].b_name,Carpeta.content[i].b_name);
            }else{//Archivo
                CopiaDir.content[i].b_inodo=CopiarContenido(Super,Contenido.b_inodo,PathReal);
                strcpy(CopiaDir.content[i].b_name,".....");
            }
        }else{
            CopiaDir.content[i].b_inodo=-1;
        }
    }



    int NuevaCopia=BloqueLibre(Super,PathReal);
    if(NuevaCopia==-1)
        return NuevaCopia;
    f=fopen(PathReal,"r+");
    fseek(f,NuevaCopia,SEEK_SET);
    fwrite(&CopiaDir,sizeof(CopiaDir),1,f);
    fclose(f);
    return NuevaCopia;
}
int EXT::CopiarIndirectos(SPB *Super,int Nivel, int NivelActual, int Comienzo,  const char *PathReal,int Tipo){
    if(Nivel==NivelActual){
        return CopiarDirectos(Super,Comienzo,PathReal,Tipo);
    }
    FILE *f;
    f=fopen(PathReal,"r+");
    BAP Apunta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Apunta,sizeof(Apunta),1,f);
    fclose(f);

    BAP CopiaPtr;

    for(int i=0;i<16;i++){
        int Valor=Apunta.b_pointers[i];
        if(Valor!=-1){
            CopiaPtr.b_pointers[i]=CopiarIndirectos(Super,Nivel,NivelActual+1,Valor,PathReal,Tipo);
        }else{
            CopiaPtr.b_pointers[i]=-1;
        }
    }

    int NuevaCopia=BloqueLibre(Super,PathReal);
    if(NuevaCopia==-1)
        return NuevaCopia;
    f=fopen(PathReal,"r+");
    fseek(f,NuevaCopia,SEEK_SET);
    fwrite(&CopiaPtr,sizeof(CopiaPtr),1,f);
    fclose(f);
    return NuevaCopia;

}
int EXT::CopiarInodo(SPB *Super,int Comienzo, const char *PathReal){
    if(TienePermiso(Comienzo,PathReal,"100")==false){
        return -1;
    }


    FILE *f;
    f=fopen(PathReal,"r+");
    INO Carpeta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);

    INO CopiaCarpeta;
    DuplicarInodo(&Carpeta,&CopiaCarpeta);
    int Tipo=1;
    if(Carpeta.i_type=='0')
        Tipo=0;
    for(int i=0;i<12;i++){
        int Apuntador=Carpeta.i_block[i];
        if(Apuntador!=-1){
            CopiaCarpeta.i_block[i]=CopiarIndirectos(Super,0,0,Apuntador,PathReal,Tipo);

        }else{
            CopiaCarpeta.i_block[i]=-1;
        }
    }

    for(int i=0;i<3;i++){
        int Apuntador=Carpeta.i_block[i+12];
        if(Apuntador!=-1){
            CopiaCarpeta.i_block[i]=CopiarIndirectos(Super,1+i,0,Apuntador,PathReal,Tipo);
        }else{
            CopiaCarpeta.i_block[i]=-1;
        }
    }
    int NuevaCopia=InodoLibre(Super,PathReal);
    if(NuevaCopia==-1)
        return NuevaCopia;
    f=fopen(PathReal,"r+");
    fseek(f,NuevaCopia,SEEK_SET);
    fwrite(&CopiaCarpeta,sizeof(CopiaCarpeta),1,f);
    fclose(f);
    return NuevaCopia;
}

void EXT::DuplicarInodo(INO *Original, INO *Copia){
    Copia->i_gid=Original->i_gid;
    Copia->i_uid=Original->i_uid;
    Copia->i_perm=Original->i_perm;
    Copia->i_size=Original->i_size;
    Copia->i_type=Original->i_type;
    Copia->i_atime=Original->i_atime;
    Copia->i_ctime=Original->i_ctime;
    Copia->i_mtime=Original->i_mtime;
}
//CambiarNombre
bool EXT::CambiarNombre(int Comienzo, std::string PathVirtual, const char *PathReal,std::string Renombre){
    int Padre=BuscarPadre(Comienzo,PathVirtual,PathReal);
    if(Padre==-1){
        std::cout<<"No Se Encontro Una Carpeta O Archivo En "<<PathVirtual<<" No Se Pudo CambiarPermiso"<<std::endl;
        return false ;
    }
    RenombrarInodo(Padre,PathReal,Renombre,PathVirtual);

    return  true;
}
bool EXT::RenombrarDirectos(int Comienzo, const char *PathReal,std::string  Info,std::string  Busqueda){
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
            if(Fun->IF(Contenido.b_name,Nama)){




                if(TienePermiso(Contenido.b_inodo,PathReal,"010")==false){
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
bool EXT::RenombrarIndirectos(int Nivel, int NivelActual, int Comienzo,  const char *PathReal,std::string  Info,std::string  Busqueda){
    if(Nivel==NivelActual){
        return PermisoDirectos(Comienzo,PathReal);
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
bool EXT::RenombrarInodo(int Comienzo, const char *PathReal,std::string  Info,std::string  Busqueda){
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
//Busqueda De Carpetas O Archivos
void EXT::CambiarPermisosNormalRecursivo(int Comienzo, const char *PathVirtual, const char *PathReal,int Ope,int Perm){
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
        std::cout<<"No Se Pueden Cambiar Los Permisos El Usuario Con Codigo "<<Permiso.Uid<<" No Es El Propietario"<<std::endl;
        return ;
    }

    fclose(f);


    //Cambiar De Manera Normal
    if(Ope==1){
        std::cout<<"Se Cambiaron Los Permisos A Solo Una Carpeta De '"<<PathVirtual<<"' Al Tipo De Permisos: "<<std::to_string(Perm).substr(1)<<std::endl;
        return ;

    }

    //Es Carpeta
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

bool EXT::TienePermiso(int Comienzo, const char *PathReal, std::string Info){   
    std::string PermisoCarpeta=PermisosEnElPadre(Comienzo,PathReal);
   if(Fun->IF(PermisoCarpeta,""))
       return false;



   for(int i=0;i<3;i++){
       char Com=PermisoCarpeta.data()[i];
       char Per=Info.data()[i];
       if(Per=='1'){


           if(Com=='0'){

               return false;
               }
       }
   }

   return true;
}

std::string EXT::PermisosEnElPadre(int Comienzo, const char *PathReal){
    FILE *f;
    f=fopen(PathReal,"r+");
    INO Carpeta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);

    int Selec=3;
    if(Carpeta.i_uid==Permiso.Uid){
        Selec=1;
    }else if(Carpeta.i_gid==Permiso.Gid){
        Selec=2;
    }

    if(Permiso.Uid==1 || Permiso.Gid==1)
        return "111";

    std::string Comparar="";

    std::string Num = std::to_string(Carpeta.i_perm);
    if(Num.length()==10){
        switch (Selec) {
        case 1:{
            Comparar=Comparar+Num.data()[1]+Num.data()[2]+Num.data()[3];
            break;
        }
        case 2:{
            Comparar=Comparar+Num.data()[4]+Num.data()[5]+Num.data()[6];
            break;
        }
        case 3:{
            Comparar=Comparar+Num.data()[7]+Num.data()[8]+Num.data()[9];
            break;
        }

        }

    }else
        std::cout<<"Error En La Particion, Permisos n Leer Correctamente"<<std::endl;
    return Comparar;
}
//Verificar Si Tiene Permisos
bool EXT::PermisoDirectos(int Comienzo, const char *PathReal){
    FILE *f;
    f=fopen(PathReal,"r+");
    BCA Carpeta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);
    std::string Concatenar="";
    bool Comp=true;
    for(int i=0;i<4;i++){
        CON Contenido=Carpeta.content[i];

        if(Contenido.b_inodo!=-1){
            Comp=PermisoInodo(Contenido.b_inodo,PathReal);
            if(Comp==false)
                return false;
        }
    }
    return true;
}
bool EXT::PermisoIndirectos(int Nivel, int NivelActual, int Comienzo,  const char *PathReal){
    if(Nivel==NivelActual){
        return PermisoDirectos(Comienzo,PathReal);
    }
    FILE *f;
    f=fopen(PathReal,"r+");
    BAP Apunta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Apunta,sizeof(Apunta),1,f);
    fclose(f);
    bool Com=true;
    for(int i=0;i<16;i++){
        int Valor=Apunta.b_pointers[i];
        if(Valor!=-1){
            Com=PermisoIndirectos(Nivel,NivelActual+1,Valor,PathReal);
            if(Com==false)
                return false;
        }
    }

    return true;
}
bool EXT::PermisoInodo(int Comienzo, const char *PathReal){
    FILE *f;
    f=fopen(PathReal,"r+");
    INO Carpeta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);

    if(TienePermiso(Comienzo,PathReal,"010")==false)
        return false;

    if(Carpeta.i_type=='1')//Es Carpeta No Hay Mas
        return true;

    bool Comp=true;
    for(int i=0;i<12;i++){
        int Apuntador=Carpeta.i_block[i];
        if(Apuntador!=-1){
            Comp=PermisoIndirectos(0,0,Apuntador,PathReal);
            if(Comp==false)
                return false;
        }
    }

    for(int i=0;i<3;i++){
        int Apuntador=Carpeta.i_block[i+12];
        if(Apuntador!=-1){
            Comp=PermisoIndirectos(1+i,0,Apuntador,PathReal);
            if(Comp==false)
                return false;
        }
    }
    return true;
}
//Modificar CHMOD
void EXT::ModificarDirectos(int Comienzo, const char *PathReal, int Tipo,int Perm){
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
void EXT::ModificarIndirectos(int Nivel, int NivelActual, int Comienzo,  const char *PathReal, int Tipo,int Perm){
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
void EXT::ModificarInodo(int Comienzo, const char *PathReal,int Tipo,int Perm){
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
//Eliminar Archivo
bool EXT::EliminarArchivoCarpetaPadre(SPB *Super, int Comienzo, const char *PathVirtual, const char *PathReal, int Hijo){
    int Actual=BuscarPadre(Comienzo,PathVirtual,PathReal);
    if(Actual==-1){
        std::cout<<"No Se Encontro Una Carpeta O Archivo En "<<PathVirtual<<" No Se Pudo Borrar"<<std::endl;
        return false;
    }


    FILE *f;
    f=fopen(PathReal,"r+");
    INO Carpeta;
    fseek(f,Actual,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);
    bool Retorno=false;
    for(int i=0;i<12;i++){
        int Apuntador=Carpeta.i_block[i];
        if(Apuntador!=-1){
            Retorno=EliminarIndirectos(Super,0,0,Apuntador,PathReal,4,Hijo);
            if(Retorno)
                return  true;
        }
    }

    for(int i=0;i<3;i++){
        int Apuntador=Carpeta.i_block[i+12];
        if(Apuntador!=-1){
            Retorno=EliminarIndirectos(Super,1+i,0,Apuntador,PathReal,4,Hijo);
            if(Retorno)
                return  true;
        }
    }

    return false;
}

bool EXT::EliminarArchivoCarpeta(SPB *Super, int Comienzo, const char *PathVirtual, const char *PathReal){
    std::string Conserva=PathVirtual;
    int Actual=BuscarActual(Comienzo,PathVirtual,PathReal);
    if(Actual==-1){
        std::cout<<"No Se Encontro Una Carpeta O Archivo En "<<PathVirtual<<" No Se Pudo Borrar"<<std::endl;
        return false;
    }
    bool Permitido=PermisoInodo(Actual,PathReal);
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
void EXT::LiberarInodo(SPB *Super, const char *PathReal, int Comienzo){
    FILE *f;
    f=fopen(PathReal,"r+");
    char Actual='0';
    int See=Super->s_bm_inode_start+(Comienzo-Super->s_inode_start)/Super->s_inode_size;
    fseek(f,See,SEEK_SET);
    fwrite(&Actual,sizeof(Actual),1,f);
    fclose(f);
}
void EXT::LiberarBloque(SPB *Super, const char *PathReal,int Comienzo){
    FILE *f;
    f=fopen(PathReal,"r+");
    char Actual='0';
    int See=Super->s_bm_block_start+(Comienzo-Super->s_block_start)/Super->s_block_size;
    fseek(f,See,SEEK_SET);
    fwrite(&Actual,sizeof(Actual),1,f);
    fclose(f);

}
bool EXT::EliminarDirectos(SPB *Super,int Comienzo, const char *PathReal, int Tipo, int Elim){
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
            if(Contenido.b_inodo==Elim && Tipo ==4){
                Carpeta.content[i].b_inodo=-1;
                strcpy(Carpeta.content[i].b_name,"*********");
                f=fopen(PathReal,"r+");
                fseek(f,Comienzo,SEEK_SET);
                fwrite(&Carpeta,sizeof(Carpeta),1,f);
                fclose(f);
                return true;
            }

            if(Tipo==1){
                EliminarBloqueContenido(Super,Contenido.b_inodo,PathReal);
            }else if(Tipo==0){
                EliminarInodo(Super,Contenido.b_inodo,PathReal);
            }
        }
    }
    if(Tipo!=4)
    LiberarBloque(Super,PathReal,Comienzo);
    return false;
}
bool EXT::EliminarBloqueContenido(SPB *Super,int Comienzo,const char *PathReal){
    LiberarBloque(Super,PathReal,Comienzo);
    return true;
}
bool EXT::EliminarIndirectos(SPB *Super,int Nivel, int NivelActual, int Comienzo,  const char *PathReal, int Tipo, int Elim){
    if(Nivel==NivelActual){
        return EliminarDirectos(Super,Comienzo,PathReal,Tipo,Elim);
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
            EliminarIndirectos(Super,Nivel,NivelActual+1,Valor,PathReal,Tipo,Elim);
        }
    }
    if(Tipo!=4)
    LiberarBloque(Super,PathReal,Comienzo);

    return true;
}
bool EXT::EliminarInodo(SPB *Super,int Comienzo, const char *PathReal){
    FILE *f;
    f=fopen(PathReal,"r+");
    INO Carpeta;
    fseek(f,Comienzo,SEEK_SET);
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

    LiberarInodo(Super,PathReal,Comienzo);
    return true;
}
//LeerArchivo
std::string EXT::LeerDirectos(int Comienzo,const char *PathReal){
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
std::string EXT::LeerBloqueContenido(int Comienzo, const char *PathReal){
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
std::string EXT::LeerIndirectos(int Nivel, int NivelActual, int Comienzo,  const char *PathReal){
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

std::string EXT::LeerArchivo(int Inicio, const char *Disco, const char *Path){

    int Busqueda=BuscarActual(Inicio,Path,Disco);
    std::string Contenido="";





    if(Busqueda==-1){
        std::cout<<"No Se Encontro El Archivo"<<std::endl;
        return "";
    }else{

        if(TienePermiso(Busqueda,Disco,"100")==false){
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

//Expandir Archivos
void EXT::ExpandirArchivo(SPB *Super, int Comienzo, const char *PathVirtual, const char *PathReal, std::string Contenido){
    int PosArchivo=0;
    PosArchivo=BuscarActual(Comienzo,PathVirtual,PathReal);
    if(PosArchivo==-1){
        std::cout<<"No Se Pudo Agregar Contenido Al Archivo  en"<<PathVirtual<<" En El Disco  Virtual Ubicado En"<<PathReal<<std::endl;
        return ;
    }

    if(TienePermiso(PosArchivo,PathReal,"110")==false){
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
    if(Fun->IF(Retor,"")){
        std::cout<<"Se Modifico El Archivo "<<PathVirtual<<std::endl;
        return ;
    }else{
        std::string Retor=ContenidoArchivoInDirectos(&Inodo,Super,PosArchivo,PathReal,"",Contenido);
    }

    if(Fun->IF(Retor,"")){
        std::cout<<"Se Modifico El Archivo "<<PathVirtual<<std::endl;
        return ;
    }

    std::cout<<" El Archivo Llego A Su Limite"<<std::endl;
}
//REDUCIR TAMANIO String
std::string EXT::ReducirTamanio(std::string *Ingreso, int Num){
    int Longitud=Ingreso->length();
    std::string Copia="";
    if(Longitud>Num){
       Copia=Ingreso->substr(0,Num);
       *Ingreso=Ingreso->substr(Num);
       return Copia;
    }else{
        Copia=*Ingreso;
        *Ingreso="";
        return Copia;
    }
}
std::string EXT::ColocarContenidoArchivo(int PosDirecto, SPB *Super, const char *PathReal, std::string Contenido){
    int Longitud=Contenido.length();
    if(Longitud>64*4){
        std::cout<<"STRING MUY GRANDFEE"<<std::endl;
        return Contenido;
    }

    FILE *f;
    f=fopen(PathReal,"r+");
    fseek(f,PosDirecto,SEEK_SET);
    BCA Directo;
    fread(&Directo,sizeof(Directo),1,f);
    for(int z=0;z<4;z++){
        if(Fun->IF(Contenido,""))
            break;
        int Pos=Directo.content[z].b_inodo;

        if(Pos==-1){

            //Llenar Nombre
            std::string Sub="......";

            strcpy(Directo.content[z].b_name,Sub.c_str());
            //Inodo Nuevo
            //int Libre = BloqueLibre(Super,PathReal);
            int Libre = BloqueLibreConte(Super,PathReal);
            Directo.content[z].b_inodo=Libre;

            //Se Reduce
            std::string ValorBloque=ReducirTamanio(&Contenido,64);
            //Se Coloca Contenido De Archivo
            fseek(f,Libre,SEEK_SET);
            BAR ConteArchivo;
            //std::cout<<"Se Coloco Contenido "<<ValorBloque <<" en "<<Libre <<" BORRAR MENSAJE   "<<z<<std::endl;
            strcpy(ConteArchivo.b_content,ValorBloque.c_str());
            fwrite(&ConteArchivo,sizeof (ConteArchivo),1,f);
            //Se Actualizo El Apuntador Directo
            fseek(f,PosDirecto,SEEK_SET);
            fwrite(&Directo,sizeof (Directo),1,f);




        }else{
            f=fopen(PathReal,"r+");
            BAR Cont;
            fseek(f,Pos,SEEK_SET);
            fread(&Cont,sizeof(Cont),1,f);
            std::string Almacenado=Cont.b_content;
            int Llenar=64-(Almacenado.length());



            if(Llenar>0){
                Almacenado=Almacenado+ReducirTamanio(&Contenido,Llenar);


            strcpy(Cont.b_content,Almacenado.c_str());

            fseek(f,Pos,SEEK_SET);
            fwrite(&Cont,sizeof(Cont),1,f);
            }
        }

    }

    fclose(f);
    //fwrite(&Apuntador,sizeof (Apuntador),1,f);


    return Contenido;
}
std::string EXT::ContenidoArchivoDirectos(INO *Ino, SPB *Super, int PosPadre, const char *PathReal,  std::string Contenido){
    INO Inodo=*Ino;
    for(int i=0;i<12;i++){
        if(Fun->IF(Contenido,""))
            return "";

        int Pos=Inodo.i_block[i];

          if(Pos==-1){
            //Crea Bloque Directo Y Se Manda A Crear Carpeta

            int EspacioBloque=BloqueLibre(Super,PathReal);

            if(EspacioBloque==-1){
                std::cout<<"No Se Pudo Crear El Bloque, Insuficiente Tamanio"<<std::endl;
                return Contenido;
            }
            FILE *f;
            f=fopen(PathReal,"r+");
            BCA BloqueDirecto;
            IniciarBloqueCarpeta(&BloqueDirecto);
            fseek(f,EspacioBloque,SEEK_SET);
            fwrite(&BloqueDirecto,sizeof (BloqueDirecto),1,f);
            Inodo.i_block[i]=EspacioBloque;
            fseek(f,PosPadre,SEEK_SET);
            fwrite(&Inodo,sizeof (Inodo),1,f);
            fclose(f);

            std::string Colocacion="";
            std::string Parametro;
            Parametro=ReducirTamanio(&Contenido,64*4);
            Colocacion=ColocarContenidoArchivo(EspacioBloque,Super,PathReal,Parametro);
            if(!Fun->IF(Colocacion,"")){
                Contenido=Contenido+Parametro;
            }



        }else{
            //Como Posicion Es Valida Se Prueba Colocar Carpeta
            std::string Valor="";
            std::string Parametro;
            Parametro=ReducirTamanio(&Contenido,64*4);
            Valor=ColocarContenidoArchivo(Pos,Super,PathReal,Parametro);
            if(!Fun->IF(Valor,"")){
                Contenido=Contenido+Parametro;
            }
        }
    }
    return Contenido;
}
std::string EXT::ContenidoArchivoInDirectos(INO *Ino, SPB *Super, int PosPadre, const char *PathReal, const char *PathVirtual,  std::string Contenido){
    INO Inodo=*Ino;
    //Posicion De Un Bloque De Directos Con Alguna Ranura
    for(int i=0;i<3;i++){
        if(Fun->IF(Contenido,""))
            return "";

        int Pos=Inodo.i_block[12+i];
        if(Pos==-1){
            //Se Crean Los Bloques Indirectos
            Pos=CrearIndirectos(i+1,0,Super,PathReal);
            if(Pos!=-1 && Pos!=0){
                //Si No Se Puede Crear Retornar
                std::cout<<"Cancelando POR NO PODER CREAR INDIRECTO"<<std::endl;
                return Contenido;
            }else{
                Inodo.i_block[12+i]=Pos;
                //Escribir Inodo Modificado
                FILE *f;
                f=fopen(PathReal,"r+");
                fseek(f,PosPadre,SEEK_SET);
                fwrite(&Inodo,sizeof (Inodo),1,f);
                fclose(f);
            }
        }

        //El Indirecto En La Posicion Pos Si Existe
        int Busqueda=BuscarIndirectos(Super,0,0,Pos,PathVirtual,PathReal,2);
        if(Busqueda!=-1){
            //Bloque Directo Existente
            std::string  Valor;
            std::string Parametro;
            Parametro=ReducirTamanio(&Contenido,64*4);
            Valor=ColocarContenidoArchivo(Pos,Super,PathReal,Parametro);
            if(!Fun->IF(Valor,"")){
                Contenido=Contenido+Parametro;
            }
        }

    }
    return Contenido;
}

int EXT::BuscarActual(int Comienzo, std::string PathVirtual, const char *PathReal){
    PathVirtual=PathVirtual.substr(1);
    int Busq=BuscarPadre(Comienzo,(PathVirtual),PathReal);
    if(Busq==-1)
        return Busq;
    std::string Nombre=NombreACrear(PathVirtual.data());
    FILE *f;
    f=fopen(PathReal,"r+");
    INO Carpeta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);
    int Punteros=-1;

    for(int i=0;i<12;i++){
        int Apuntador=Carpeta.i_block[i];
        if(Apuntador!=-1){
             Punteros=BuscarIndirectos(nullptr,0,0,Apuntador,Nombre,PathReal,3);
             if(Punteros!=-1)
                 return Punteros;
        }
    }
    for(int i=0;i<3;i++){
        int Apuntador=Carpeta.i_block[12+i];
        if(Apuntador!=-1){
            Punteros=BuscarIndirectos(nullptr,1+i,0,Apuntador,Nombre,PathReal,3);
            if(Punteros!=-1)
                return Punteros;
        }
    }



    return  Punteros;
}
void EXT::CantidadVeces(std::string Contenido){
    int Div = int(Contenido.length())/64;
    if(Contenido.length()%64!=0)
        Div++;
    ValTamanio=Div;
}
//CrearArchivo
bool EXT::CrearArchivoCompleto(SPB *Super, int Comienzo, const char *PathVirtual, const char *PathReal, std::string Contenido){
    int PosPadre=0;
    if(Fun->IF(Contenido,"")){
        Contenido=Contenido+" ";
    }
    //CrearCarpetaCompleto(Super,Comienzo,PathVirtual,PathReal);
    std::string CarpetaCrear=PathArchivo(PathVirtual);
    if(CarpetaCrear.length()==0)
        CarpetaCrear=CarpetaCrear+"/";

    CrearCarpetaCompleto(Super,Comienzo,CarpetaCrear.data(),PathReal);

    std::string NombreArchivo=NombreACrear(PathVirtual);
    if(CantidadBarras(PathVirtual)==1){
        PosPadre=Comienzo;
    }else{
        PosPadre=BuscarPadre(Comienzo,PathVirtual,PathReal);
        if(PosPadre==-1){
            std::cout<<"No Se Pudo Crear El Archivo "<<NombreArchivo  <<" En "<<PathVirtual<<" En El Disco Ubicado En"<<PathReal<<std::endl;
            return false;
        }
    }

    if(!TienePermiso(PosPadre,PathReal,"010")==false){
        std::cout<<"No Se Pudo Crear El Archivo "<<NombreArchivo  <<" La Sesion Actual No Tiene Los Permisos Necesarios Para La Ruta"<<PathReal<<std::endl;
        return false;
    }

    std::string NombreCarpeta=NombreACrear(PathVirtual);
    FILE *f;
    f=fopen(PathReal,"r+");
    INO Inodo;
    fseek(f,PosPadre,SEEK_SET);
    fread(&Inodo,sizeof(Inodo),1,f);
    fclose(f);

    int Num=CarpetaArchivoSimpleDirectos(&Inodo,Super,PosPadre,PathReal,NombreCarpeta,Contenido);
    if(Num==-2)
        return false;

    if(Num==1)
        return true;

    if(CarpetaArchivoSimpleInDirectos(&Inodo,Super,PosPadre,PathReal,PathVirtual,NombreCarpeta,Contenido))
        return true;

    return false;
}
bool EXT::CrearArchivoSimple(SPB *Super, int Comienzo, const char *PathVirtual, const char *PathReal, std::string Contenido){
    int PosPadre=0;
    if(Fun->IF(Contenido,"")){
        Contenido=Contenido+" ";
    }
    std::string NombreArchivo=NombreACrear(PathVirtual);
    if(CantidadBarras(PathVirtual)==1){
        PosPadre=Comienzo;
    }else{
        PosPadre=BuscarPadre(Comienzo,PathVirtual,PathReal);
        if(PosPadre==-1){
            std::cout<<"No Se Pudo Crear El Archivo "<<NombreArchivo  <<" En "<<PathVirtual<<" En El Disco Ubicado En"<<PathReal<<std::endl;
            return false;
        }
    }

    if(!TienePermiso(PosPadre,PathReal,"010")){
        std::cout<<"No Se Pudo Crear El Archivo "<<NombreArchivo  <<" La Sesion Actual No Tiene Los Permisos Necesarios Para La Ruta"<<PathReal<<std::endl;
        return false;
    }

    std::string NombreCarpeta=NombreACrear(PathVirtual);
    FILE *f;
    f=fopen(PathReal,"r+");
    INO Inodo;
    fseek(f,PosPadre,SEEK_SET);
    fread(&Inodo,sizeof(Inodo),1,f);
    fclose(f);
    int Num;
    Num=CarpetaArchivoSimpleDirectos(&Inodo,Super,PosPadre,PathReal,NombreCarpeta,Contenido);
    if(Num==1)
        return true;
    if(Num==-2)
        return false;

    if(CarpetaArchivoSimpleInDirectos(&Inodo,Super,PosPadre,PathReal,PathVirtual,NombreCarpeta,Contenido)==1)
        return true;

    return false;
}
//ColocarArchivo
int EXT::ColocarArchivo(std::string NombreCarpeta, int PosDirecto, SPB *Super, const char *PathReal, std::string Contenido){
    FILE *f;
    f=fopen(PathReal,"r+");
    fseek(f,PosDirecto,SEEK_SET);
    BCA Directo;
    fread(&Directo,sizeof(Directo),1,f);
    for(int z=0;z<4;z++){

        int Pos=Directo.content[z].b_inodo;

        if(Pos==-1){

            //Llenar Nombre
            std::string Sub;
            Sub=NombreCarpeta.substr(0,12);
            strcpy(Directo.content[z].b_name,Sub.c_str());
            //Inodo Nuevo
            int Libre = InodoLibre(Super,PathReal);
            Directo.content[z].b_inodo=Libre;

            //Se Coloca Archivo
            fseek(f,Libre,SEEK_SET);
            INO Archivo;
            std::cout<<"Se creo Archivo  "<<NombreCarpeta <<" en "<<Libre <<" PERO FALTA PONERLE PERMISOS Y ESO"<<std::endl;
            IniciarInodo(&Archivo,1,1,0,-1,'0',111111);
            Archivo.i_type='1';
            fwrite(&Archivo,sizeof (Archivo),1,f);
            //Se Actualizo El Apuntador Directo
            fseek(f,PosDirecto,SEEK_SET);
            fwrite(&Directo,sizeof (Directo),1,f);
            fclose(f);

            std::string Retor=ContenidoArchivoDirectos(&Archivo,Super,Libre,PathReal,Contenido);
            if(Fun->IF(Retor,"")){
                return 1;
            }else{
                std::string Retor=ContenidoArchivoInDirectos(&Archivo,Super,Libre,PathReal,"",Contenido);
            }

            if(Fun->IF(Retor,"")){
                return 1;
            }
        }

    }


    return -1;
}
//Cuenta Cuantas '/' Hay en un string
int EXT::CantidadBarras(std::string Path){
    int Contador=0;
    int Longitud=Path.length();
    for(int i=0;i<Longitud;i++){
        if('/'==Path.at(i)){
            Contador++;
        }
    }
    return Contador;
}
std::string EXT::Reducir(std::string *Entrada){

    int Longitud=int(Entrada->length());
    for(int i=0;i<Longitud;i++){
        char Letra=char((*Entrada)[i]);
        if(Letra=='/'){
            std::string  Salida=Entrada->substr(0,i);
            *Entrada=Entrada->substr(i);

            return Salida;
        }
    }
    std::string Salida=*Entrada;
    *Entrada="";
    return Salida;
}
//BSUCA EN EL INODO
int EXT::BuscarInodos(int Comienzo, std::string PathVirtual, const char *PathReal){
    //std::cout<<"InodoPathVirtual"<<"  "<<PathVirtual<<"     "<<Comienzo<<std::endl;

    int Contador=CantidadBarras(PathVirtual);


    FILE *f;
    f=fopen(PathReal,"r+");
    INO Inodo;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Inodo,sizeof(Inodo),1,f);
    fclose(f);






    if(Contador==0){
        return Comienzo;
    }

    if(Inodo.i_type=='1'){

        return Comienzo;
    }
    for(int i=0;i<12;i++){
        int Comprobar=Inodo.i_block[i];



        if(Comprobar!=-1){
            Comprobar =BuscarIndirectos(nullptr,0,0,Comprobar,PathVirtual,PathReal,1);

            if(Comprobar==-2)
                return -2;

            if(Comprobar!=-1){
                //Es El Padre El Inodo Actual
                if(Comprobar==1)
                    return Comienzo;
                else
                  return Comprobar;
            }
        }

    }


    for(int i=0;i<3;i++){
        int Busq=BuscarIndirectos(nullptr,1+i,0,Inodo.i_block[12+i],PathVirtual,PathReal,1);
        if(Busq==-2)
            return -2;

        if(Busq!=-1)
            return Comienzo;
    }

    return -1;
}
int EXT::BuscarDirectos(int Comienzo, std::string PathVirtual, const char *PathReal,int Tipo){


    FILE *f;
    f=fopen(PathReal,"r+");
    BCA Carpeta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);
    std::string NombreTotal =PathVirtual.substr(1);

    std::string NombreActual=Reducir(&NombreTotal);

    for(int i=0;i<4;i++){

        CON Contenido=Carpeta.content[i];

        //std::cout<<PathVirtual<<"  "<<Contenido.b_inodo<<std::endl;

         std::string Nombre=Contenido.b_name;
         Nombre=Nombre.substr(0,12);
       // std::cout<<Nombre<<"----"<<PathVirtual<<"****"<<Comienzo<<"****"<<Contenido.b_inodo<<std::endl;
        if(Tipo==1){
            if(CantidadBarras( PathVirtual)==1){
                return 1;
            }

            if(Fun->IF(Nombre,NombreActual) && Contenido.b_inodo!=-1){
                int Busq=BuscarInodos(Contenido.b_inodo,NombreTotal,PathReal);
                if(Busq==-1 || Busq==-2){

                    return -2;

                }

                return Busq;
            }
        }else if(Tipo==2)
            //Tipo 2 Pra Posocion Del Bloque Directo, Al crear Carpetas
            {
                if(Contenido.b_inodo==-1)
                    return Comienzo;
        }else if(Tipo==3 && Contenido.b_inodo!=-1){

            if(Fun->IF(Nombre,PathVirtual)){

                return Contenido.b_inodo;
            }
        }
    }
    /*if(Tipo==1){

    //Siginifca que el Inodo Anterior Era El Padre
    if(Fun->IF(NombreTotal,""))
        return 1;
    }*/

    return -1;
}
int EXT::BuscarIndirectos(SPB *Super,int Nivel, int NivelActual, int Comienzo, std::string PathVirtual, const char *PathReal,int Tipo){



    if(Nivel==NivelActual){
        return BuscarDirectos(Comienzo,PathVirtual,PathReal,Tipo);
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
            Valor=BuscarIndirectos(Super,Nivel,NivelActual+1,Valor,PathVirtual,PathReal,Tipo);
            if(Valor==-2){
                return -2;
            }

            if(Valor!=-1){
                return Valor;
            }
        }else if(Tipo==2){
            int BloqueDirectoNuevo=BloqueLibre(Super,PathReal);
            FILE *f;
            f=fopen(PathReal,"r+");
            fseek(f,BloqueDirectoNuevo,SEEK_SET);
            BCA BloqueDirecto;
            IniciarBloqueCarpeta(&BloqueDirecto);
            fwrite(&BloqueDirecto,sizeof (BloqueDirecto),1,f);
            fclose(f);
            //Crear El Directo
            return BloqueDirectoNuevo;

        }
    }
    return -1;
}
int EXT::CrearIndirectos(int Nivel, int NivelActual, SPB *Super, const char *PathReal){
    if(Nivel==NivelActual)
        return 0;

    int PosicionPadre=BloqueLibre(Super,PathReal);
    if(PosicionPadre==-1)
        return -1;

    BAP Apuntador;
    for(int i=0;i<16;i++){
         Apuntador.b_pointers[i]=-1;
    }
    for(int i=0;i<16;i++){
        int Hijo=CrearIndirectos(Nivel,NivelActual+1,Super,PathReal);
        if(Hijo==-1){
            std::cout<<" Se Llego Al Limite De Apuntadores "<<std::endl;
            break;
        }else if(Hijo!=0){
            //Posicion De Cada Hijo;
            Apuntador.b_pointers[i]=Hijo;
        }
    }

    FILE *f;
    f=fopen(PathReal,"r+");
    fseek(f,PosicionPadre,SEEK_SET);
    fwrite(&Apuntador,sizeof (Apuntador),1,f);
    fclose(f);
    return PosicionPadre;

}
int EXT::BuscarPadre(int Comienzo, std::string PathVirtual, const char *PathReal){
    int Num=BuscarInodos(Comienzo,PathVirtual,PathReal);
    if(Num==-2){
        std::cout<<"OPTI"<<std::endl;
        return-1;
    }
    return Num;

}
std::string EXT::PathArchivo(const char *PathVirtual){
    std::string s = PathVirtual;
    std::string delimiter = "/";
    size_t pos = 0;
    std::string token;
    std::string Escritura="";
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        if(this->Fun->IF("",token)){

        }else{
        Escritura=Escritura+"/"+token;
        }
        s.erase(0, pos + delimiter.length());
    }

    return Escritura;
}
std::string EXT::NombreACrear(const char *PathVirtual){
    std::string s = PathVirtual;
    std::string delimiter = "/";
    size_t pos = 0;
    std::string token;
    std::string Escritura="";
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        if(this->Fun->IF("",token)){

        }else{
        Escritura=Escritura+"/"+token;
        }
        s.erase(0, pos + delimiter.length());
    }

    return s;
}
//Crear CarpetasYArchivos
int EXT::CarpetaArchivoSimpleDirectos(INO *Ino,SPB *Super,int PosPadre, const char *PathReal ,std::string NombreCarpeta,std::string Contenido){
    INO Inodo=*Ino;    
    FILE *f;
    f=fopen(PathReal,"r+");
    BCA BloqueDirecto;


    for(int i=0;i<12;i++){
        int Pos=Inodo.i_block[i];
        fseek(f,Pos,SEEK_SET);
        fread(&BloqueDirecto,sizeof (BloqueDirecto),1,f);
            for(int j=0;j<4;j++){
                CON Con=BloqueDirecto.content[j];
                if(Fun->IF(NombreCarpeta,Con.b_name)){
                    fclose(f);
                    return -2;
                }
            }


    }
    fclose(f);
    for(int i=0;i<12;i++){
        int Pos=Inodo.i_block[i];

          if(Pos==-1){
            //Crea Bloque Directo Y Se Manda A Crear Carpeta

            int EspacioBloque=BloqueLibre(Super,PathReal);

            if(EspacioBloque==-1){
                std::cout<<"No Se Pudo Crear El Bloque, Insuficiente Tamanio"<<std::endl;
                return -1;
            }
            FILE *f;
            f=fopen(PathReal,"r+");
            BCA BloqueDirecto;
            IniciarBloqueCarpeta(&BloqueDirecto);
            fseek(f,EspacioBloque,SEEK_SET);
            fwrite(&BloqueDirecto,sizeof (BloqueDirecto),1,f);
            Inodo.i_block[i]=EspacioBloque;
            fseek(f,PosPadre,SEEK_SET);
            fwrite(&Inodo,sizeof (Inodo),1,f);
            fclose(f);

            int Colocacion=0;
            if(Fun->IF("",Contenido))
            Colocacion=ColocarCarpeta(NombreCarpeta,EspacioBloque,Super,PathReal);
            else
            Colocacion=ColocarArchivo(NombreCarpeta,EspacioBloque,Super,PathReal,Contenido);


            if(Colocacion!=-1)
                return 1;

        }else{
            //Como Posicion Es Valida Se Prueba Colocar Carpeta
            int Valor=-1;
            if(Fun->IF("",Contenido))
            Valor=ColocarCarpeta(NombreCarpeta,Pos,Super,PathReal);
            else
            Valor=ColocarArchivo(NombreCarpeta,Pos,Super,PathReal,Contenido);


            if(Valor!=-1){
                //Se Creo La Carpeta
                return 1;
            }
        }
    }
    return -1;
}
int EXT::CarpetaArchivoSimpleInDirectos(INO *Ino, SPB *Super, int PosPadre, const char *PathReal,const char *PathVirtual, std::string NombreCarpeta,std::string Contenido){
    INO Inodo=*Ino;
    //Posicion De Un Bloque De Directos Con Alguna Ranura
    for(int i=0;i<3;i++){
        int Pos=Inodo.i_block[12+i];
        if(Pos==-1){
            //Se Crean Los Bloques Indirectos
            Pos=CrearIndirectos(i+1,0,Super,PathReal);
            if(Pos==-1 || Pos==0){
                //Si No Se Puede Crear Retornar
                std::cout<<"Cancelando POR NO PODER CREAR INDIRECTO "<<Pos<<std::endl;
                return -1;
            }else{
                Inodo.i_block[12+i]=Pos;
                //Escribir Inodo Modificado
                FILE *f;
                f=fopen(PathReal,"r+");
                fseek(f,PosPadre,SEEK_SET);
                fwrite(&Inodo,sizeof (Inodo),1,f);
                fclose(f);
            }
        }

        //El Indirecto En La Posicion Pos Si Existe
        int Busqueda=BuscarIndirectos(Super,0,0,Pos,PathVirtual,PathReal,2);
        if(Busqueda!=-1){
            //Bloque Directo Existente
            int Valor=-1;
            if(Fun->IF("",Contenido))
            Valor=ColocarCarpeta(NombreCarpeta,Pos,Super,PathReal);
            else
            Valor=ColocarArchivo(NombreCarpeta,Pos,Super,PathReal,Contenido);
            if(Valor!=-1){
                //Se Creo La Carpeta
                return 1;
            }
        }

    }
    return -1;
}
//CarpetaSimple
bool EXT::CrearCarpetaSimple(SPB *Super,int Comienzo, const char *PathVirtual, const char *PathReal){
    /*if(BuscarActual(Comienzo,PathVirtual,PathReal)!=-1)
        return true;
*/

    int PosPadre=0;
    if(CantidadBarras(PathVirtual)==1){
        PosPadre=Comienzo;
    }else{
        PosPadre=BuscarPadre(Comienzo,PathVirtual,PathReal);
        if(PosPadre==-1){
            std::cout<<"No Se Pudo Crear La Carpeta En "<<PathVirtual<<" En El Disco Ubicado En"<<PathReal<<std::endl;
            return false;
        }
    }

    if(TienePermiso(PosPadre,PathReal,"010")==false){
        std::cout<<"No Se Tiene Permisos Para ESCRIBIR En la Carpeta Padre En '"<<PathVirtual<<"' La Sesion Actual No Tiene Los Permisos Necesarios "<<std::endl;
        return false;
    }

    std::string NombreCarpeta=NombreACrear(PathVirtual);
    FILE *f;
    f=fopen(PathReal,"r+");
    INO Inodo;
    fseek(f,PosPadre,SEEK_SET);
    fread(&Inodo,sizeof(Inodo),1,f);
    fclose(f);
    int Num=CarpetaArchivoSimpleDirectos(&Inodo,Super,PosPadre,PathReal,NombreCarpeta,"");
    if(Num==1)
        return true;
    if(Num==-2)
        return false;

    if(CarpetaArchivoSimpleInDirectos(&Inodo,Super,PosPadre,PathReal,PathVirtual,NombreCarpeta,"")==1)
        return true;
    return false;
}
//CarpetaCompletaUsandoLaSimple
bool EXT::CrearCarpetaCompleto(SPB *Super,int Comienzo, const char *PathVirtual, const char *PathReal){
    std::string s = PathVirtual;
    std::string delimiter = "/";
    size_t pos = 0;
    std::string token;
    std::string Escritura="";   
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        if(this->Fun->IF("",token)){

        }else{
        Escritura=Escritura+"/"+token;
                if(BuscarActual(Comienzo,Escritura.data(),PathReal)==-1){

                    CrearCarpetaSimple(Super,Comienzo,Escritura.data(),PathReal);
                }
        }
        s.erase(0, pos + delimiter.length());
    }
    Escritura=Escritura+"/"+s;
    CrearCarpetaSimple(Super,Comienzo,Escritura.data(),PathReal);

    return true;
}
//ColocarCarpetaEnElBloque
int EXT::ColocarCarpeta(std::string NombreCarpeta,int PosDirecto, SPB *Super, const char *PathReal){
    FILE *f;
    f=fopen(PathReal,"r+");
    fseek(f,PosDirecto,SEEK_SET);
    BCA Directo;
    fread(&Directo,sizeof(Directo),1,f);
    for(int z=0;z<4;z++){

        int Pos=Directo.content[z].b_inodo;

        if(Pos==-1){

            //Llenar Nombre
            std::string Sub;
            Sub=NombreCarpeta.substr(0,12);
            strcpy(Directo.content[z].b_name,Sub.c_str());
            //Inodo Nuevo
            int Libre = InodoLibre(Super,PathReal);
            Directo.content[z].b_inodo=Libre;

            //Se Coloca La Carpeta
            fseek(f,Libre,SEEK_SET);
            INO Carpeta;
            std::cout<<"SE CREO CARPETA  "<<NombreCarpeta <<" EN "<<Libre <<" PERO FALTA PONERLE PERMISOS Y ESO"<<std::endl;
            IniciarInodo(&Carpeta,1,1,0,-1,'0',111111);
            fwrite(&Carpeta,sizeof (Carpeta),1,f);
            //Se Actualizo El Apuntador Directo
            fseek(f,PosDirecto,SEEK_SET);
            fwrite(&Directo,sizeof (Directo),1,f);
            fclose(f);
            return 1;
        }

    }
    //fwrite(&Apuntador,sizeof (Apuntador),1,f);


    return -1;
}


int EXT::InodoLibre(SPB *Super,const char* Path){
    int Out=-1;
    FILE *f;
    f=fopen(Path,"r+");
    int Ubi=Super->s_bm_inode_start;
    int Tamanio=Super->s_inodes_count;
    //Ubicarse En el BM
    fseek(f,Ubi,SEEK_SET);
    char Lectura;
    //std::cout<<"/////////////////////// "<< Super->s_block_start<<std::endl;
    for(int i=0;i<Tamanio;i++){
        fread(&Lectura,sizeof(Lectura),1,f);
        if(Lectura=='0'){
            Out= Super->s_inode_start+(i*Super->s_inode_size);
            fseek(f,Ubi+i,SEEK_SET);
            char Actualizar='1';
            fwrite(&Actualizar,sizeof (Actualizar),1,f);
            break;
        }else if(Lectura!='1'){
            std::cout<<"El Disco En "<<Path<<"Presenta Errores, Se Recomienda Restaurarlo "<<std::endl;
            break;
        }else if(Lectura!='1' && Lectura!='0'){
            std::cout<<"El Disco En "<<Path<<"Presenta Errores, Se Recomienda Restaurarlo '"<<Lectura<<"'"<<std::endl;
            break;
        }
    }
    //std::cout<<"/////////////////////// "<< Super->s_block_start<<std::endl;
    fclose(f);
    return Out;
}
int EXT::BloqueLibre(SPB *Super, const char *Path){
    int Out=-1;
    FILE *f;
    f=fopen(Path,"r+");
    int Ubi=Super->s_bm_block_start;
    int Tamanio=Super->s_blocks_count;
    //Ubicarse En el BM
    fseek(f,Ubi,SEEK_SET);
    char Lectura;



    for(int i=0;i<Tamanio;i++){
        fread(&Lectura,sizeof(Lectura),1,f);
        if(Lectura=='0'){
            //ARREGLAR
            Super->s_block_start= Super->s_inode_start+Super->s_inodes_count*(int(sizeof (INO)));
            //
            Out= Super->s_block_start+(i*Super->s_block_size);
            fseek(f,Ubi+i,SEEK_SET);
            char Actualizar='1';
            fwrite(&Actualizar,sizeof (Actualizar),1,f);


            break;
        }else if(Lectura!='1'){
            std::cout<<"El Disco En "<<Path<<"Presenta Errores, Se Recomienda Restaurarlo "<<std::endl;
            break;
        }else if(Lectura!='1' && Lectura!='0'){
            std::cout<<"El Disco En "<<Path<<"Presenta Errores, Se Recomienda Restaurarlo '"<<Lectura<<"'"<<std::endl;
            break;
        }
    }
    fclose(f);


    return Out;

}
int EXT::BloqueLibreConte(SPB *Super, const char *Path){
    if(ValPrimeraPos==-1){
        int Retorno=DarPrimeraPos(Super,Path);
        //Poner Primera Posicion
        ValPrimeraPos=Retorno;

        if(Retorno==-1){
            std::cout<<"No Hay Espacio Contiguo Para Colocar El Archivo "<<std::endl;
        }else{
            ValTamanio=0;
        }
        return Retorno;
    }
    ValTamanio++;
    return ValPrimeraPos+(ValTamanio)*(int(sizeof (BAR)));
}
int EXT::DarPrimeraPos(SPB *Super, const char *Path){
    int Out=-1;
        FILE *f;
        f=fopen(Path,"r+");
        int Ubi=Super->s_bm_block_start;
        int Tamanio=Super->s_blocks_count;
        //Ubicarse En el BM
        char Lectura;
        int Contador=0;
        for(int i=0;i<Tamanio;i++){
            //Leer Cada Uno
            fseek(f,Ubi+i,SEEK_SET);
            fread(&Lectura,sizeof(Lectura),1,f);
            //Si Libre Sumar 1
            if(Lectura=='0'){
                Contador++;
                //Si Es El Primer '0' Indicar Salida
                if(Contador==1)
                    Out=Super->s_block_start+(i*Super->s_block_size);
                //Si Supera El Espacio Buscado
                if(Contador>=ValTamanio){
                    //Colocar En El Primero
                    Lectura='1';
                    fseek(f,Ubi+i,SEEK_SET);
                    fread(&Lectura,sizeof(Lectura),1,f);
                    break;
                }
            }else{
                //Si Ocupado Reiniciar
                Contador=0;
            }

            //fwrite(&Actualizar,sizeof (Actualizar),1,f);
        }

        fclose(f);

        return Out;
}
int EXT::CalcularCantidad(int Tamanio){

    int PesoEstructuras=0;
    //Tipo  1 EXT2  Tipo 2 EXT3
    PesoEstructuras=4+3*int(sizeof (BCA))+int(sizeof (INO))+int(sizeof (JOR));
    Tamanio = Tamanio-int(sizeof (SPB));
    int Sal=Tamanio/PesoEstructuras;
    //std::cout<<"QQ "<<Tamanio <<"   "<<Tamanio%PesoEstructuras<<std::endl;
    return Sal;
}
SPB EXT::LlenarSuperBloque(int Tipo,int Comienzo,int Cantidad){
    SPB Nuevo;
    //TipoDeFormato
    Nuevo.s_filesystem_type=Tipo;
    //Cantidad Inodos
    Nuevo.s_inodes_count=Cantidad;
    //Cantidad Bloques
    Nuevo.s_blocks_count=Cantidad*3;
    //Cantidad Inodos Libre
    Nuevo.s_free_inodes_count=Cantidad;
    //Cantidad Bloques Libre
    Nuevo.s_free_blocks_count=Cantidad*3;
    //Fecha Montado
    Fun->Fecha(&Nuevo.s_mtime);
    //Fecha Desmontado
    Fun->Fecha(&Nuevo.s_umtime);
    //VecesMontado
    Nuevo.s_mnt_count=0;
    //NumeroMagico
    Nuevo.s_magic=0xEF53;
    //Tamaño Inodo
    Nuevo.s_inode_size=int(sizeof (INO));
    //Tamaño Bloque
    Nuevo.s_block_size=int(sizeof (BAP));
    //Primer Inodo Libre
    //Primer Bloque Libre
    //Inicio BMInodo
    Nuevo.s_bm_inode_start=Comienzo+int(sizeof (SPB))+Cantidad*int(sizeof (JOR));
    //Inicio BMBloque
    Nuevo.s_bm_block_start=Nuevo.s_bm_inode_start+Cantidad;
    //Inicio Inodo
    Nuevo.s_inode_start=Nuevo.s_bm_block_start+Cantidad*3;
    Nuevo.s_first_ino=Nuevo.s_inode_start;
    //Inicio Bloque
    Nuevo.s_block_start= Nuevo.s_inode_start+Cantidad*(int(sizeof (INO)));
    Nuevo.s_first_blo=Nuevo.s_block_start;
    return Nuevo;
}
void EXT::EstructurarFormatoEXT3(int ComienzoParticion, int TamanioParticion, int TamanioStruct, std::string Direcc,int Tipo){
    const char*Path =Direcc.data();
    int Cantidad= CalcularCantidad(TamanioParticion);
    int ComienzoEscritura=ComienzoParticion+TamanioStruct;
    //Tipo 1 EXT2

    SPB Super=LlenarSuperBloque(1,ComienzoEscritura,Cantidad);

    FILE *f;
    f=fopen(Path,"r+");
    fseek(f,ComienzoEscritura,SEEK_SET);
    //Escribir El Super Bloque
    fwrite(&Super,sizeof (SPB),1,f);
    fclose(f);
    //Llenar BitmapInodo

    //std::cout<<ComienzoEscritura+sizeof (SPB)<<"--------"<<Super.s_bm_inode_start<<std::endl;




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

    CrearArchivoSimple(&Super,PrimerInodo,"/users.txt",Path,"1,G,root\n1,U,root,root,123\n");
    Recuperacion *Recu= new Recuperacion();
    if(Tipo==1)
    Recu->IniciarJOUR(ComienzoEscritura,Path);
}
void EXT::IniciarBloqueCarpeta(BCA *Bloque){
    for(int i=0;i<4;i++){
        Bloque->content[i].b_inodo=-1;
        for(int j=0;j<12;j++){
        Bloque->content[i].b_name[j]='*';
        }
    }
}
void EXT::IniciarInodo(INO *Inodo, int i_uid, int i_gid, int i_size, int PrimerBloque, char Tipo,int Perm){
    Inodo->i_uid=i_uid;
    Inodo->i_gid=i_gid;
    Inodo->i_size=i_size;
    Fun->Fecha(&Inodo->i_atime);
    Fun->Fecha(&Inodo->i_ctime);
    Fun->Fecha(&Inodo->i_mtime);
    Inodo->i_block[0]=PrimerBloque;
    for(int i=1;i<15;i++){
        Inodo->i_block[i]=-1;
    }
    Inodo->i_type=Tipo;
    Inodo->i_perm=2110110010;
}



void EXT::LlenarVacio(int Begin, int Size, char Character,const char *Path){
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
EXT::EXT(IUG Permiso)
{
 this->Permiso=Permiso;
 Fun=new Functions();
}
