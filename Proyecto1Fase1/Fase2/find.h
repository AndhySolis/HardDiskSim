#ifndef FIND_H
#define FIND_H
#include <iostream>
#include <time.h>
#include "structsext.h"
#include "functionsext.h"

class FIND:public FunctionsExt
{
public:
    FIND(int Comienzo,std::string PathVirtual,const char *PathReal,IUG Permiso);
    //Buscar
    void Find(int Comienzo,std::string PathVirtual,const char *PathReal);
private:
    //FIND
    IUG Permiso;
    void FindInodo(int Comienzo,const char *PathReal,std::string Expansion);
    void FindDirectos(int Comienzo,const char *PathReal,int Tipo,std::string Expansion);
    void FindIndirectos(int Nivel, int NivelActual,int Comienzo,const char *PathReal,int Tipo,std::string Expansion);
};

#endif // FIND_H
