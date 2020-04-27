#ifndef REPORTS_H
#define REPORTS_H
#include "structs.h"
#include "functions.h"
#include <iomanip>
#include <queue>
#include <sstream>
class Reports
{
public:
    void ReporteJournaling(int Inicio,const char *Disco,const char *Path);
    void ReporteLS(int Inicio,const char *PathReal,const char *Salida,const char *Nombre);
    void ReporteFile(const char *Path,const char *Contenido);
    void ReporteSB(int Inicio,const char *Disco,const char *Path);
    void ReporteBlock(int Inicio,const char *Disco,const char *Path);
    void ReporteInode(int Inicio,const char *Disco,const char *Path);
    void ReporteTablaMBR(const char *Path,const char *Guardar,int Num);
    void ReporteTablaEBR(EBR Extendida,const char *Guardar,int Num);
    void Reportebm_Inodo(int Inicio,const char *Disco,const char *Path);
    void Reportebm_Bloque(int Inicio,const char *Disco,const char *Path);
    void Graphviz(const char *Path,const char *Guardar);
    void ReporteArbol(int Inicio,const char *Disco,const char *Path);
    Reports();
private:
    std::string NuevaFilaLS(std::string Color,std::string Permiso,std::string Owner,std::string Grupo,std::string Size,std::string Fecha,std::string Hora,std::string Tipo,std::string Name);

    //
    int Contador;
    std::queue <int> Cola;
    std::queue <int> ColaI;
    //Generadores Del LS
    std::string LsInodos(int Comienzo,const char *PathReal,const char *Nombre);
    std::string LsDirectos(int Comienzo,const char *PathReal,int Tipo);
    std::string LsIndirectos(int Nivel, int NivelActual,int Comienzo,const char *PathReal,int Tipo);
    //Generadores

    std::string RecorrerBloqueContenido(int Comienzo,const char *PathReal);
    std::string RecorrerInodos(int Comienzo,const char *PathReal);
    std::string RecorrerDirectos(int Comienzo,const char *PathReal,int Tipo);
    std::string RecorrerIndirectos(int Nivel, int NivelActual,int Comienzo,const char *PathReal,int Tipo);

    std::string InodoAString(INO Inodo,int Comienzo,int Nombre);
    //TABLA
    std::string TablaPAR(PAR Parti,int Num);
    std::string TablaEBR(EBR Extendida,int Num);
    //GRAFICO
    std::queue <RDI> LlenarLogicas(const char *Path, int Begin, int End);
    std::queue <RDI> LogicReport(const char *Path, int Begin, int End);
    std::queue <RDI> PARTReport(const char *Path);
    std::string GraphP(RDI Dita,const char *Path);
    std::string GraphEmpty(RDI Dita,const char *Path);
    std::string GraphE(RDI Dita,const char *Path,std::queue <RDI> Que);
    std::string GraphL(const char *Path,std::queue <RDI> Que);
    void FillQueue(std::queue <RDI> *Q1,std::queue <RDI> Q2);
    Functions *Fun = new Functions();
    //ARBOL
    std::string GraficarBloqueContenido(int Comienzo,const char *PathReal);
    std::string GraficarInodos(int Comienzo,const char *PathReal);
    std::string GraficarDirectos(int Comienzo,const char *PathReal,int Tipo);
    std::string GraficarIndirectos(int Nivel, int NivelActual,int Comienzo,const char *PathReal,int Tipo);
    std::string NuevaFila(std::string Color1,std::string Color2,std::string Contenido1,std::string Contenido2);
};

#endif // REPORTS_H
