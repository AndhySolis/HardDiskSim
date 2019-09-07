#ifndef DISCO_H
#define DISCO_H
#include <QList>
#include "structs.h"
#include "functions.h"
class Disco
{
public:
    void FormatearParticion(const char *Nombre,int Tipo);
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
    void BuscarDisco(const char *Nombre);
    void Reporte(const char *ID,const char *Path,const char *Tipo);
private:
    Functions *Fun=  new Functions();
    std::string GenerarApodo();
    std::string NumeroAString(int Num);

};

#endif // DISCO_H
