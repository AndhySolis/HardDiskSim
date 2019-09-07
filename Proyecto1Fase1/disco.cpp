#include "disco.h"
#include "reports.h"
#include "ext.h"
void Disco::FormatearParticion(const char *Nombre, int Tipo){
    Disco *Tempo=this;
    while (Tempo!=nullptr) {

        for (int i=0;i<Tempo->Lista.count();i++) {
            MOU Te= Lista.at(i);
            std::string NombreParti=Tempo->Apodo+std::to_string(Te.Numero);
            if(Fun->IF(NombreParti,Nombre)){
                EXT *E = new EXT();
                std::string Path=Tempo->Path;
                int TamanioStruct;
                int TamanioParticion;
                int Comienzo;
                //Es Logica
                if(Te.EsLogica){
                    TamanioStruct=int(sizeof(EBR));
                    TamanioParticion=Te.Logica.part_size;
                    Comienzo=Te.Logica.part_start;
                }else{
                    //TamanioStruct=int(sizeof(EBR));
                    TamanioStruct=0;
                    TamanioParticion=Te.Particion.part_size;
                    Comienzo=Te.Particion.part_start;
                }

                //Tipo De Formato
                if(Tipo==1){
                    E->EstructurarFormatoEXT2(Comienzo,TamanioParticion,TamanioStruct,Path);
                    std::cout<<"Se Formateo La Particion "<<Nombre<<" Con El Formato EXT2 Del Disco Ubicado En "<<Tempo->Path<<std::endl;
                }else{
                    E->EstructurarFormatoEXT3(Comienzo,TamanioParticion,TamanioStruct,Path);
                    std::cout<<"Se Formateo La Particion "<<Nombre<<" Con El Formato EXT3 Del Disco Ubicado En "<<Tempo->Path<<std::endl;
                }

                return;
            }
        }
        Tempo=Tempo->Siguiente;
    }

    std::cout<<"No Se Encontro La Particion Para Formatear "<<Nombre<<std::endl;
}
Disco::Disco(std::string Path,Disco *Nuevo)
{
    this->Path=Path;
    this->Siguiente=Nuevo;
    this->Apodo="vd"+this->GenerarApodo();
}
std::string Disco::GenerarApodo(){
    if(Siguiente==nullptr){
        this->Num=0;
        return this->NumeroAString(0);
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
    if(Fun->ExisteArchivo(Path.data())){
        FILE *f;
        MBR Main;
        f=fopen(Path.data(),"r+");
        if (!f){
            return;
        }
        fread(&Main,sizeof(MBR),1,f);
        fclose(f);
        int ParIndex=Fun->SearchPAR(Nombre,Path.data());

        if(ParIndex==-1){
           EBR Logic=Fun->SearchEBR(Nombre,Path.data());
            if(Logic.part_status=='\0'){
                std::cout<<"No Se Encontro La Particion "<<Nombre<<" En El Disco De  "<<this->Path<<std::endl;
                return;
            }else{//Es Logica
                Mont.EsLogica=true;
                Mont.Logica=Logic;
            }
        }else{
            //Es Primario O Extendida
            Mont.EsLogica=false;
            PAR Part=Main.mbr_partition[ParIndex];
            Mont.Particion=Part;
        }
        Mont.Numero=this->Lista.count()+1;
        this->Lista<<Mont;
        std::cout<<"Se monto la particion:'"<<Nombre << "'  con el alias:'"<<this->Apodo<<Mont.Numero<<"' En El Disco De  "<<this->Path<<std::endl ;
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
bool Disco::DiscoLibreParaBorrar(const char *Nombre){
    Disco *Tempo=this;
    while (Tempo!=nullptr) {
            if(Fun->IF(Tempo->Path,Nombre)){
                    return false;
            }
        Tempo=Tempo->Siguiente;
    }
    return true;
}
bool Disco::ParticionLibreParaBorrar(const char *Nombre){
    Disco *Tempo=this;
    while (Tempo!=nullptr) {

        for (int i=0;i<Tempo->Lista.count();i++) {
            MOU Te= Lista.at(i);
            std::string NombreParti=Tempo->Apodo+std::to_string(Te.Numero);
            if(Fun->IF(NombreParti,Nombre)){
                    return false;
            }
        }
        Tempo=Tempo->Siguiente;
    }
    return true;
}
void Disco::Reporte(const char *ID, const char *Path, const char *Tipo){
    Disco *Tempo=this;
    while (Tempo!=nullptr) {
        for (int i=0;i<Tempo->Lista.count();i++) {
            MOU Te= Lista.at(i);
            std::string NombreParti=Tempo->Apodo+std::to_string(Te.Numero);
            if(Fun->IF(NombreParti,ID)){
                Reports *R= new Reports();
                if(Fun->IF(Tipo,"disk")){
                    R->Graphviz(Tempo->Path.data(),Path);
                }else if(Fun->IF(Tipo,"mbr")){
                    //Tipo De Reporet eEBR o MBR
                    if(!Te.EsLogica){
                        R->ReporteTablaMBR(Tempo->Path.data(),Path,Te.Numero);
                    }else{                       
                        R->ReporteTablaEBR(Te.Logica,Path,Te.Numero);
                    }

                }else{
                    Fun->Out("Impos");
                }
                delete(R);
                return;
            }
        }
        Tempo=Tempo->Siguiente;
    }
    std::cout<<"No Se Encontro La Particion "<<ID<<std::endl;


}
