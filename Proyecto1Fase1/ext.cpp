#include "ext.h"
#include "structsext.h"

int EXT::CalcularCantidad(int Tamanio,int Tipo){
    int PesoEstructuras=0;
    //Tipo  1 EXT2  Tipo 2 EXT3
    if(Tipo==1)
      PesoEstructuras=4+3*int(sizeof (BCA))+int(sizeof (BCA));
    else
      PesoEstructuras=4+3*int(sizeof (BCA))+int(sizeof (BCA))+int(sizeof (JOR));
    Tamanio = Tamanio-int(sizeof (SPB));
    return Tamanio%PesoEstructuras;
}
void EXT::EstructurarFormatoEXT2(int ComienzoParticion, int TamanioParticion, int TamanioStruct, std::string Path){
    int Cantidad= CalcularCantidad(TamanioParticion,1);
    int ComienzoEscritura=ComienzoParticion+TamanioStruct;

    std::cout<<ComienzoParticion<<std::endl;

}
void EXT::EstructurarFormatoEXT3(int ComienzoParticion, int TamanioParticion, int TamanioStruct, std::string Path){


}
EXT::EXT()
{

}
