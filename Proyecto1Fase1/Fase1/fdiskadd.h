#ifndef FDISKADD_H
#define FDISKADD_H
#include<QDebug>
#include <iostream>
#include <time.h>
#include "structsext.h"
#include "functions.h"

class FDISKADD
{
public:
    FDISKADD(int Size, const char *Path, const char *Name);
private:

    Functions *Fun;
    void ReducirLogica(int Size, const char *Path, EBR Ext,const char *Name);
    void ReducirPrimaria(int Size,const char *Path,int Indice);
    void AgregarMas(int Size,const char *Path,const char *Name);
    void AgregarMenos(int Size,const char *Path,const char *Name);
};

#endif // FDISKADD_H
