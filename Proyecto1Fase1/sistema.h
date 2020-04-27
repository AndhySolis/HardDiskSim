#ifndef SISTEMA_H
#define SISTEMA_H
#include "menu.h"

class Sistema
{
public:
    //FASE 2
    //1 MKFS
    void Mkfs(std::string Ejecutar,std::string Type,std::string Ext);
    //2 LOGIN
    void Login(std::string Usr,std::string Pwd,std::string Id);
    //3 LOGOUT
    void Logout();
    //4 Mkgrp
    void Mkgrp(std::string Grp);
    //5 Rmgrp
    void Rmgrp(std::string Grp);
    //6 Mkusr
    void Mkusr(std::string Usr,std::string Pwd,std::string Grp);
    //7 Rmusr
    void Rmusr(std::string Usr);
    //8 Chmod
    void Chmod(std::string Path,std::string Ugo,std::string R);
    //9 MKFILE
    void Mkfile(std::string Path,std::string P,std::string Num,std::string Cont);
    //10 CAT
    void Cat(std::string Path);
    //11 REM
    void Rem(std::string Path);
    //12 Edit
    void Edit(std::string Path,std::string Cont);
    //13 REN
    void Ren(std::string Path,std::string Name);
    //14 MKDIR
    void Mkdir(std::string Path,std::string P);
    //15
    void Cp(std::string Path,std::string Dest);
    //16
    void Mv(std::string Path,std::string Dest);
    //17
    void Find(std::string Path,std::string Name);
    //18
    void Chown(std::string Path,std::string R,std::string Usr);
    //19
    void Chgrp(std::string Usr,std::string Grp);
    //20
    void Recovery(std::string Id);
    //21
    void Loss(std::string Id);
    //



    //FASE 1
    void Ejecutar(std::string Ejecutar);
    void CrearDirectorio(std::string Conte);
    std::string SplitRaid(std::string Conte);
    void Crear(int Size,char Unit, char Fit[2],std::string Path);
    void BorrarDisco(std::string Path);
    //Borrar Disco
    void Formato(int Size, char Fit[2],char Unit,std::string Path,char Type,std::string Name);
    void Aumentar(int Size, std::string Path, std::string Name, char Unit);
    void Borrar(std::string Delete,std::string Path,std::string Name);
    //Borrar Particion
    void Reportes(std::string Id, std::string  Name,std::string Path,std::string Ruta);
    void Montar(std::string Path, std::string  Name);
    void Desmontar(std::string  Name);
    Sistema();
private:
Functions *Func;
Menu *M;
};

#endif // SISTEMA_H
