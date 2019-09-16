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
    void ReporteTablaMBR(const char *Path,const char *Guardar,int Num);
    void ReporteTablaEBR(EBR Extendida,const char *Guardar,int Num);
    void Reportebm_Inodo(int Inicio,const char *Disco,const char *Path);
    void Reportebm_Bloque(int Inicio,const char *Disco,const char *Path);
    void Graphviz(const char *Path,const char *Guardar);
    void ReporteArbol(int Inicio,const char *Disco,const char *Path);
    Reports();
private:
    //TABLA
    std::string TablaPAR(PAR Parti,int Num);
    std::string TablaEBR(EBR Extendida,int Num);
    //GRAFICO
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
