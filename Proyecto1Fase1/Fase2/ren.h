#ifndef REN_H
#define REN_H
#include "functionsext.h"

class REN:public FunctionsExt

{
public:
    REN(int Comienzo,std::string PathVirtual,const char *PathReal,std::string Renombre,IUG Permiso);
private:
    IUG Permiso;
    //Renombrar Archivo O Carpeta
    bool CambiarNombre(int Comienzo,std::string PathVirtual,const char *PathReal,std::string Renombre);
    //Renombrar
    bool RenombrarInodo(int Comienzo,const char *PathReal,std::string  Info,std::string  Busqueda);
    bool RenombrarDirectos(int Comienzo,const char *PathReal,std::string  Info,std::string  Busqueda);
    bool RenombrarIndirectos(int Nivel, int NivelActual,int Comienzo,const char *PathReal,std::string  Info,std::string  Busqueda);

};

#endif // REN_H
