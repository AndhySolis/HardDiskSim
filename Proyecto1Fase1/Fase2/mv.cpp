#include "mv.h"

MV::MV(IUG Permiso,SPB *Super,int Comienzo,std::string PathVirtualOrigen,const char *PathReal,std::string PathVirtualDestino)
{
    this->Permiso=Permiso;
    MoverCarpetaArchivo(Super,Comienzo,PathVirtualOrigen,PathReal,PathVirtualDestino);
}

//Mover
void MV::MoverCarpetaArchivo(SPB *Super, int Comienzo, std::string PathVirtualOrigen, const char *PathReal, std::string PathVirtualDestino){
    int Existe=BuscarActual(Comienzo,PathVirtualOrigen,PathReal);
    //Buscar Que Exista
    if(Existe==-1){
        std::cout<<"El Archivo/Carpeta No Existe En La Ruta De Origen"<<PathVirtualOrigen<<std::endl;
        return;
    }

    //Borrar Del Padre
    EliminarArchivoCarpetaPadre(Super,Comienzo,PathVirtualOrigen.data(),PathReal,Existe);





    int NuevoPadre=BuscarActual(Comienzo,PathVirtualDestino,PathReal);
    if(NuevoPadre==-1){
        std::cout<<"No Se Puede Copiar, Porque No Se Encontro La Carpeta/Archivo De DESTINO  "<<PathVirtualOrigen<<std::endl;
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
            BloqueDirecto.content[0].b_inodo=Existe;
            strcpy(BloqueDirecto.content[0].b_name,NombreACrear(PathVirtualOrigen.data()).c_str());
            fseek(f,EspacioBloque,SEEK_SET);
            fwrite(&BloqueDirecto,sizeof (BloqueDirecto),1,f);
            CarpetaPadre.i_block[i]=EspacioBloque;
            fseek(f,NuevoPadre,SEEK_SET);
            fwrite(&CarpetaPadre,sizeof (INO),1,f);
            fclose(f);
            std::cout<<"Copia Colocada Exitosamente En: "<<PathVirtualDestino<<std::endl;
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

                      BloqueDirecto.content[z].b_inodo=Existe;
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

                    BloqueDirecto.content[z].b_inodo=Existe;
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
