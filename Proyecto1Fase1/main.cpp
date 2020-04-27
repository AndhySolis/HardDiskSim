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



    printf("\n");



    Functions *Fu = new Functions();
    while (true) {
        std::cout<<"\x1B[32m"<<"--------------MANEJO DE RAID---------------"<<std::endl;
        std::cout<<"Ingrese El Comando , Escriba Salir O Limpiar "<<std::endl;
        char Exec[1000];
        std::cin.getline(Exec,1000);



        if(Fu->IF("salir",Exec)){
            std::cout<<"Saliendo Del Programa"<<std::endl;
            return 1;
        }else if(Fu->IF("limpiar",Exec)){
            std::system("clear");
        }else{
            std::ofstream Archivo("salida.txt");
            Archivo <<Exec;
            //Archivo<<"exec -path=/home/pc/Desktop/Fase.sh";
            //Archivo<<"exec -path=/home/archivos/Fase.sh";
            Archivo.close();
            const char* x = "salida.txt";

            FILE* input = fopen(x, "r" );
            yyrestart(input);
            yyparse();

            //return 1;
        }
    }




}


