#ifndef EXT_H
#define EXT_H
#include <iostream>
#include "structsext.h"
#include <stdio.h>
#include "stdlib.h"
#include "functions.h"
#include "recuperacion.h"
class EXT
{
public:    
    //Cambiar Dueño
    void CambiarPropietarioNormalRecursivo(int Comienzo,const char *PathVirtual,const char *PathReal,int NuevoDuenio,int OPE);
    void FIND(int Comienzo,std::string PathVirtual,const char *PathReal);
    //MoverCarpetaOArchivo
    void MoverCarpetaArchivo(SPB *Super,int Comienzo,std::string PathVirtualOrigen,const char *PathReal,std::string PathVirtualDestino);
    //CopiaCarpetaOArchivo
    void CopiarCarpetaArchivo(SPB *Super,int Comienzo,std::string PathVirtualOrigen,const char *PathReal,std::string PathVirtualDestino);
    //Renombrar Archivo O Carpeta
    bool CambiarNombre(int Comienzo,std::string PathVirtual,const char *PathReal,std::string Renombre);
    //Cambiar Permisos Normal Y Recursivo  Ope 1== Normal    Ope 2== Recursivo
    void CambiarPermisosNormalRecursivo(int Comienzo,const char *PathVirtual,const char *PathReal,int Ope,int Perm);
    //Eliminar ArchivoCarpeta
    bool EliminarArchivoCarpeta(SPB *Super,int Comienzo,const char *PathVirtual,const char *PathReal);
    //Leer Archivo Almacenado
    std::string LeerArchivo(int Inicio,const char *Disco,const char *Path);
    //Expande Archivo
    void ExpandirArchivo(SPB *Super,int Comienzo,const char *PathVirtual,const char *PathReal,std::string Contenido);
    //CrearArchivoSimple
    bool CrearArchivoCompleto(SPB *Super,int Comienzo,const char *PathVirtual,const char *PathReal,std::string Contenido);
    //CrearArchivoSimple
    bool CrearArchivoSimple(SPB *Super,int Comienzo,const char *PathVirtual,const char *PathReal,std::string Contenido);
    //CrearTodasCarpetas
    bool CrearCarpetaCompleto(SPB *Super,int Comienzo,const char *PathVirtual,const char *PathReal);
    //CrearCarpetasSimples
    bool CrearCarpetaSimple(SPB *Super,int Comienzo,const char *PathVirtual,const char *PathReal);
    //Calcular la cantidad de estructruas
    int CalcularCantidad(int Tamanio);
    //CrearFormato
    SPB LlenarSuperBloque(int Tipo,int Comienzo,int Cantidad);
    void EstructurarFormatoEXT3(int ComienzoParticion,int TamanioParticion,int TamanioStruct,std::string Direcc,int Tipo);

