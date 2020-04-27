#ifndef RECUPERACION_H
#define RECUPERACION_H
#include "functions.h"
#include <queue>
#include "structsext.h"
class Recuperacion
{
public:


    void RecuCHGRP(int Comienzo, const char *Path,const char*Grp,const char*Usr,IUG Inf);
    void RecuCHOWN(int Comienzo, const char *Path,const char*PathVirtual,const char*Usr,bool Recursivo,IUG Inf);
    void RecuMV(int Comienzo, const char *Path,const char*PathOrigen,const char*PathDestino,IUG Inf);
    void RecuCP(int Comienzo, const char *Path,const char*PathOrigen,const char*PathDestino,IUG Inf);
    void RecuMKDIR(int Comienzo, const char *Path,const char*PathVirtual,bool Recursivo,IUG Inf);
    void RecuREN(int Comienzo, const char *Path,const char*PathVirtual,const char*NuevoNombre,IUG Inf);
    void RecuEDIT(int Comienzo, const char *Path,const char*PathVirtual,const char *Cont,bool Recursivo,int Tamanio,int PosiArchivo,IUG Inf);
    void RecuREM(int Comienzo, const char *Path,const char*PathVirtual,IUG Inf);
    void RecuMKFILE(int Comienzo, const char *Path,const char*PathVirtual, const char *Cont,bool Recursivo,int Tamanio,int PosiArchivo,IUG Inf);
    void RecuCHMOD(int Comienzo, const char *Path,const char*PathVirtual,const char*Ugo,bool Recursivo,IUG Inf);
    void RecuMKUSR(int Comienzo, const char *Path,const char*Usr,const char*Pwd,const char*Grp,IUG Inf);
    void RecuRMUSR(int Comienzo, const char *Path,const char*Usr,IUG Inf);
    void RecuMKGRP(int Comienzo, const char *Path,const char*Nombre,IUG Inf);
    void RecuRMGRP(int Comienzo, const char *Path,const char*Nombre,IUG Inf);
    void IniciarJOUR(int Comienzo,const char *Path);
    std::queue<JOR> ListaDeOperaciones(int Comienzo,const char *Path);
    Recuperacion();
private:
    void NuevoRegistro(int Comienzo, const char *Path, JOR Recu);
};

#endif // RECUPERACION_H
