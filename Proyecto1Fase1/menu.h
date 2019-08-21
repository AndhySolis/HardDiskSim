#ifndef MENU_H
#define MENU_H
#include<QDebug>
#include <iostream>
#include <time.h>
#include "functions.h"
#include "structs.h"
#include "reports.h"
#include "disco.h"
//Para el mount

//Para Los Fit


class Menu
{
public:
    //AGREGAR
    void FDISKAdd(int Size,const char *Path,const char *Name);
    //MONTAR
    void UNMOUNT(const char *Name);
    void MOUNT(const char *Path,const char *Name);
    //RMDISK
        void RMDISK(const char *Path);
    //MKDsik
    void Mkdisk(int Size,const char Fit[2],char Unit,const char *Path);
    //FDisk
    void FDisk(int Size,const char Fit[2],char Unit,const char *Path,char Type,const char *Name);

    //Menu
    Menu();
private:
    void ReducirLogica(int Size, const char *Path, EBR Ext,const char *Name);
    void ReducirPrimaria(int Size,const char *Path,int Indice);
    void AgregarMas(int Size,const char *Path,const char *Name);
    void AgregarMenos(int Size,const char *Path,const char *Name);
    Functions *Fun=  new Functions();
    Reports *Repo=  new Reports();
    Disco *PrimerDisco = nullptr;


    //MOUNT


    //
    //FDISK
        //FDISKDELETE
        void FDISKDelete(const char *Delete,const char *Path,const char *Name);
        void DeleteFastLogic(EBR InputLogic,const char *Path);
        void DeleteFullLogic(EBR InputLogic,const char *Path);
        void DeleteFast(PAR Parti,const char *Path);
        void DeleteFull(PAR Parti,const char *Path);

        //
    void FillPAR(PAR *NPAR);

    void FillName(char Arra[16],const char *Input);
    void FillDisk(int Begin,int Size,char Character,const char *Path);
    void NewPrimary(int Size,const char Fit[2],char Unit,const char *Path,const char *Name);
    void NewExtended(int Size,const char Fit[2],char Unit,const char *Path,const char *Name);
    void NewLogical(int Size,const char Fit[2],char Unit,const char *Path,const char *Name);

    int HasBytes(const char *Path);
    int HasSlot(const char *Path);
    void Resize();
    void DeleteParth();
    //Utilidades

    void NewMenu();




};

#endif // MENU_H
