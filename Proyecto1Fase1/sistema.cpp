#include "sistema.h"
#include "parser.h"
#include "menu.h"
#include "parser.h"
#include "functions.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <sstream>

#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>

extern int yyrestart( FILE* archivo);//METODO QUE PASA EL ARCHIVO A FLEX
extern int yyparse();
//FASE 2
// 1
void Sistema::Mkfs(std::string Ejecutar, std::string Type,std::string Ext){
    std::cout<<"--------------MKFS---------------"<<std::endl;
    int TExt=0;//2fs
    int Tipo=0;//Fast
    if(Func->IF(Type,"full"))
        Tipo=1;

    if(Func->IF(Ext,"3fs"))
        TExt=1;

        M->MKFS(Ejecutar.data(),Tipo,TExt);
    std::cout<<"-----------------------------------"<<std::endl;
}
//2
void Sistema::Login(std::string Usr, std::string Pwd, std::string Id){
    std::cout<<"--------------Login---------------"<<std::endl;
    M->LOGIN(Usr.data(),Pwd.data(),Id.data());
    std::cout<<"-----------------------------------"<<std::endl;
}
//3
void Sistema::Logout(){
    std::cout<<"--------------LOGOUT---------------"<<std::endl;
    M->Logout();
    std::cout<<"-----------------------------------"<<std::endl;

}
//4
void Sistema::Mkgrp(std::string Grp){
    std::cout<<"--------------MKGRP---------------"<<std::endl;
    M->MKGRP(Grp.data());
    std::cout<<"-----------------------------------"<<std::endl;

}
//5
void Sistema::Rmgrp(std::string Grp){
    std::cout<<"--------------RMGRP---------------"<<std::endl;
    M->RMGRP(Grp.data());
    std::cout<<"-----------------------------------"<<std::endl;
}
//6
void Sistema::Mkusr(std::string Usr, std::string Pwd, std::string Grp){
    std::cout<<"--------------MKUSR---------------"<<std::endl;
    M->MKUSR(Usr.data(),Pwd.data(),Grp.data());
    std::cout<<"-----------------------------------"<<std::endl;
}
//7
void Sistema::Rmusr(std::string Usr){
    std::cout<<"--------------RMUSR---------------"<<std::endl;
    M->RMUSR(Usr.data());
    std::cout<<"-----------------------------------"<<std::endl;
}
//8
void Sistema::Chmod(std::string Path, std::string Ugo, std::string R){
    std::cout<<"--------------CHMOD---------------"<<std::endl;
    int Tipo=0;
    if(R[0]=='1')
        Tipo=1;
    M->CHMOD(Path.data(),std::atoi(Ugo.data()),Tipo);
    std::cout<<"-----------------------------------"<<std::endl;
}
//9
void Sistema::Mkfile(std::string Path, std::string P, std::string Num, std::string Cont){
    std::cout<<"--------------MKFILE---------------"<<std::endl;
    std::string Contenido="";

    bool RutaVacio=  Func->IF(Cont,"");
    if(!RutaVacio){
        bool Valido=Func->ExisteArchivo(Cont.data());
        if(Valido){
            std::ifstream file(Cont);//Lectura
            std::string str;
            while (std::getline(file, str)) {
              Contenido=Contenido+str;
              }
        }else{
            std::cout<<"El Archivo En La Ruta       "<<Cont<<"No Existe"<<std::endl;
        }
    }

    if((!Func->IF(Num,"0")) && RutaVacio){
        Contenido="";
        int Tamanio=std::atoi(Num.data());//Tamaños

        if(Tamanio<0){
            std::cout<<"El Tamanio Especificado Es Negativo  MKFILE RUTA:   "<<Path<<"  Numero  "<<Num<<std::endl;
            return ;
        }

        for (int i=0;i<Tamanio;i++) {
            Contenido=Contenido+"0";
        }
    }
    //std::cout<<Contenido<<std::endl;
    M->MKFILE(Path.data(),P[0],Contenido.data());

    std::cout<<"-----------------------------------"<<std::endl;
}
//10
void Sistema::Cat(std::string Path){
    std::cout<<"--------------CAT---------------"<<std::endl;
    std::cout<<M->CAT(Path.data())<<std::endl;
    std::cout<<"-----------------------------------"<<std::endl;
}
//11
void Sistema::Rem(std::string Path){
    std::cout<<"--------------REM------------------"<<std::endl;
    M->REM(Path.data());
    std::cout<<"-----------------------------------"<<std::endl;

}
//12
void Sistema::Edit(std::string Path, std::string Cont){
    std::cout<<"--------------EDIT------------------"<<std::endl;
    M->EDIT(Path.data(),Cont.data());
    std::cout<<"-----------------------------------"<<std::endl;
}
//13
void Sistema::Ren(std::string Path, std::string Name){
    std::cout<<"--------------EDIT------------------"<<std::endl;
    M->REN(Path.data(),Name.data());
    std::cout<<"-----------------------------------"<<std::endl;
}
//14
void Sistema::Mkdir(std::string Path, std::string P){
    std::cout<<"--------------MKDIR---------------"<<std::endl;
    M->MKDIR(Path.data(),P[0]);
    std::cout<<"-----------------------------------"<<std::endl;
}
//15
void Sistema::Cp(std::string Path, std::string Dest){
    std::cout<<"--------------CP---------------"<<std::endl;
    M->CP(Path.data(),Dest.data());
    std::cout<<"-----------------------------------"<<std::endl;
}
//16
void Sistema::Mv(std::string Path, std::string Dest){
    std::cout<<"--------------MV---------------"<<std::endl;
    M->MV(Path.data(),Dest.data());
    std::cout<<"-----------------------------------"<<std::endl;
}
//17
void Sistema::Find(std::string Path, std::string Name){
    std::cout<<"--------------FIND---------------"<<std::endl;
    M->FIND(Path.data(),Name.data());
    std::cout<<"-----------------------------------"<<std::endl;
}
//18
void Sistema::Chown(std::string Path, std::string R, std::string Usr){
    std::cout<<"--------------CHOWN---------------"<<std::endl;
    int Tipo=0;
    if(Func->IF("1",R))
        Tipo=1;
    M->CHOWN(Path.data(),Usr.data(),Tipo);
    std::cout<<"-----------------------------------"<<std::endl;
}
//19
void Sistema::Chgrp(std::string Usr, std::string Grp){
    std::cout<<"--------------CHGRP---------------"<<std::endl;
    M->CHGRP(Usr.data(),Grp.data());
    std::cout<<"-----------------------------------"<<std::endl;
}
//20
void Sistema::Recovery(std::string Id){
    std::cout<<"--------------RECOVERY---------------"<<std::endl;
    M->Recuperar(Id);
    std::cout<<"-----------------------------------"<<std::endl;
}
//21
void Sistema::Loss(std::string Id){
    std::cout<<"--------------RECOVERY---------------"<<std::endl;
    M->Loss(Id);
    std::cout<<"-----------------------------------"<<std::endl;
}
//
//FASE 1
void Sistema::CrearDirectorio(std::string Conte){
    std::string s = Conte;
    std::string delimiter = "/";
    size_t pos = 0;
    std::string token;

    std::string Escritura="";


    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        if(this->Func->IF("",token)){

        }else{
            Escritura=Escritura+"/"+token;

            if (mkdir(Escritura.data(), 0777) == -1){

            }
            else{
                std::cout <<" Directorio: "<<Escritura<<" No Existia Fue Creado"<<std::endl;
            }
        }
        s.erase(0, pos + delimiter.length());
    }


}
std::string Sistema::SplitRaid(std::string Conte){

    std::string s = Conte;
    std::string delimiter = ".";
    size_t pos = 0;
    std::string token;
    std::string Escritura="";
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        Escritura=token+"_"+"ra1.disk";
        s.erase(0, pos + delimiter.length());
    }
    return Escritura;
}
void Sistema::Ejecutar(std::string  Ejecutar){
    std::cout<<"--------------EXEC---------------"<<std::endl;

    if(Func->ExisteArchivo(Ejecutar.data())==false){
        std::cout<<"No Existe Un Archivo En La Ubicacion "<<Ejecutar<<std::endl;
        return;
    }else{


        FILE* input = fopen(Ejecutar.data(), "r" );
        yyrestart(input);//SE PASA LA CADENA DE ENTRADA A FLEX
        yyparse();//SE INICIA LA COMPILACION
        fclose(input);

/*
          std::ifstream file(Ejecutar);
          std::string str;
          Functions *F = new Functions();
          while (std::getline(file, str)) {
            if(!F->IF("",str)){
                std::ofstream Archivo("exec.txt");
                Archivo <<str;
                Archivo.close();
                std::cout<<"Ejecutando "<<std::endl<<std::endl;
                std::cout<<std::endl<<"{"<<str<<"}"<<std::endl;
                FILE* input = fopen("exec.txt", "r+" );
                //input = fopen("exec.txt", "r" );
                yyrestart(input);//SE PASA LA CADENA DE ENTRADA A FLEX
                yyparse();//SE INICIA LA COMPILACION
                fclose(input);
            }
          }*/




    }
    std::cout<<"-----------------------------------"<<std::endl;
}

