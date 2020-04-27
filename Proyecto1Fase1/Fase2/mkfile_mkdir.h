#ifndef MKFILE_H
#define MKFILE_H
#include <iostream>
#include <time.h>
#include "structsext.h"
#include "functionsext.h"

class MKFILE_MKDIR:public FunctionsExt
{
public:
    MKFILE_MKDIR(SPB *Super, long Comienzo, const char *PathVirtual, const char *PathReal, std::string Contenido,bool EsCarpeta, bool EsCompleto,IUG Permiso);
    //CrearArchivoSimple
    bool CrearArchivoCompleto(SPB *Super,long Comienzo,const char *PathVirtual,const char *PathReal,std::string Contenido);
    //CrearArchivoSimple
    bool CrearArchivoSimple(SPB *Super,long Comienzo,const char *PathVirtual,const char *PathReal,std::string Contenido);
    //CrearTodasCarpetas
    bool CrearCarpetaCompleto(SPB *Super,long Comienzo,const char *PathVirtual,const char *PathReal);
    //CrearCarpetasSimples
    bool CrearCarpetaSimple(SPB *Super,long Comienzo,const char *PathVirtual,const char *PathReal);
    //Buscadores
    long CarpetaArchivoSimpleDirectos(INO *Ino,SPB *Super,long PosPadre, const char *PathReal ,std::string NombreCarpeta,std::string Contenido);
    //CrearCarpetaSimpleEn Apuntadores Indirectos
    long CarpetaArchivoSimpleInDirectos(INO *Ino,SPB *Super,long PosPadre, const char *PathReal,const char *PathVirtual ,std::string NombreCarpeta,std::string Contenido);

private:
    IUG Permiso;
    //Poner Archivo
    long ColocarArchivo(std::string NombreCarpeta,long PosDirecto,SPB *Super,const char *PathReal,std::string Contenido);
    //CrearCarpetaSimpleEn Apuntadores Drectos
    //Comprobar Si Se Puede Colocar Carpeta En Un Bloque Directo
    long ColocarCarpeta(std::string NombreCarpeta,long PosDirecto,SPB *Super,const char *PathReal);
};

#endif // MKFILE_H
