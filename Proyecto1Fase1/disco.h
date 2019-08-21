#ifndef DISCO_H
#define DISCO_H
#include <QList>
#include "structs.h"
#include "functions.h"
class Disco
{
public:
    QList <MOU> Lista;
    Disco(const char *Path,Disco *Nuevo);
    const char *Path;
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
