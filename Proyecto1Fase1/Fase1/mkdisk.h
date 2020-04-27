#ifndef MKDISK_H
#define MKDISK_H
#include<QDebug>
#include <iostream>
#include <time.h>
#include "structsext.h"
#include "functions.h"
class MKDISK
{
public:
    MKDISK(int Size,const char Fit[2],char Unit,const char *Path);
private:
    Functions *Fun;


};

#endif // MKDISK_H
