#ifndef DISCO_H
#define DISCO_H
#include <QList>
#include "structs.h"
#include "functions.h"
class Disco
{
public:
    //CHMOD
    void  PermisoArchivoParticion(const char *Nombre,const char *Path,int Tipo,int Perm,IUG Permiso);
    //REM
    void  BorrarArchivoParticion(const char *Nombre,const char *Path,IUG Permiso);
    //CAT
    std::string LeerArchivoParticion(const char *Nombre,const char *Path,IUG Permiso);
    //EDIT
    void ExpandirArchivoParticion(const char *Nombre,const char *Path,std::string Contenido,IUG Permiso);
    //MKFILE
    void CrearArchivoParticion(const char *Nombre,const char *Path, char Padre,std::string Contenido,IUG Permiso);
    //MKDIR
    void CrearCarpetaParticion(const char *Nombre,const char *Path, char Padre,IUG Permiso);
    //FDISK
    void FormatearParticion(const char *Nombre,int Tipo,IUG Permiso);
    //---------------------------------FASE1


    bool ParticionLibreParaBorrar(const char *Nombre);
    bool DiscoLibreParaBorrar(const char *Nombre);
    QList <MOU> Lista;
    Disco(std::string Path,Disco *Nuevo);
    std::string Path;
    Disco *Siguiente;
    int Num;
    std::string Apodo;
    void AgregarParticion(const char *Nombre);
    void BorrarParticion(const char *Nombre);
    bool ExisteParticionMontada(const char *Nombre);
    void BuscarDisco(const char *Nombre);
    void Reporte(const char *ID,const char *Path,const char *Tipo);
private:
    Functions *Fun=  new Functions();
    std::string GenerarApodo();
    std::string NumeroAString(int Num);

};

#endif // DISCO_H
