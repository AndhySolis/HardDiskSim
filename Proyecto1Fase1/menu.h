#ifndef MENU_H
#define MENU_H
#include<QDebug>
#include <iostream>
#include <time.h>
#include "functions.h"
#include "structs.h"
#include "reports.h"
#include "operacionusuario.h"
#include "disco.h"
#include "Fase1/mkdisk.h"
#include "Fase1/fdiskadd.h"
#include "Fase1/fdiskdelete.h"
#include "Fase1/rmdisk.h"
#include "Fase1/fdisk.h"
//Para el mount

//Para Los Fit


class Menu
{
public:
    //Loss
    void Loss(std::string IDMontado);
    //Recovery
    void Recuperar(std::string IDMontado);
    void SubRecuperar(std::queue<JOR> Cola);
    //CP
    void CP(const char *PathOrigen,const char *PathDestino);
    //MV
    void MV(const char *PathOrigen,const char *PathDestino);
    //FIND
    void FIND(const char *PathVirtual,const char *Nombre);
    //CHGRP
    void CHGRP(const char *Usr,const char *NuevoGrupo);
    //CHOWN
    //Tipo 1=Normal  Tipo 2=Recursivo
    void CHOWN(const char *PathVirtual,std::string NuevoDuenio,int Tipo);
    //REN
    void REN(const char *PathVirtual,const char *NuevoNombre);
    //CHMOD
    //Tipo 1=Normal  Tipo 2=Recursivo
    void CHMOD(const char *PathVirtual,int Ugo,int Tipo);
    //MKUSR
    void MKUSR(const char *USR,const char *Pwd,const char *Grp);
    //RMUSRT
    void RMUSR(const char *USR);
    //MKGRP
    void RMGRP(const char *Nombre);
    //MKGRP
    void MKGRP(const char *Nombre);
    //REM
    void REM(const char *Path);
    //LOGOUT
    void Logout();
    //LOGIN
    void LOGIN(const char *Usr,const char *Pwd,const char *Id);
    //EDIT
    void EDIT(const char *Path,const char *Contenido);
    //CAT
    std::string CAT(const char *Path);
    //MKFILE
    void MKFILE(const char *Path, char Padre,const char *Contenido);
    //MKDIR
    void MKDIR(const char *Path, char Padre);
    //MKFS
    void MKFS(const char *Id,int Type,int Tipo);
    //REP
    void REP(const char *Id, const char *Name, const char *Path,const char *Ruta);

    //AGREGAR
    void FDISKAdd(int Size,const char *Path,const char *Name);
    //MONTAR
    void UNMOUNT(const char *Name);
    void MOUNT(const char *Path,const char *Name);
    //RMDISK
    void Rmdisk(const char *Path);
    //MKDsik
    void Mkdisk(int Size,const char Fit[2],char Unit,const char *Path);
    //FDisk
    void FDisk(int Size,const char Fit[2],char Unit,const char *Path,char Type,const char *Name);
    void FDISKDelete(const char *Delete,const char *Path,const char *Name);
    //Menu

    Menu();
private:


    void LimpiarDiscosVacios();

    OperacionUsuario *OpeU= new OperacionUsuario();
    Functions *Fun=  new Functions();
    Reports *Repo=  new Reports();
    Disco *PrimerDisco = nullptr;






    int HasBytes(const char *Path);

    void Resize();
    void DeleteParth();
    //Utilidades

    void NewMenu();




};

#endif // MENU_H
