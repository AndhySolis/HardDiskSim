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
    void ReporteTablaMBR(const char *Path,const char *Guardar);
    void ReporteTablaEBR(EBR Extendida,const char *Guardar);
    void Graphviz(const char *Path);
    Reports();
private:
    //TABLA
    std::string TablaPAR(PAR Parti,int Num);
    std::string TablaEBR(EBR Extendida);
    //GRAFICO
    std::queue <RDI> LogicReport(const char *Path, int Begin, int End);
    std::queue <RDI> PARTReport(const char *Path);
    std::string GraphP(RDI Dita,const char *Path);
    std::string GraphEmpty(RDI Dita,const char *Path);
    std::string GraphE(RDI Dita,const char *Path,std::queue <RDI> Que);
    std::string GraphL(const char *Path,std::queue <RDI> Que);
    void FillQueue(std::queue <RDI> *Q1,std::queue <RDI> Q2);
    Functions *Fun = new Functions();
};

#endif // REPORTS_H
