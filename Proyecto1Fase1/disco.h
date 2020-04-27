#ifndef DISCO_H
#define DISCO_H
#include <QList>
#include <queue>
#include "structsext.h"
#include "structs.h"
#include "functions.h"
class Disco
{
public:
    //CHOWN
    void  PropietarioArchivoParticion(const char *Nombre,const char *Path,int Tipo,int Perm,IUG Permiso,const char *NameUsr);
    //Recovery
    std::queue<JOR> RecuperarInformacion(const char *Nombre);
    std::queue<JOR> Recuperar(int Comienzo,const char*Path);
    //LOSS
    void FillDisk(int Begin, int Size, char Character,const char *Path);
    void PerderInformacion(const char *Nombre);
    //FIND
    void BuscarArchivoParticion(const char *Nombre,const char *PathBase,const char *NombreBusqueda,IUG Permiso);
    //CP
    void  CopiarArchivoParticion(const char *Nombre,const char *PathOrigen,const char *PathDestino,IUG Permiso);
    //MV
    void  MoverArchivoParticion(const char *Nombre,const char *PathOrigen,const char *PathDestino,IUG Permiso);
    //REN
    void  RenombrarArchivoParticion(const char *Nombre,const char *NuevoNombre,const char *Path,IUG Permiso);
    //CHMOD
    void  PermisoArchivoParticion(const char *Nombre,const char *Path,int Tipo,int Perm,IUG Permiso,const char *NameUsr);
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
    //MKFS
    void FormatearParticion(const char *Nombre,IUG Permiso,int Tipo,int Ext);
    //Espacial
    void Contar(const char *Nombre,bool Montar);
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

    void Reporte(const char *ID,const char *Path,const char *Tipo,const char *Ruta);
private:
    Functions *Fun=  new Functions();
    std::string GenerarApodo();
    std::string NumeroAString(int Num);

};

#endif // DISCO_H
