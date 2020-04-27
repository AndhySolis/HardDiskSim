#include "rmdisk.h"

RMDISK::RMDISK(const char *Path)
{
    this->Fun=new Functions();
    if(Fun->ExisteArchivo(Path)==false){
        std::cout<<"No Existe La Ubicacion "<<Path<<std::endl;
        return;
    }

    if(this->DisponibleBorrarDisco(Path)==false){
        std::cout<<"No se puede borrar disco porque esta montado en memoria"<<std::endl;
        return;
    }

       if(remove(Path)== 0) {
          std::cout<<"Disco Borrado"<<std::endl;
       } else {
         std::cout<<"No Se Pudo Borrar El Disco El Archivo Esta En Uso "<<std::endl;
       }
}
bool RMDISK::DisponibleBorrarDisco(const char *Path){
    this->PrimerDisco=PrimerDisco;
    if(this->PrimerDisco==nullptr){
            return true;
    }else{
        return this->PrimerDisco->DiscoLibreParaBorrar(Path);
    }

}
