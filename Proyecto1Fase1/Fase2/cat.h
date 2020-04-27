#ifndef CAT_H
#define CAT_H
#include "functionsext.h"

class CAT:public FunctionsExt
{
public:
    CAT(IUG Permiso);
    std::string LeerArchivo(int Inicio,const char *Disco,const char *Path);
private:
    IUG Permiso;
    //Leer Archivo Almacenado

    //LecturaPartes
    std::string LeerBloqueContenido(int Comienzo,const char *PathReal);
    std::string LeerDirectos(int Comienzo,const char *PathReal);
    std::string LeerIndirectos(int Nivel, int NivelActual,int Comienzo,const char *PathReal);
    //


};

#endif // CAT_H
