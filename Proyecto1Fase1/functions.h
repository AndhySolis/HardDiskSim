#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include<QDebug>
#include <iostream>
#include <time.h>
#include <queue>
#include "structs.h"
#include <algorithm>
class Functions
{
public:
    Functions();
    int Mult(int Num,char C);
    int LogicFit( char Fit[2],int Size,const char *Path,int Begin,int End);
    int DiskFit( char Fit[2],int Size,const char *Path);
    int FileSize(const char *Path);
    int BlockSize(int Num,const char *Path);
    int LogicalFirstFit(int Size,const char *Path,int Begin,int End);
    int LogicalWorstFit(int Size,const char *Path,int Begin,int End);
    int LogicalBestFit(int Size,const char *Path,int Begin,int End);
    int FirstFit(int Size,const char *Path);
    int WorstFit(int Size,const char *Path);
    int BestFit(int Size,const char *Path);
    int HasExtended(const char *Path);
    void Out(const char *Path);
    bool IF( const char* a, const char* b);

    EBR SearchEBR(const char *Name,const char *Path);
    PAR SearchPAR(const char *Name,const char *Path);

};

#endif // FUNCTIONS_H
