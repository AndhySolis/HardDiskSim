#include "disco.h"

Disco::Disco(const char *Path,Disco *Nuevo)
{
    this->Path=Path;
    this->Siguiente=Nuevo;
    this->Apodo="VD"+this->GenerarApodo();
}
std::string Disco::GenerarApodo(){
    if(Siguiente==nullptr){
        this->Num=0;
        return this->GenerarApodo();
    }else{
        this->Num=Siguiente->Num+1;
        if(Num/26>0){
            return this->NumeroAString(Num/26)+this->NumeroAString(Num%26);
        }else {
            return this->NumeroAString(Num%26);
        }
    }
}
void Disco::AgregarParticion(const char *Nombre){
    MOU Mont;
    Mont.Particion=nullptr;
    Mont.Logica=nullptr;
    if(Fun->ExisteArchivo(Path)){
        FILE *f;
        MBR Main;
        f=fopen(Path,"r+");
        if (!f){
            return;
        }
        fread(&Main,sizeof(MBR),1,f);
        fclose(f);
        int ParIndex=Fun->SearchPAR(Nombre,Path);

        if(ParIndex==-1){
           EBR Logic=Fun->SearchEBR(Nombre,Path);
            if(Logic.part_status=='\0'){
                std::cout<<"No Se Encontro La Particion "<<Nombre<<std::endl;
                return;
            }else{//Es Logica
                Mont.Logica=&Logic;
            }
        }else{
            //Es Primario O Extendida
            PAR Part=Main.mbr_partition[ParIndex];
            Mont.Particion=&Part;
        }
        Mont.Numero=this->Lista.count()+1;
        this->Lista<<Mont;
        std::cout<<"Se ha montado una nueva partcion con el alias de "<<this->Apodo<<Mont.Numero<<std::endl;
    }
    else
    {
        std::cout<<"No Se Encontro Un Archivo En La Ubicación "<<Path<<std::endl;
    }

}
std::string Disco::NumeroAString(int Num){
    std::string Salida(1, char(97+Num));    
    return Salida;
}
void Disco::BorrarParticion(const char *Nombre){
    Disco *Tempo=this;
    while (Tempo!=nullptr) {

        for (int i=0;i<Tempo->Lista.count();i++) {
            MOU Te= Lista.at(i);
            std::string NombreParti=Tempo->Apodo+std::to_string(Te.Numero);
            if(Fun->IF(NombreParti,Nombre)){
                this->Lista.removeAt(i);
                std::cout<<"Se Borro La Particion "<<Nombre<<" De Memoria Del Disco En Ubicacion "<<Tempo->Path<<std::endl;
                return;
            }
        }
        Tempo=Tempo->Siguiente;
    }

    std::cout<<"No Se Encontro La Particion "<<Nombre<<std::endl;
}

void Disco::BuscarDisco(const char *Nombre){
    Disco *Tempo=this;
    while (Tempo!=nullptr) {

        for (int i=0;i<Tempo->Lista.count();i++) {
            MOU Te= Lista.at(i);
            std::string NombreParti=Tempo->Apodo+std::to_string(Te.Numero);
            if(Fun->IF(NombreParti,Nombre)){


            }
        }
        Tempo=Tempo->Siguiente;
    }

    std::cout<<"No Se Encontro La Particion "<<Nombre<<std::endl;
}

void Disco::Reporte(const char *ID, const char *Path, const char *Tipo){
    Disco *Tempo=this;
    while (Tempo!=nullptr) {

        for (int i=0;i<Tempo->Lista.count();i++) {
            MOU Te= Lista.at(i);
            std::string NombreParti=Tempo->Apodo+std::to_string(Te.Numero);
            if(Fun->IF(NombreParti,ID)){

                return;
            }
        }
        Tempo=Tempo->Siguiente;
    }
    std::cout<<"No Se Encontro La Particion "<<ID<<std::endl;


}
