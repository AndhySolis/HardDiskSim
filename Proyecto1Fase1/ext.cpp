#include "ext.h"
#include "structsext.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

/*
 * AL COLOCAR ARCHIVOS,ARCHIVO CONTENIDO Y CARPETAS FALTA COMPROBACION SI SE ACABARON LOS ESOACIOS PARA BLOQUES INODOS
*/
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
        return true;
    }else{
        std::cout<<"No Se Pudo Eliminar"<<PathVirtual<<std::endl;
        return  false;
    }

}
void EXT::LiberarInodo(SPB *Super, const char *PathReal, int Comienzo){}
void EXT::LiberarBloque(SPB *Super, const char *PathReal,int Comienzo){}
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
        std::cout<<" No Se Encontro El Archivo"<<std::endl;
        return "";
    }else{
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
            int Libre = InodoLibre(Super,PathReal);
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
//CrearArchivo
bool EXT::CrearArchivoCompleto(SPB *Super, int Comienzo, const char *PathVirtual, const char *PathReal, std::string Contenido){

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

    std::string NombreCarpeta=NombreACrear(PathVirtual);
    FILE *f;
    f=fopen(PathReal,"r+");
    INO Inodo;
    fseek(f,PosPadre,SEEK_SET);
    fread(&Inodo,sizeof(Inodo),1,f);
    fclose(f);

    if(CarpetaArchivoSimpleDirectos(&Inodo,Super,PosPadre,PathReal,NombreCarpeta,Contenido))
        return true;

    if(CarpetaArchivoSimpleInDirectos(&Inodo,Super,PosPadre,PathReal,PathVirtual,NombreCarpeta,Contenido))
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





    if(Inodo.i_type=='1'){

        return Comienzo;
    }
    if(Contador==0){
        return Comienzo;
    }

    for(int i=0;i<12;i++){
        int Comprobar=Inodo.i_block[i];
        if(Comprobar!=-1){
            Comprobar =BuscarIndirectos(nullptr,0,0,Comprobar,PathVirtual,PathReal,1);
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

    if(BuscarIndirectos(nullptr,1+i,0,Inodo.i_block[12+i],PathVirtual,PathReal,1)!=-1)
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
                return BuscarInodos(Contenido.b_inodo,NombreTotal,PathReal);
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
    return BuscarInodos(Comienzo,PathVirtual,PathReal);

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
bool EXT::CarpetaArchivoSimpleDirectos(INO *Ino,SPB *Super,int PosPadre, const char *PathReal ,std::string NombreCarpeta,std::string Contenido){
    INO Inodo=*Ino;
    for(int i=0;i<12;i++){
        int Pos=Inodo.i_block[i];

          if(Pos==-1){
            //Crea Bloque Directo Y Se Manda A Crear Carpeta

            int EspacioBloque=BloqueLibre(Super,PathReal);

            if(EspacioBloque==-1){
                std::cout<<"No Se Pudo Crear El Bloque, Insuficiente Tamanio"<<std::endl;
                return false;
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
                return true;

        }else{
            //Como Posicion Es Valida Se Prueba Colocar Carpeta
            int Valor=-1;
            if(Fun->IF("",Contenido))
            Valor=ColocarCarpeta(NombreCarpeta,Pos,Super,PathReal);
            else
            Valor=ColocarArchivo(NombreCarpeta,Pos,Super,PathReal,Contenido);


            if(Valor!=-1){
                //Se Creo La Carpeta
                return true;
            }
        }
    }
    return false;
}
bool EXT::CarpetaArchivoSimpleInDirectos(INO *Ino, SPB *Super, int PosPadre, const char *PathReal,const char *PathVirtual, std::string NombreCarpeta,std::string Contenido){
    INO Inodo=*Ino;
    //Posicion De Un Bloque De Directos Con Alguna Ranura
    for(int i=0;i<3;i++){
        int Pos=Inodo.i_block[12+i];
        if(Pos==-1){
            //Se Crean Los Bloques Indirectos
            Pos=CrearIndirectos(i+1,0,Super,PathReal);
            if(Pos!=-1 && Pos!=0){
                //Si No Se Puede Crear Retornar
                std::cout<<"Cancelando POR NO PODER CREAR INDIRECTO"<<std::endl;
                return false;
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
                return true;
            }
        }

    }
    return false;
}
//CarpetaSimple
bool EXT::CrearCarpetaSimple(SPB *Super,int Comienzo, const char *PathVirtual, const char *PathReal){
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
    std::string NombreCarpeta=NombreACrear(PathVirtual);
    FILE *f;
    f=fopen(PathReal,"r+");
    INO Inodo;
    fseek(f,PosPadre,SEEK_SET);
    fread(&Inodo,sizeof(Inodo),1,f);
    fclose(f);

    if(CarpetaArchivoSimpleDirectos(&Inodo,Super,PosPadre,PathReal,NombreCarpeta,""))
        return true;

    if(CarpetaArchivoSimpleInDirectos(&Inodo,Super,PosPadre,PathReal,PathVirtual,NombreCarpeta,""))
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
        CrearCarpetaSimple(Super,Comienzo,Escritura.data(),PathReal);
        }
        s.erase(0, pos + delimiter.length());
    }
    Escritura=Escritura+"/"+s;
    CrearCarpetaSimple(Super,Comienzo,Escritura.data(),PathReal);
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
int EXT::CalcularCantidad(int Tamanio,int Tipo){

    int PesoEstructuras=0;
    //Tipo  1 EXT2  Tipo 2 EXT3
    if(Tipo==1)
      PesoEstructuras=4+3*int(sizeof (BCA))+int(sizeof (INO));
    else
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
    if(Tipo==1)
    Nuevo.s_bm_inode_start=Comienzo+int(sizeof (SPB))+4;
    else
    Nuevo.s_bm_inode_start=Comienzo+int(sizeof (SPB))+Cantidad*int(sizeof (JOR))+4;
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
void EXT::EstructurarFormatoEXT2(int ComienzoParticion, int TamanioParticion, int TamanioStruct, std::string Direcc){
    const char*Path =Direcc.data();
    int Cantidad= CalcularCantidad(TamanioParticion,1);
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
    Inodo->i_perm=Perm;
}

void EXT::EstructurarFormatoEXT3(int ComienzoParticion, int TamanioParticion, int TamanioStruct, std::string Direcc){


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
EXT::EXT()
{
 Fun=new Functions();
}
