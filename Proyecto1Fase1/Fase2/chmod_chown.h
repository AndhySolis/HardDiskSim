#ifndef CHMOD_CHOWN_H
#define CHMOD_CHOWN_H
#include "functionsext.h"

class CHMOD_CHOWN: public FunctionsExt{
public:
    CHMOD_CHOWN(int Comienzo, const char *PathVirtual, const char *PathReal, int NuevoDuenio,int OPE,IUG Permiso,bool Propietario);
private:
    IUG Permiso;
    //Cambiar Dueño
    void CambiarPropietarioNormalRecursivo(int Comienzo,const char *PathVirtual,const char *PathReal,int NuevoDuenio,int OPE);
    //Cambiar Permisos Normal Y Recursivo  Ope 1== Normal    Ope 2== Recursivo
    void CambiarPermisosNormalRecursivo(int Comienzo,const char *PathVirtual,const char *PathReal,int Ope,int Perm);
    //ModificarValores
    void ModificarInodo(int Comienzo,const char *PathReal,int Tipo,int Perm);
    void ModificarDirectos(int Comienzo,const char *PathReal, int Tipo,int Perm );
    void ModificarIndirectos(int Nivel, int NivelActual,int Comienzo,const char *PathReal, int Tipo,int Perm);
};

#endif // CHMOD_CHOWN_H
