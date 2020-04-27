#ifndef FDISKDELETE_H
#define FDISKDELETE_H
#include<QDebug>
#include <iostream>
#include <time.h>
#include "structsext.h"
#include "functions.h"
#include "disco.h"
class FDISKDELETE
{
public:
    FDISKDELETE(const char *Delete,const char *Path,const char *Name,Disco *Primero);
private:

    void DeleteFastLogic(EBR InputLogic,const char *Path);
    void DeleteFullLogic(EBR InputLogic,const char *Path);
    void DeleteFast(PAR Parti,const char *Path);
    void DeleteFull(PAR Parti,const char *Path);
    bool DisponibleBorrarParticionMontada(const char *Id);

    //
    Disco *Primero;
    Functions *Fun;
};

#endif // FDISKDELETE_H
