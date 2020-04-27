#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include<QDebug>
#include <iostream>
#include <time.h>
#include "structs.h"
#include <algorithm>
#include "structsext.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <sstream>

class Functions
{
public:

    //Llenar Espacios
    void LlenarVacio(int Begin, int Size, char Character,const char *Path);
    //Calcular la cantidad de estructruas
    int CalcularCantidad(int Tamanio,int Tipo);
    //CrearFormato
    SPB LlenarSuperBloque(int Tipo,int Comienzo,int Cantidad);
    //Inicio
    void IniciarInodo(INO *Inodo,int i_uid,int i_gid,int i_size,int PrimerBloque,char Tipo,int Perm);
    void IniciarBloqueCarpeta(BCA *Bloque);
    //
    void FillName(char Arra[16],const char *Input);
    void FillDisk(int Begin,int Size,char Character,const char *Path);
    void FillPAR(PAR *NPAR);
    Functions();
    int GenerarNumeroRandom();
    void Fecha(struct tm *Dita);
    std::string FechaString(struct tm *Dita);
    int LogicaFinal(PAR Extendida,const char *Path);
    int Mult(int Num,char C);
    int LogicFit( char Fit[2],int Size,const char *Path,int Begin,int End);
    int DiskFit( char Fit[2],int Size,const char *Path);
    int FileSize(const char *Path);
    int BlockSize(int Num,const char *Path);
    bool DiskLimit(MBR Main,int Index,int Size,const char *Path);
    bool LogicLimit(int EBRLimit,int Ini,int Size,const char *Path);
    int HasExtended(const char *Path);
    void Out(const char *Path);
    bool IFEspecial(std::string A , std::string B );
    bool IF(std::string A , std::string B );
    bool IF( const char* a, const char* b);
    EBR SearchEBR(const char *Name,const char *Path);
    int SearchPAR(const char *Name,const char *Path);
    bool ExisteArchivo(const char *Path);
    std::string DecimalBinario(char Decimal);
private:
    bool Valido(int Num);
    void EscribirRandom(int Num);

    int LogicalFirstFit(int Size,const char *Path,int Begin,int End);
    int LogicalWorstFit(int Size,const char *Path,int Begin,int End);
    int LogicalBestFit(int Size,const char *Path,int Begin,int End);
    int FirstFit(int Size,const char *Path);
    int WorstFit(int Size,const char *Path);
    int BestFit(int Size,const char *Path);


};

#endif // FUNCTIONS_H
