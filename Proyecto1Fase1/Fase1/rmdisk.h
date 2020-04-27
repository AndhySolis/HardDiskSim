#ifndef RMDISK_H
#define RMDISK_H
#include<QDebug>
#include <iostream>
#include <time.h>
#include "structsext.h"
#include "functions.h"
#include "disco.h"

class RMDISK
{
public:
    RMDISK(const char *Path);
private:
    Disco *PrimerDisco;
    bool DisponibleBorrarDisco(const char *Path);
    Functions *Fun;
};

#endif // RMDISK_H
