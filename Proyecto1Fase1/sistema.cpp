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
void Sistema::CrearDirectorio(std::string Conte){
    std::cout<<"CREAR DIRECTORIO DESACTIVADO WINDOWS, PROBLEMA CON CREAR CARPETAS  ESTA ELIMINADO"<<std::endl;
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
        }
        s.erase(0, pos + delimiter.length());
    }
   /* if (mkdir(Escritura.data(), 0777) == -1){

    }*/
    /*else{
        std::cout <<" Directorio: "<<Escritura<<"No Existia Fue Creado"<<std::endl;
    }*/

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
        std::cout<<"No Existe Un Disco En La Ubicacion "<<Ejecutar<<std::endl;
        return;
    }else{
        const char* x = Ejecutar.data();
        FILE* input = fopen(x, "r" );
        yyrestart(input);//SE PASA LA CADENA DE ENTRADA A FLEX
        yyparse();//SE INICIA LA COMPILACION
    }
    std::cout<<"-----------------------------------"<<std::endl;
}

void Sistema::Crear(int Size, char Unit, char Fit[],  std::string  Path){
    std::cout<<"--------------MKDISK---------------"<<std::endl;
    CrearDirectorio(Path);
    M->Mkdisk(Size,Fit,Unit,Path.data());
    M->Mkdisk(Size,Fit,Unit,SplitRaid(Path).data());
    std::cout<<"-----------------------------------"<<std::endl;
}
void Sistema::BorrarDisco(std::string Path){
    std::cout<<"--------------RMDISK---------------"<<std::endl;
    M->RMDISK(Path.data());
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
void Sistema::Reportes(std::string Id, std::string Name, std::string Path){
    std::cout<<"-------------REPORTES--------------"<<std::endl;

    M->REP(Id.data(),Name.data(),Path.data());    
    if (Func->ExisteArchivo(Path.data())) {
        std::cout<<"Reporte De:"<<Id<<" De Tipo: "<<Name<<" Existe En:"<<Path<<std::endl;
    }else{
        std::cout<<"No Se Pudo Crear El Reporte En "<<Path<<std::endl;

    }
    std::cout<<"-----------------------------------"<<std::endl;
}
Sistema::Sistema(){
    this->M=new Menu();
    this->Func = new Functions();
}