    EXT(IUG Permiso);
private :
    //Auxiliares
    void CantidadVeces(std::string Contenido);
    int ValPrimeraPos=-1;
    int ValTamanio=-1;
    //
    void DuplicarInodo(INO *Original,INO *Copia);
    IUG Permiso;
    //FIND
    void FindInodo(int Comienzo,const char *PathReal,std::string Expansion);
    void FindDirectos(int Comienzo,const char *PathReal,int Tipo,std::string Expansion);
    void FindIndirectos(int Nivel, int NivelActual,int Comienzo,const char *PathReal,int Tipo,std::string Expansion);
    //Copiar
    int CopiarInodo(SPB *Super,int Comienzo,const char *PathReal);
    int CopiarDirectos(SPB *Super,int Comienzo,const char *PathReal,int Tipo);
    int CopiarIndirectos(SPB *Super,int Nivel, int NivelActual,int Comienzo,const char *PathReal,int Tipo);
    int CopiarContenido(SPB *Super,int Comienzo,const char *PathReal);
    //Renombrar
    bool RenombrarInodo(int Comienzo,const char *PathReal,std::string  Info,std::string  Busqueda);
    bool RenombrarDirectos(int Comienzo,const char *PathReal,std::string  Info,std::string  Busqueda);
    bool RenombrarIndirectos(int Nivel, int NivelActual,int Comienzo,const char *PathReal,std::string  Info,std::string  Busqueda);
    //Permisos
    bool TienePermiso(int Comienzo,const char * PathReal,std::string Info);
    std::string PermisosEnElPadre(int Comienzo,const char * PathReal);
    //ComprobarPermisos
    bool PermisoInodo(int Comienzo,const char *PathReal);
    bool PermisoDirectos(int Comienzo,const char *PathReal);
    bool PermisoIndirectos(int Nivel, int NivelActual,int Comienzo,const char *PathReal);
    //ModificarValores
    void ModificarInodo(int Comienzo,const char *PathReal,int Tipo,int Perm);
    void ModificarDirectos(int Comienzo,const char *PathReal, int Tipo,int Perm );
    void ModificarIndirectos(int Nivel, int NivelActual,int Comienzo,const char *PathReal, int Tipo,int Perm);
    //Eliminar
    bool EliminarArchivoCarpetaPadre(SPB *Super,int Comienzo,const char *PathVirtual,const char *PathReal,int Hijo);
    void LiberarBloque(SPB *Super,const char *PathReal,int Comienzo);
    void LiberarInodo(SPB *Super,const char *PathReal,int Comienzo);
    bool EliminarBloqueContenido(SPB *Super,int Comienzo,const char *PathReal);
    bool EliminarInodo(SPB *Super,int Comienzo,const char *PathReal);
    bool EliminarDirectos(SPB *Super,int Comienzo,const char *PathReal, int Tipo , int Elim);
    bool EliminarIndirectos(SPB *Super,int Nivel, int NivelActual,int Comienzo,const char *PathReal, int Tipo, int Elim);
    //LecturaPartes
    std::string LeerBloqueContenido(int Comienzo,const char *PathReal);
    std::string LeerDirectos(int Comienzo,const char *PathReal);
    std::string LeerIndirectos(int Nivel, int NivelActual,int Comienzo,const char *PathReal);
    //
    int BuscarActual(int Comienzo,std::string PathVirtual,const char *PathReal);
    //Reduce Un String Enviado En Tamanio Y Devuelve Lo Que Se Redujo
    std::string ReducirTamanio(std::string *Ingreso,int Num);
    //Contenido En El Archivo
    std::string ColocarContenidoArchivo(int PosDirecto,SPB *Super,const char *PathReal,std::string Contenido);
    //ContenidoArchivoDirecto
    std::string ContenidoArchivoDirectos(INO *Ino,SPB *Super,int PosPadre, const char *PathReal ,std::string Contenido);
    //ContenidoArchivoIndirecto
    std::string ContenidoArchivoInDirectos(INO *Ino,SPB *Super,int PosPadre, const char *PathReal,const char *PathVirtual ,std::string Contenido);
    //Poner Archivo
    int ColocarArchivo(std::string NombreCarpeta,int PosDirecto,SPB *Super,const char *PathReal,std::string Contenido);
    //CrearCarpetaSimpleEn Apuntadores Drectos
    int CarpetaArchivoSimpleDirectos(INO *Ino,SPB *Super,int PosPadre, const char *PathReal ,std::string NombreCarpeta,std::string Contenido);
    //CrearCarpetaSimpleEn Apuntadores Indirectos
    int CarpetaArchivoSimpleInDirectos(INO *Ino,SPB *Super,int PosPadre, const char *PathReal,const char *PathVirtual ,std::string NombreCarpeta,std::string Contenido);
    //CantidadDeBarras
    int CantidadBarras(std::string Path);
    //Nombre De La Cosa A Crear
    std::string PathArchivo(const char *PathVirtual);
    std::string NombreACrear(const char *PathVirtual);
    //Buscar Inodo Libre
    int InodoLibre(SPB *Super,const char* Path);
    //Buscar Bloque Libre
    int BloqueLibre(SPB *Super,const char* Path);
    int BloqueLibreConte(SPB *Super,const char* Path);
    int DarPrimeraPos(SPB *Super,const char* Path);
    //Comprobar Si Se Puede Colocar Carpeta En Un Bloque Directo
    int ColocarCarpeta(std::string NombreCarpeta,int PosDirecto,SPB *Super,const char *PathReal);
    int CrearIndirectos(int Nivel,int NivelActual,SPB *Super,const char *PathReal);
    std::string Reducir(std::string *Entrada);
    int BuscarPadre(int Comienzo,std::string PathVirtual,const char *PathReal);
    int BuscarInodos(int Comienzo,std::string PathVirtual,const char *PathReal);
    int BuscarDirectos(int Comienzo,std::string PathVirtual,const char *PathReal,int Tipo);
    int BuscarIndirectos(SPB *Super,int Nivel,int NivelActual,int Comienzo,std::string PathVirtual,const char *PathReal,int Tipo);
    void IniciarInodo(INO *Inodo,int i_uid,int i_gid,int i_size,int PrimerBloque,char Tipo,int Perm);
    void IniciarBloqueCarpeta(BCA *Bloque);
    void LlenarVacio(int Begin, int Size, char Character,const char *Path);
    Functions *Fun;
};

#endif // EXT_H
