#include "functionsext.h"
#include <qstring.h>
FunctionsExt::FunctionsExt()
{

}

//

long FunctionsExt::InodoLibre(SPB *Super,const char* Path){
    long Out=-1;
    FILE *f;
    f=fopen(Path,"r+");
    long Ubi=Super->s_bm_inode_start;
    long Tamanio=Super->s_inodes_count;
    //Ubicarse En el BM
    fseek(f,Ubi,SEEK_SET);
    char Lectura;
    //std::cout<<"/////////////////////// "<< Super->s_block_start<<std::endl;
    for(long i=0;i<Tamanio;i++){
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
long FunctionsExt::BloqueLibre(SPB *Super, const char *Path){
    long Out=-1;
    FILE *f;
    f=fopen(Path,"r+");
    long Ubi=Super->s_bm_block_start;
    long Tamanio=Super->s_blocks_count;
    //Ubicarse En el BM
    fseek(f,Ubi,SEEK_SET);
    char Lectura;



    for(long i=0;i<Tamanio;i++){
        fread(&Lectura,sizeof(Lectura),1,f);
        if(Lectura=='0'){
            //ARREGLAR
            Super->s_block_start= Super->s_inode_start+Super->s_inodes_count*(long(sizeof (INO)));
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
long FunctionsExt::BloqueLibreConte(SPB *Super, const char *Path){
    /*if(ValPrimeraPos==-1){
        long Retorno=DarPrimeraPos(Super,Path);
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
    return ValPrimeraPos+(ValTamanio)*(long(sizeof (BAR)));*/
    return BloqueLibre(Super,Path);
}
long FunctionsExt::DarPrimeraPos(SPB *Super, const char *Path){
    long Out=-1;
        FILE *f;
        f=fopen(Path,"r+");
        long Ubi=Super->s_bm_block_start;
        long Tamanio=Super->s_blocks_count;
        //Ubicarse En el BM
        char Lectura;
        long Contador=0;
        for(long i=0;i<Tamanio;i++){
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

//DEL
bool FunctionsExt::EliminarDirectos(SPB *Super,long Comienzo, const char *PathReal, long Tipo, long Elim){
    FILE *f;
    f=fopen(PathReal,"r+");
    BCA Carpeta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);
    std::string Concatenar="";
    for(long i=0;i<4;i++){
        CON Contenido=Carpeta.content[i];

        if(Contenido.b_inodo!=-1){
            if(Contenido.b_inodo==Elim && Tipo ==4){
            //if(Tipo ==4){
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
bool FunctionsExt::EliminarBloqueContenido(SPB *Super,long Comienzo,const char *PathReal){
    LiberarBloque(Super,PathReal,Comienzo);
    return true;
}
bool FunctionsExt::EliminarIndirectos(SPB *Super,long Nivel, long NivelActual, long Comienzo,  const char *PathReal, long Tipo, long Elim){
    if(Nivel==NivelActual){
        return EliminarDirectos(Super,Comienzo,PathReal,Tipo,Elim);
    }
    FILE *f;
    f=fopen(PathReal,"r+");
    BAP Apunta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Apunta,sizeof(Apunta),1,f);
    fclose(f);
    for(long i=0;i<16;i++){
        long Valor=Apunta.b_pointers[i];
        if(Valor!=-1){
            EliminarIndirectos(Super,Nivel,NivelActual+1,Valor,PathReal,Tipo,Elim);
        }
    }
    if(Tipo!=4)
    LiberarBloque(Super,PathReal,Comienzo);

    return true;
}
bool FunctionsExt::EliminarInodo(SPB *Super,long Comienzo, const char *PathReal){
    FILE *f;
    f=fopen(PathReal,"r+");
    INO Carpeta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);
    long Tipo=0;
    if(Carpeta.i_type=='1')
        Tipo=1;
    for(long i=0;i<12;i++){
        long Apuntador=Carpeta.i_block[i];
        if(Apuntador!=-1){
            EliminarIndirectos(Super,0,0,Apuntador,PathReal,Tipo,10);
        }
    }

    for(long i=0;i<3;i++){
        long Apuntador=Carpeta.i_block[i+12];
        if(Apuntador!=-1){
            EliminarIndirectos(Super,1+i,0,Apuntador,PathReal,Tipo,10);
        }
    }

    LiberarInodo(Super,PathReal,Comienzo);
    return true;
}

//Eliminar Archivo
bool FunctionsExt::EliminarArchivoCarpetaPadre(SPB *Super, long Comienzo, const char *PathVirtual, const char *PathReal, long Hijo){
    long Actual=BuscarPadre(Comienzo,PathVirtual,PathReal);
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
    for(long i=0;i<12;i++){
        long Apuntador=Carpeta.i_block[i];
        if(Apuntador!=-1){
            Retorno=EliminarIndirectos(Super,0,0,Apuntador,PathReal,4,Hijo);
            if(Retorno)
                return  true;
        }
    }

    for(long i=0;i<3;i++){
        long Apuntador=Carpeta.i_block[i+12];
        if(Apuntador!=-1){
            Retorno=EliminarIndirectos(Super,1+i,0,Apuntador,PathReal,4,Hijo);
            if(Retorno)
                return  true;
        }
    }

    return false;
}
//Aux
void FunctionsExt::DuplicarInodo(INO *Original, INO *Copia){
    Copia->i_gid=Original->i_gid;
    Copia->i_uid=Original->i_uid;
    Copia->i_perm=Original->i_perm;
    Copia->i_size=Original->i_size;
    Copia->i_type=Original->i_type;
    Copia->i_atime=Original->i_atime;
    Copia->i_ctime=Original->i_ctime;
    Copia->i_mtime=Original->i_mtime;
    for(int i=0;i<16;i++){
        Copia->i_block[i]=-1;
    }
}
void FunctionsExt::CantidadVeces(std::string Contenido){
    long Div = long(Contenido.length())/64;
    if(Contenido.length()%64!=0)
        Div++;
      ValTamanio=Div;
}


//Contenido
//
std::string FunctionsExt::ContenidoArchivoDirectos(INO *Ino, SPB *Super, long PosPadre, const char *PathReal,  std::string Contenido){
    INO Inodo=*Ino;
    for(long i=0;i<12;i++){
        if(IF(Contenido,""))
            return "";

        long Pos=Inodo.i_block[i];

          if(Pos==-1){
            //Crea Bloque Directo Y Se Manda A Crear Carpeta

            long EspacioBloque=BloqueLibre(Super,PathReal);

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
            if(!IF(Colocacion,"")){
                Contenido=Contenido+Parametro;
            }



        }else{
            //Como Posicion Es Valida Se Prueba Colocar Carpeta
            std::string Valor="";
            std::string Parametro;
            Parametro=ReducirTamanio(&Contenido,64*4);
            Valor=ColocarContenidoArchivo(Pos,Super,PathReal,Parametro);
            if(!IF(Valor,"")){
                Contenido=Contenido+Parametro;
            }
        }
    }






    return Contenido;
}
std::string FunctionsExt::ContenidoArchivoInDirectos(INO *Ino, SPB *Super, long PosPadre, const char *PathReal, const char *PathVirtual,  std::string Contenido){
    INO Inodo=*Ino;
    FILE *f;
    f=fopen(PathReal,"r+");
    fseek(f,PosPadre,SEEK_SET);
    fread(&Inodo,sizeof (Inodo),1,f);
    fclose(f);



    //Posicion De Un Bloque De Directos Con Alguna Ranura
    for(long i=0;i<3;i++){


        long Pos=Inodo.i_block[12+i];
        if(Pos==-1){
            //Se Crean Los Bloques Indirectos
            Pos=CrearIndirectosContenido(i+1,0,Super,PathReal,0);
            if(Pos==-1 || Pos==0){
                //Si No Se Puede Crear Retornar
                std::cout<<"Cancelando Colocacion POR NO PODER CREAR INDIRECTO      "<<Pos <<std::endl;
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
        long Busqueda=0;


        while (IF(Contenido,"")==false && Busqueda!=-1) {

        Busqueda=BuscarIndirectos(Super,i+1,0,Pos,PathVirtual,PathReal,4);


        if(Busqueda!=-1){
            //Bloque Directo Existente
            std::string  Valor;
            std::string Parametro;


            Parametro=ReducirTamanio(&Contenido,64*4);




            Valor=ColocarContenidoArchivo(Busqueda,Super,PathReal,Parametro);
            if(!IF(Valor,"")){
                Contenido=Contenido+Parametro;
            }
        }
       }

        if(IF(Contenido,""))
            return "";

    }



    return Contenido;
}
//Liberar
void FunctionsExt::LiberarInodo(SPB *Super, const char *PathReal, long Comienzo){
    FILE *f;
    f=fopen(PathReal,"r+");
    char Actual='0';
    long See=Super->s_bm_inode_start+(Comienzo-Super->s_inode_start)/Super->s_inode_size;
    fseek(f,See,SEEK_SET);
    fwrite(&Actual,sizeof(Actual),1,f);
    fclose(f);
}
void FunctionsExt::LiberarBloque(SPB *Super, const char *PathReal,long Comienzo){
    FILE *f;
    f=fopen(PathReal,"r+");
    char Actual='0';
    long See=Super->s_bm_block_start+(Comienzo-Super->s_block_start)/Super->s_block_size;
    fseek(f,See,SEEK_SET);
    fwrite(&Actual,sizeof(Actual),1,f);
    fclose(f);

}
//Busqueda
long FunctionsExt::BuscarPadre(long Comienzo, std::string PathVirtual, const char *PathReal){
    std::cout<<PathVirtual<<std::endl;

    if(IF(PathVirtual,"/") || CantidadBarras(PathVirtual)==1 || CantidadBarras(PathVirtual)==0)
        return Comienzo;

    long Num=BuscarInodos(Comienzo,PathVirtual,PathReal);
    if(Num==-2){

        //std::cout<<"OPTI"<<std::endl;
        return-1;
    }
    return Num;

}
//BSUCA EN EL INODO
long FunctionsExt::BuscarInodos(long Comienzo, std::string PathVirtual, const char *PathReal){


    long Contador=CantidadBarras(PathVirtual);

    FILE *f;
    f=fopen(PathReal,"r+");
    INO Inodo;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Inodo,sizeof(Inodo),1,f);
    fclose(f);






    if(Contador==1){
        return Comienzo;
    }

    if(Inodo.i_type=='1'){

        return Comienzo;
    }
    for(long i=0;i<12;i++){
        long Comprobar=Inodo.i_block[i];



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


    for(long i=0;i<3;i++){
        if(Inodo.i_block[12+i]!=-1){

            long Busq=BuscarIndirectos(nullptr,1+i,0,Inodo.i_block[12+i],PathVirtual,PathReal,1);
            //std::cout<<"Comprobar "<<Busq<<"        "<<"        "<<PathVirtual<<std::endl;

            if(Busq==-2)
                return -2;

            if(Busq!=-1)
                return Busq;
        }
    }

    return -1;
}
long BloqueContenidoArchivo(long Comienzo ,const char *PathReal){
    FILE *f;
    f=fopen(PathReal,"r+");
    BCA Carpeta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);



    for(long i=0;i<4;i++){
        CON Conten=Carpeta.content[i];
        if(Conten.b_inodo==-1){
            //std::cout<<Comienzo<<std::endl;
            return Comienzo;
        }
    }


    return -1;
}

long FunctionsExt::CrearIndirectosContenido(long Nivel, long NivelActual, SPB *Super, const char *PathReal,int Comienzo){
    BAP Apuntador;
    for(long i=0;i<16;i++){
         Apuntador.b_pointers[i]=-1;
    }

    if(Nivel==NivelActual){
        //ARREGLAR  crear directos
        long Actual=BloqueLibre(Super,PathReal);

        //std::cout<<"Function BORRAR     "<<Actual<<std::endl;
        FILE *f;
        BCA Carpeta;
        IniciarBloqueCarpeta(&Carpeta);

        f=fopen(PathReal,"r+");
        //Actualizar Indirecto
        fseek(f,Actual,SEEK_SET);
        fwrite(&Carpeta,sizeof (Carpeta),1,f);
        //Actualizar Indirecto
        fclose(f);
        return Actual;
    }
    long PosicionPadre=BloqueLibre(Super,PathReal);
    if(PosicionPadre==-1){
        std::cout<<"No Se Puedo Encontrar Un Bloque Libre"<<std::endl;
        return -1;
    }

    for(long i=0;i<16;i++){
        long Hijo=CrearIndirectosContenido(Nivel,NivelActual+1,Super,PathReal,0);
        if(Hijo==-1){
            std::cout<<" Se Llego Al Limite De Apuntadores "<<std::endl;
            break;
        }else if(Hijo!=0){
            //Posicion De Cada Hijo;
            //std::cout<<" Hola "<<Hijo<<std::endl;
            Apuntador.b_pointers[i]=Hijo;

            FILE *f;
            f=fopen(PathReal,"r+");
            fseek(f,PosicionPadre,SEEK_SET);
            fwrite(&Apuntador,sizeof (Apuntador),1,f);
            fclose(f);

            return PosicionPadre;
        }
    }


    return -1;

}
long FunctionsExt::BuscarDirectos(long Comienzo, std::string PathVirtual, const char *PathReal,long Tipo){
    if(Tipo==4)//Contenido De Archivos
        return BloqueContenidoArchivo(Comienzo,PathReal);

    FILE *f;
    f=fopen(PathReal,"r+");
    BCA Carpeta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);



    std::string NombreTotal =PathVirtual.substr(1);

    std::string NombreActual=Reducir(&NombreTotal);

    for(long i=0;i<4;i++){

        CON Contenido=Carpeta.content[i];

        //std::cout<<PathVirtual<<"  "<<Contenido.b_inodo<<std::endl;

        std::string Nombre=Contenido.b_name;
        Nombre=Nombre.substr(0,12);


        if(Tipo==1){
            if(CantidadBarras(PathVirtual)==1){
                return 1;
            }

            if(Contenido.b_inodo!=-1&&IF(Nombre,NombreActual) ){
                long Busq=BuscarInodos(Contenido.b_inodo,NombreTotal,PathReal);
                 //std::cout<<Nombre<<"----"<<NombreTotal<<"****"<<Comienzo<<"****"<<Contenido.b_inodo<<std::endl;
                if(Busq==-1 || Busq==-2){

                    return -2;

                }

                return Busq;
            }
        }else if(Tipo==2)
            //Tipo 2 Pra Posocion Del Bloque Directo, Al crear Carpetas
        {
            if(Contenido.b_inodo==-1){

                return Comienzo;

             }
        }else if(Tipo==3 && Contenido.b_inodo!=-1){//Tipo 3

            if(IF(Nombre,PathVirtual)){

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
long FunctionsExt::BuscarIndirectos(SPB *Super,long Nivel, long NivelActual, long Comienzo, std::string PathVirtual, const char *PathReal,long Tipo){



    if(Nivel==NivelActual){

        return BuscarDirectos(Comienzo,PathVirtual,PathReal,Tipo);
    }
    FILE *f;
    f=fopen(PathReal,"r+");
    BAP Apunta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Apunta,sizeof(Apunta),1,f);
    fclose(f);




    for(long i=0;i<16;i++){
        long Valor=Apunta.b_pointers[i];


        if(Valor!=-1){





            Valor=BuscarIndirectos(Super,Nivel,NivelActual+1,Valor,PathVirtual,PathReal,Tipo);


            if(Valor==-2){
                return -2;
            }

            if(Valor!=-1){
                return Valor;
            }
        }else if(Tipo==2 || Tipo==4){
            int NuevoIndirecto=CrearIndirectosContenido(Nivel,NivelActual,Super,PathReal,0);
            if(NuevoIndirecto==-1)
                return -1;

            Apunta.b_pointers[i]=NuevoIndirecto;
            f=fopen(PathReal,"r+");
            fseek(f,Comienzo,SEEK_SET);
            fwrite(&Apunta,sizeof(Apunta),1,f);
            fclose(f);
            return BuscarIndirectos(Super,Nivel,NivelActual,Comienzo,PathVirtual,PathReal,Tipo);
            //return CrearIndirectosContenido(Nivel,NivelActual+1,Super,PathReal,Comienzo);

             std::cout<<"IMP "<<std::endl;
                return -1;
            long BloqueDirectoNuevo=BloqueLibre(Super,PathReal);
            if(BloqueDirectoNuevo==-1){
                std::cout<<"No Se Pudo Crear Nuevos Bloques"<<std::endl;
                return -1;
             }
            FILE *f;
            f=fopen(PathReal,"r+");

            if(Nivel-NivelActual!=1){
                BuscarIndirectos(Super,Nivel,NivelActual+1,Valor,PathVirtual,PathReal,Tipo);
            }




            //Escribiendo el Directo
            fseek(f,BloqueDirectoNuevo,SEEK_SET);
            BCA BloqueDirecto;
            IniciarBloqueCarpeta(&BloqueDirecto);
            //std::cout<<BloqueDirecto.content[2].b_name<<std::endl;

            fwrite(&BloqueDirecto,sizeof (BloqueDirecto),1,f);
            //Actualizando Indirectos


            fseek(f,Comienzo,SEEK_SET);
            Apunta.b_pointers[i]=BloqueDirectoNuevo;
            fwrite(&Apunta,sizeof (Apunta),1,f);


            fclose(f);
            //Crear El Directo


            return BloqueDirectoNuevo;

        }
    }
    return -1;
}

//Permisos
std::string FunctionsExt::PermisosEnElPadre(long Comienzo, const char *PathReal,IUG Permiso){
    FILE *f;
    f=fopen(PathReal,"r+");
    INO Carpeta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);

    long Selec=3;
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
bool FunctionsExt::TienePermiso(long Comienzo, const char *PathReal, std::string Info,IUG Permiso){
    std::string PermisoCarpeta=PermisosEnElPadre(Comienzo,PathReal,Permiso);
    if(IF(PermisoCarpeta,""))
        return false;



    for(long i=0;i<3;i++){
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
//Nombres
std::string FunctionsExt::PathArchivo(const char *PathVirtual){
    std::string s = PathVirtual;
    std::string delimiter = "/";
    size_t pos = 0;
    std::string token;
    std::string Escritura="";
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        if(IF("",token)){

        }else{
            Escritura=Escritura+"/"+token;
        }
        s.erase(0, pos + delimiter.length());
    }

    return Escritura;
}
std::string FunctionsExt::NombreACrear(const char *PathVirtual){
    std::string s = PathVirtual;
    std::string delimiter = "/";
    size_t pos = 0;
    std::string token;
    std::string Escritura="";
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        if(IF("",token)){

        }else{
            Escritura=Escritura+"/"+token;
        }
        s.erase(0, pos + delimiter.length());
    }

    return s;
}
//Cuenta Cuantas '/' Hay en un string
long FunctionsExt::CantidadBarras(std::string Path){
    long Contador=0;
    long Longitud=Path.length();
    for(long i=0;i<Longitud;i++){
        if('/'==Path.at(i)){
            Contador++;
        }
    }
    return Contador;
}
//BuscarActual
long FunctionsExt::BuscarActual(long Comienzo, std::string PathVirtual, const char *PathReal){
    if(IF(PathVirtual,"/"))
        return Comienzo;
    //PathVirtual=PathVirtual.substr(1);
    long Busq=BuscarPadre(Comienzo,(PathVirtual),PathReal);

    if(Busq==-1){
        std::cout<<"No Se Encontro La Carpeta Padre"<<std::endl;
        return Busq;
    }
    std::string Nombre=NombreACrear(PathVirtual.data());
    FILE *f;
    f=fopen(PathReal,"r+");
    INO Carpeta;
    fseek(f,Busq,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);
    long Punteros=-1;

    for(long i=0;i<12;i++){
        long Apuntador=Carpeta.i_block[i];
        if(Apuntador!=-1){
             Punteros=BuscarIndirectos(nullptr,0,0,Apuntador,Nombre,PathReal,3);
             if(Punteros!=-1)
                 return Punteros;
        }
    }
    for(long i=0;i<3;i++){
        long Apuntador=Carpeta.i_block[12+i];
        if(Apuntador!=-1){
            Punteros=BuscarIndirectos(nullptr,1+i,0,Apuntador,Nombre,PathReal,3);
            if(Punteros!=-1)
                return Punteros;
        }
    }



    return  Punteros;
}
long FunctionsExt::CrearIndirectos(long Nivel, long NivelActual, SPB *Super, const char *PathReal){
    BAP Apuntador;
    for(long i=0;i<16;i++){
         Apuntador.b_pointers[i]=-1;
    }

    if(Nivel==NivelActual){
        //ARREGLAR  crear directos
        long Actual=BloqueLibre(Super,PathReal);

        //std::cout<<"Function BORRAR     "<<Actual<<std::endl;
        FILE *f;
        BCA Carpeta;
        IniciarBloqueCarpeta(&Carpeta);

        f=fopen(PathReal,"r+");
        //Actualizar Indirecto
        fseek(f,Actual,SEEK_SET);
        fwrite(&Carpeta,sizeof (Carpeta),1,f);
        //Actualizar Indirecto
        fclose(f);



        return Actual;
    }
    long PosicionPadre=BloqueLibre(Super,PathReal);
    if(PosicionPadre==-1){
        std::cout<<"No Se Puedo Encontrar Un Bloque Libre"<<std::endl;
        return -1;
    }

    for(long i=0;i<16;i++){
        long Hijo=CrearIndirectos(Nivel,NivelActual+1,Super,PathReal);
        if(Hijo==-1){
            std::cout<<" Se Llego Al Limite De Apuntadores "<<std::endl;
            break;
        }else if(Hijo!=0){
            //Posicion De Cada Hijo;
            //std::cout<<" Hola "<<Hijo<<std::endl;
            Apuntador.b_pointers[i]=Hijo;
            //break;

        }
    }

    FILE *f;
    f=fopen(PathReal,"r+");
    fseek(f,PosicionPadre,SEEK_SET);
    fwrite(&Apuntador,sizeof (Apuntador),1,f);
    fclose(f);
    return PosicionPadre;

}

//REDUCIR TAMANIO String
std::string FunctionsExt::ReducirTamanio(std::string *Ingreso, long Num){
    long Longitud=Ingreso->length();
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
//Redux
std::string FunctionsExt::Reducir(std::string *Entrada){

    long Longitud=long(Entrada->length());
    for(long i=0;i<Longitud;i++){
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
std::string FunctionsExt::ColocarContenidoArchivo(long PosDirecto, SPB *Super, const char *PathReal, std::string Contenido){
    long Longitud=Contenido.length();
    if(Longitud>64*4){
        std::cout<<"STRING MUY GRANDFEE"<<std::endl;
        return Contenido;
    }




    FILE *f;
    f=fopen(PathReal,"r+");
    fseek(f,PosDirecto,SEEK_SET);
    BCA Directo;
    fread(&Directo,sizeof(Directo),1,f);
    for(long z=0;z<4;z++){


        long Pos=Directo.content[z].b_inodo;

        if(IF(Contenido,"") && Pos==-1){
            //Llenar Nombre
            std::string Sub="......";
            strcpy(Directo.content[z].b_name,Sub.c_str());

            //Se Actualizo El Apuntador Directo
            fseek(f,PosDirecto,SEEK_SET);
            fwrite(&Directo,sizeof (Directo),1,f);

        }else

        if(Pos==-1){

            //Llenar Nombre
            std::string Sub="......";
            strcpy(Directo.content[z].b_name,Sub.c_str());
            //Inodo Nuevo
            //long Libre = BloqueLibre(Super,PathReal);
            long Libre = BloqueLibreConte(Super,PathReal);
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
            long Llenar=64-(Almacenado.length());



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
//Contenido
//Verificar Si Tiene Permisos
bool FunctionsExt::PermisoDirectos(long Comienzo, const char *PathReal,IUG Permiso){
    FILE *f;
    f=fopen(PathReal,"r+");
    BCA Carpeta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);
    std::string Concatenar="";
    bool Comp=true;
    for(long i=0;i<4;i++){
        CON Contenido=Carpeta.content[i];

        if(Contenido.b_inodo!=-1){
            Comp=PermisoInodo(Contenido.b_inodo,PathReal,Permiso);
            if(Comp==false)
                return false;
        }
    }
    return true;
}
bool FunctionsExt::PermisoIndirectos(long Nivel, long NivelActual, long Comienzo,  const char *PathReal,IUG Permiso){
    if(Nivel==NivelActual){
        return PermisoDirectos(Comienzo,PathReal,Permiso);
    }
    FILE *f;
    f=fopen(PathReal,"r+");
    BAP Apunta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Apunta,sizeof(Apunta),1,f);
    fclose(f);
    bool Com=true;
    for(long i=0;i<16;i++){
        long Valor=Apunta.b_pointers[i];
        if(Valor!=-1){
            Com=PermisoIndirectos(Nivel,NivelActual+1,Valor,PathReal,Permiso);
            if(Com==false)
                return false;
        }
    }

    return true;
}
bool FunctionsExt::PermisoInodo(long Comienzo, const char *PathReal,IUG Permiso){
    FILE *f;
    f=fopen(PathReal,"r+");
    INO Carpeta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);

    if(TienePermiso(Comienzo,PathReal,"010",Permiso)==false)
        return false;

    if(Carpeta.i_type=='1')//Es Carpeta No Hay Mas
        return true;

    bool Comp=true;
    for(long i=0;i<12;i++){
        long Apuntador=Carpeta.i_block[i];
        if(Apuntador!=-1){
            Comp=PermisoIndirectos(0,0,Apuntador,PathReal,Permiso);
            if(Comp==false)
                return false;
        }
    }

    for(long i=0;i<3;i++){
        long Apuntador=Carpeta.i_block[i+12];
        if(Apuntador!=-1){
            Comp=PermisoIndirectos(1+i,0,Apuntador,PathReal,Permiso);
            if(Comp==false)
                return false;
        }
    }
    return true;
}

