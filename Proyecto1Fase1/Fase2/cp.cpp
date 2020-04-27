#include "cp.h"
#include "mkfile_mkdir.h"
#include "cat.h"
CP::CP(SPB *Super,int Comienzo,std::string PathVirtualOrigen,const char *PathReal,std::string PathVirtualDestino,IUG Permiso)
{
    this->Permiso=Permiso;
    CopiarCarpetaArchivo(Super,Comienzo,PathVirtualOrigen,PathReal,PathVirtualDestino);
}

//Copiar
void CP::CopiarCarpetaArchivo(SPB *Super,int Comienzo, std::string PathVirtualOrigen, const char *PathReal, std::string PathVirtualDestino){

    int Actual=BuscarActual(Comienzo,PathVirtualOrigen,PathReal);
    if(Actual==-1){
        std::cout<<"No Se Puede Copiar, Porque No Se Encontro La Carpeta/Archivo De ORIGEN  "<<PathVirtualOrigen<<std::endl;
        return;
    }
    int NuevoPadre=BuscarActual(Comienzo,PathVirtualDestino,PathReal);
    if(NuevoPadre==-1){
        std::cout<<"No Se Puede Copiar, Porque No Se Encontro La Carpeta/Archivo De DESTINO  "<<PathVirtualOrigen<<std::endl;
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
    INO CarpetaPadre;//Leyendo Nuevo Padre
    fseek(f,NuevoPadre,SEEK_SET);
    fread(&CarpetaPadre,sizeof(CarpetaPadre),1,f);
    fclose(f);

    for(long i=0;i<12;i++){
        long Pos=CarpetaPadre.i_block[i];
          if(Pos==-1){
            //Crea Bloque Directo Y Se Manda A Crear Carpeta
            long EspacioBloque=BloqueLibre(Super,PathReal);
            if(EspacioBloque==-1){
                std::cout<<"No Se Pudo Crear El Bloque, Insuficiente Tamanio"<<std::endl;
                return ;
            }
            f=fopen(PathReal,"r+");
            BCA BloqueDirecto;
            IniciarBloqueCarpeta(&BloqueDirecto);
            BloqueDirecto.content[0].b_inodo=Actual;
            strcpy(BloqueDirecto.content[0].b_name,NombreACrear(PathVirtualOrigen.data()).c_str());
            fseek(f,EspacioBloque,SEEK_SET);
            fwrite(&BloqueDirecto,sizeof (BloqueDirecto),1,f);
            CarpetaPadre.i_block[i]=EspacioBloque;
            fseek(f,NuevoPadre,SEEK_SET);
            fwrite(&CarpetaPadre,sizeof (INO),1,f);
            fclose(f);
            std::cout<<"Copia Colocada Exitosamente En: "<<Actual<<PathVirtualDestino<<std::endl;
            return;
        }else{


              f=fopen(PathReal,"r+");
              BCA BloqueDirecto;
              fseek(f,Pos,SEEK_SET);
              fread(&BloqueDirecto,sizeof (BloqueDirecto),1,f);
              fclose(f);


              for(int z=0;z<4;z++){
                  Contennt Nido=BloqueDirecto.content[z];
                  std::string Name="";

                  for(int l=0;l<12;l++){
                      if(Nido.b_name[l]=='*'){

                          break;
                      }
                      Name=Name+Nido.b_name[l];
                  }


                  if(IF(Name,NombreACrear(PathVirtualOrigen.data()))){
                      std::cout<<"La Ruta Destino Contiene Un Archivo Con El Mismo Nombre, Cancelando"<<std::endl;
                      return;
                  }

                  if(Nido.b_inodo==-1){

                      BloqueDirecto.content[z].b_inodo=Actual;
                      strcpy(BloqueDirecto.content[z].b_name,NombreACrear(PathVirtualOrigen.data()).c_str());
                      f=fopen(PathReal,"r+");
                      fseek(f,Pos,SEEK_SET);
                      fwrite(&BloqueDirecto,sizeof (BloqueDirecto),1,f);
                      fclose(f);
                      std::cout<<"Copia Colocada Exitosamente En: "<<PathVirtualDestino<<std::endl;
                      return;
                  }


              }

        }
    }

//Indirectos

return;
    for(long i=0;i<3;i++){
        long PosInd=CarpetaPadre.i_block[12+i];
        if(PosInd==-1){
            //Se Crean Los Bloques Indirectos

            PosInd=CrearIndirectosContenido(i+1,0,Super,PathReal,0);


            std::cout<<"Creando Indirectos      "<<PosInd<<std::endl;
            if(PosInd==-1 || PosInd==0){
                //Si No Se Puede Crear Retornar
                std::cout<<"Cancelando POR NO PODER CREAR INDIRECTO "<<PosInd<<std::endl;
                return ;
            }else{
                CarpetaPadre.i_block[12+i]=PosInd;
                //Escribir Inodo Modificado
                FILE *f;
                f=fopen(PathReal,"r+");
                fseek(f,NuevoPadre,SEEK_SET);
                fwrite(&CarpetaPadre,sizeof (CarpetaPadre),1,f);
                fclose(f);
            }
        }

        //El Indirecto En La Posicion Pos Si Existe
        long Busqueda=BuscarIndirectos(Super,i+1,0,PosInd,PathVirtualDestino,PathReal,4);
        if(Busqueda!=-1){
            f=fopen(PathReal,"r+");
            BCA BloqueDirecto;
            fseek(f,Busqueda,SEEK_SET);
            fread(&BloqueDirecto,sizeof (BloqueDirecto),1,f);
            fclose(f);


            for(int z=0;z<4;z++){
                Contennt Nido=BloqueDirecto.content[z];
                std::string Name="";

                for(int l=0;l<12;l++){
                    if(Nido.b_name[l]=='*'){

                        break;
                    }
                    Name=Name+Nido.b_name[l];
                }


                if(IF(Name,NombreACrear(PathVirtualOrigen.data()))){
                    std::cout<<"La Ruta Destino Contiene Un Archivo Con El Mismo Nombre, Cancelando"<<std::endl;
                    return;
                }

                if(Nido.b_inodo==-1){

                    BloqueDirecto.content[z].b_inodo=Actual;
                    strcpy(BloqueDirecto.content[z].b_name,NombreACrear(PathVirtualOrigen.data()).c_str());
                    f=fopen(PathReal,"r+");
                    fseek(f,Busqueda,SEEK_SET);
                    fwrite(&BloqueDirecto,sizeof (BloqueDirecto),1,f);
                    fclose(f);
                    std::cout<<"Copia Colocada Exitosamente En: "<<PathVirtualDestino<<std::endl;
                    return;
                }


            }
        }

    }


std::cout<<"No Se Pudo Copiar El Archivo:  "<<PathVirtualOrigen<<std::endl;



}
int CP::CopiarContenido(SPB *Super,int Comienzo, const char *PathReal){
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
int CP::CopiarDirectos(SPB *Super,int Comienzo, const char *PathReal,int Tipo){
    FILE *f;
    f=fopen(PathReal,"r+");
    BCA Carpeta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);

    BCA CopiaDir;
    IniciarBloqueCarpeta(&CopiaDir);

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
int CP::CopiarIndirectos(SPB *Super,int Nivel, int NivelActual, int Comienzo,  const char *PathReal,int Tipo){
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
        CopiaPtr.b_pointers[i]=-1;
    }


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
int CP::CopiarInodo(SPB *Super,int Comienzo, const char *PathReal){
    if(TienePermiso(Comienzo,PathReal,"100",Permiso)==false){
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
            CopiaCarpeta.i_block[i+12]=CopiarIndirectos(Super,1+i,0,Apuntador,PathReal,Tipo);
        }else{
            CopiaCarpeta.i_block[i+12]=-1;
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
