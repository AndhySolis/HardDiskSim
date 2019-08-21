#include <QCoreApplication>
#include "menu.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include "parser.h"
#include <stdio.h>
//int size = 1024;Un KiloByte
/* random record description - could be anything */
extern int yyrestart( FILE* archivo);//METODO QUE PASA EL ARCHIVO A FLEX
extern int yyparse();
struct rec
{
    int x,y,z,*d;
};


int main()
{
    new Menu();


    /*const char* x = "/home/linuxlite/Documents/Archivos/temp.txt";
    FILE* input = fopen(x, "r" );
    yyrestart(input);//SE PASA LA CADENA DE ENTRADA A FLEX
    yyparse();//SE INICIA LA COMPILACION*/


    //std::string age;
    //std::cin >> age;
    //M();
}


