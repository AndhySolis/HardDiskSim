#include <QCoreApplication>
#include "menu.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include "structs.h"
#include "parser.h"

#include "functions.h"
#include "sistema.h"



//int size = 1024;Un KiloByte
/* random record description - could be anything */
extern int yyrestart( FILE* archivo);//METODO QUE PASA EL ARCHIVO A FLEX
extern int yyparse();


int main()
{


   /* Functions *Fu = new Functions();
    Sistema *Ex= new Sistema();
    while (true) {

        std::cout<<"--------------MANEJO DE RAID---------------"<<std::endl;
        std::cout<<"Ingrese La Ubicacion Del Archivo A Procesar O Escriba Salir Para Salir"<<std::endl;
        std::string Exec;
        std::cin >> Exec;

        if(Fu->IF("salir",Exec)){
            std::cout<<"Saliendo Del Programa"<<std::endl;
            return 1;
        }
        Ex->Ejecutar(Exec);
    }
*/


    /*Functions *Fun = new Functions();
    ALE Num;
    Num.Num=20;
    Num.Siguiente=false;
    FILE *f;
    if(Fun->ExisteArchivo("Info.inf"))
        f=fopen("Info.inf","r+");
    else
        f=fopen("Info.inf","w");


    fseek(f,0,SEEK_SET);
    fread(&Num,sizeof(ALE),1,f);

*/

    //

    /*
    const char* x = "/home/linuxlite/Documents/Archivos/temp.txt";
    FILE* input = fopen(x, "r" );
    yyrestart(input);//SE PASA LA CADENA DE ENTRADA A FLEX
    yyparse();//SE INICIA LA COMPILACION*/


    //std::string age;
    //std::cin >> age;
    //M();
}