void Sistema::Crear(int Size, char Unit, char Fit[],  std::string  Path){
    std::cout<<"--------------MKDISK---------------"<<std::endl;
    CrearDirectorio(Path);
    std::cout<<Path<<std::endl;
    M->Mkdisk(Size,Fit,Unit,Path.data());
    M->Mkdisk(Size,Fit,Unit,SplitRaid(Path).data());
    std::cout<<"-----------------------------------"<<std::endl;
}
void Sistema::BorrarDisco(std::string Path){
    std::cout<<"--------------RMDISK---------------"<<std::endl;
    std::string Confirmacion;
    std::cout<<"Desea Eliminar La Particion (s/n)"<<std::endl;
    std::cin>>Confirmacion;
    if(Func->IF(Confirmacion,"s")){
        std::cout<<"Se Procedera A Eliminar"<<std::endl;
        M->Rmdisk(Path.data());
    }else{
        std::cout<<"Eliminacion de disco CANCELADA por parte del usuario"<<std::endl;
    }
    std::cout<<"-----------------------------------"<<std::endl;
}
void Sistema::Formato(int Size, char Fit[2], char Unit, std::string Path, char Type, std::string Name){
    std::cout<<"--------FDISK---DAR---FORMATO------"<<std::endl;
    if(Func->ExisteArchivo(Path.data())==false){
        std::cout<<"No Existe Un Disco En La Ubicacion "<<Path<<std::endl;
        return;
    }else{
    M->FDisk(Size,Fit,Unit,Path.data(),Type,Name.data());
    M->FDisk(Size,Fit,Unit,SplitRaid(Path).data(),Type,Name.data());
    }
    std::cout<<"-----------------------------------"<<std::endl;
}
void Sistema::Borrar(std::string Delete, std::string Path, std::string Name){
    std::cout<<"---------FDISK-----DELETE---------"<<std::endl;
    if(Func->ExisteArchivo(Path.data())==false){
        std::cout<<"No Existe Un Disco En La Ubicacion "<<Path<<std::endl;
        return;
    }else{
    M->FDISKDelete(Delete.data(),Path.data(),Name.data());
    M->FDISKDelete(Delete.data(),SplitRaid(Path).data(),Name.data());
    }
    std::cout<<"-----------------------------------"<<std::endl;
}
void Sistema::Aumentar(int Size, std::string Path, std::string Name, char Unit){
    std::cout<<"-----------FDISK----ADD------------"<<std::endl;
    if(Func->ExisteArchivo(Path.data())==false){
        std::cout<<"No Existe Un Disco En La Ubicacion "<<Path<<std::endl;
        return;
    }else{
    Size=Func->Mult(Size,Unit);
        M->FDISKAdd(Size,Path.data(),Name.data());
        M->FDISKAdd(Size,SplitRaid(Path).data(),Name.data());
    }
    std::cout<<"-----------------------------------"<<std::endl;
}
void Sistema::Montar(std::string  Path, std::string  Name){
    std::cout<<"------------MOUNT------------------"<<std::endl;
    if(Func->ExisteArchivo(Path.data())==false){
        std::cout<<"No Existe Un Disco En La Ubicacion "<<Path<<std::endl;
        return;
    }else{
    M->MOUNT(Path.data(),Name.data());

    }
    std::cout<<"-----------------------------------"<<std::endl;
}
void Sistema::Desmontar(std::string Name){
    std::cout<<"-----------UNMOUNT-----------------"<<std::endl;
    M->UNMOUNT(Name.data());
    std::cout<<"-----------------------------------"<<std::endl;
}
void Sistema::Reportes(std::string Id, std::string Name, std::string Path,std::string Ruta){
    std::cout<<"-------------REPORTES--------------"<<std::endl;
    CrearDirectorio(Path);
    M->REP(Id.data(),Name.data(),Path.data(),Ruta.data());
    if(Func->IF(Ruta,"")){
        if (Func->ExisteArchivo((Path+".png").data()) ||Func->ExisteArchivo((Path+".txt").data())) {
            std::cout<<"Reporte De:"<<Id<<" De Tipo: "<<Name<<" Existe En:"<<Path<<std::endl;
        }else{
            std::cout<<"No Se Pudo Crear El Reporte En "<<Path<<std::endl;

        }
    }else{
        if (Func->ExisteArchivo(Ruta.data())) {
            std::cout<<"Reporte De:"<<Id<<" De Tipo: "<<Name<<" Existe En:"<<Ruta<<std::endl;
        }else{
            std::cout<<"No Se Pudo Crear El Reporte En "<<Ruta<<std::endl;

        }
    }

    std::cout<<"-----------------------------------"<<std::endl;
}
Sistema::Sistema(){
    this->M=new Menu();
    this->Func = new Functions();
}
