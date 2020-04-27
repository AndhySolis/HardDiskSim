#ifndef FDISK_H
#define FDISK_H
#include<QDebug>
#include <iostream>
#include <time.h>
#include "structsext.h"
#include "functions.h"

class FDISK
{
public:
    FDISK(int Size,const char Fit[2],char Unit,const char *Path,char Type,const char *Name);
private:
    int HasSlot(const char *Path);
    Functions *Fun;
    void NewPrimary(int Size,const char Fit[2],char Unit,const char *Path,const char *Name);
    void NewExtended(int Size,const char Fit[2],char Unit,const char *Path,const char *Name);
    void NewLogical(int Size,const char Fit[2],char Unit,const char *Path,const char *Name);
};

#endif // FDISK_H
