#ifndef MV_H
#define MV_H
#include "functionsext.h"
#include "mkfile_mkdir.h"
class MV:public FunctionsExt
{
public:
    MV(IUG Permiso,SPB *Super,int Comienzo,std::string PathVirtualOrigen,const char *PathReal,std::string PathVirtualDestino);
    //MoverCarpetaOArchivo
    void MoverCarpetaArchivo(SPB *Super,int Comienzo,std::string PathVirtualOrigen,const char *PathReal,std::string PathVirtualDestino);
private:
    IUG Permiso;
};

#endif // MV_H
