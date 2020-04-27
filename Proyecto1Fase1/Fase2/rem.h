#ifndef REM_H
#define REM_H
#include<QDebug>
#include <iostream>
#include <time.h>
#include "structsext.h"
#include "functionsext.h"

class REM:public FunctionsExt
{
public:
    REM(SPB *Super,int Comienzo,const char *PathVirtual,const char *PathReal,IUG Permiso);
    //Eliminar ArchivoCarpeta
    bool EliminarArchivoCarpeta(SPB *Super,int Comienzo,const char *PathVirtual,const char *PathReal);
private:
    IUG Permiso;
    };

#endif // REM_H
