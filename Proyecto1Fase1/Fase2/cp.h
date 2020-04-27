#ifndef CP_H
#define CP_H
#include <iostream>
#include <time.h>
#include "structsext.h"
#include "functionsext.h"

class CP:public FunctionsExt
{
public:
    CP(SPB *Super,int Comienzo,std::string PathVirtualOrigen,const char *PathReal,std::string PathVirtualDestino,IUG Permiso);

    //CopiaCarpetaOArchivo
    void CopiarCarpetaArchivo(SPB *Super,int Comienzo,std::string PathVirtualOrigen,const char *PathReal,std::string PathVirtualDestino);
private:
    IUG Permiso;
    //Copiar
    int CopiarInodo(SPB *Super,int Comienzo,const char *PathReal);
    int CopiarDirectos(SPB *Super,int Comienzo,const char *PathReal,int Tipo);
    int CopiarIndirectos(SPB *Super,int Nivel, int NivelActual,int Comienzo,const char *PathReal,int Tipo);
    int CopiarContenido(SPB *Super,int Comienzo,const char *PathReal);
};

#endif // CP_H
