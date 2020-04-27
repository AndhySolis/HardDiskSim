#ifndef MKFS_H
#define MKFS_H
#include<QDebug>
#include <iostream>
#include <time.h>
#include "structsext.h"
#include "functionsext.h"

class MKFS :public FunctionsExt
{
public:
    MKFS(int ComienzoParticion,int TamanioParticion,int TamanioStruct,std::string Direcc,int Tipo,int Ext,IUG Permiso);
private:

    //
    IUG Permiso;

    //Hacer Formato
    void EstructurarFormatoEXT3(int ComienzoParticion,int TamanioParticion,int TamanioStruct,std::string Direcc,int Tipo,int Ext);



};

#endif // MKFS_H
