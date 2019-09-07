#ifndef EXT_H
#define EXT_H
#include <iostream>

class EXT
{
public:
    //Calcular la cantidad de estructruas
    int CalcularCantidad(int Tamanio,int Tipo);
    //CrearFormato

    void EstructurarFormatoEXT2(int ComienzoParticion,int TamanioParticion,int TamanioStruct,std::string Path);
    void EstructurarFormatoEXT3(int ComienzoParticion,int TamanioParticion,int TamanioStruct,std::string  Path);
    EXT();
};

#endif // EXT_H
