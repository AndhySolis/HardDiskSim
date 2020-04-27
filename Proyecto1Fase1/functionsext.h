#ifndef FUNCTIONSEXT_H
#define FUNCTIONSEXT_H

#include "functions.h"
class FunctionsExt : public Functions
{
public:
    //Auxiliares EXT
    //Buscar Inodo Libre
    long InodoLibre(SPB *Super,const char* Path);
    //Buscar Bloque Libre
    long BloqueLibre(SPB *Super,const char* Path);
    long BloqueLibreConte(SPB *Super,const char* Path);
    long DarPrimeraPos(SPB *Super,const char* Path);
    //
    //Auxiliares
    long CrearIndirectosContenido(long Nivel, long NivelActual, SPB *Super, const char *PathReal,int Comienzo);
    bool EliminarArchivoCarpetaPadre(SPB *Super,long Comienzo,const char *PathVirtual,const char *PathReal,long Hijo);
    //Eliminar
    bool EliminarBloqueContenido(SPB *Super,long Comienzo,const char *PathReal);
    bool EliminarInodo(SPB *Super,long Comienzo,const char *PathReal);
    bool EliminarDirectos(SPB *Super,long Comienzo,const char *PathReal, long Tipo , long Elim);
    bool EliminarIndirectos(SPB *Super,long Nivel, long NivelActual,long Comienzo,const char *PathReal, long Tipo, long Elim);
    //Auxiliares
    void CantidadVeces(std::string Contenido);
    void DuplicarInodo(INO *Original,INO *Copia);
    //Busqueda
    long BuscarInodos(long Comienzo,std::string PathVirtual,const char *PathReal);
    long BuscarDirectos(long Comienzo,std::string PathVirtual,const char *PathReal,long Tipo);
    long BuscarIndirectos(SPB *Super,long Nivel,long NivelActual,long Comienzo,std::string PathVirtual,const char *PathReal,long Tipo);
    long BuscarPadre(long Comienzo,std::string PathVirtual,const char *PathReal);
    //Permisos
    std::string PermisosEnElPadre(long Comienzo,const char * PathReal,IUG Permiso);
    bool TienePermiso(long Comienzo,const char * PathReal,std::string Info,IUG Permiso);
    //Nombre De La Cosa A Crear
    std::string PathArchivo(const char *PathVirtual);
    std::string NombreACrear(const char *PathVirtual);
    //Contador
    //CantidadDeBarras
    long CantidadBarras(std::string Path);
    FunctionsExt();
    //
    long BuscarActual(long Comienzo,std::string PathVirtual,const char *PathReal);
    //
    long CrearIndirectos(long Nivel,long NivelActual,SPB *Super,const char *PathReal);
    //Reduce Un String Enviado En Tamanio Y Devuelve Lo Que Se Redujo
    std::string ReducirTamanio(std::string *Ingreso,long Num);
    //Redux
    std::string Reducir(std::string *Entrada);
    //Contenido En El Archivo
    std::string ColocarContenidoArchivo(long PosDirecto,SPB *Super,const char *PathReal,std::string Contenido);
    //ComprobarPermisos
    bool PermisoInodo(long Comienzo,const char *PathReal,IUG Permiso);
    bool PermisoDirectos(long Comienzo,const char *PathReal,IUG Permiso);
    bool PermisoIndirectos(long Nivel, long NivelActual,long Comienzo,const char *PathReal,IUG Permiso);
    //Liberar
    void LiberarBloque(SPB *Super,const char *PathReal,long Comienzo);
    void LiberarInodo(SPB *Super,const char *PathReal,long Comienzo);
    //ContenidoArchivoDirecto
    std::string ContenidoArchivoDirectos(INO *Ino,SPB *Super,long PosPadre, const char *PathReal ,std::string Contenido);
    //ContenidoArchivoIndirecto
    std::string ContenidoArchivoInDirectos(INO *Ino,SPB *Super,long PosPadre, const char *PathReal,const char *PathVirtual ,std::string Contenido);
private:
    long ValPrimeraPos=-1;
    long ValTamanio=-1;
};

#endif // FUNCTIONSEXT_H
