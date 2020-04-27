#ifndef EDIT_H
#define EDIT_H
#include "functionsext.h"

class EDIT:public FunctionsExt
{
public:
    EDIT(SPB *Super,int Comienzo,const char *PathVirtual,const char *PathReal,std::string Contenido,IUG Permiso);
private:
    IUG Permiso;
    //Expande Archivo
    void ExpandirArchivo(SPB *Super,int Comienzo,const char *PathVirtual,const char *PathReal,std::string Contenido);

};

#endif // EDIT_H
