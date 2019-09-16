#ifndef EXT_H
#define EXT_H
#include <iostream>
#include "structsext.h"
#include <stdio.h>
#include "stdlib.h"
#include "functions.h"
class EXT
{
public:
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
    int CalcularCantidad(int Tamanio,int Tipo);
    //CrearFormato
    SPB LlenarSuperBloque(int Tipo,int Comienzo,int Cantidad);
    void EstructurarFormatoEXT2(int ComienzoParticion,int TamanioParticion,int TamanioStruct,std::string Direcc);
    void EstructurarFormatoEXT3(int ComienzoParticion,int TamanioParticion,int TamanioStruct,std::string  Direcc);
    EXT();
private :
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
    bool CarpetaArchivoSimpleDirectos(INO *Ino,SPB *Super,int PosPadre, const char *PathReal ,std::string NombreCarpeta,std::string Contenido);
    //CrearCarpetaSimpleEn Apuntadores Indirectos
    bool CarpetaArchivoSimpleInDirectos(INO *Ino,SPB *Super,int PosPadre, const char *PathReal,const char *PathVirtual ,std::string NombreCarpeta,std::string Contenido);
    //CantidadDeBarras
    int CantidadBarras(std::string Path);
    //Nombre De La Cosa A Crear
    std::string NombreACrear(const char *PathVirtual);
    //Buscar Inodo Libre
    int InodoLibre(SPB *Super,const char* Path);
    //Buscar Bloque Libre
    int BloqueLibre(SPB *Super,const char* Path);
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
