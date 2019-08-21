%{
#include "parser.h"  //se importa el header del analisis sintactico
#include "qdebug.h"
#include <iostream>
#include <stdio.h>
#include <string.h>

extern int yylineno; //linea actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern int columna; //columna actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern char *yytext; //lexema actual donde esta el parser (analisis lexico) lo maneja BISON



int yyerror(const char* mens)
{

    std::cout << mens <<" "<<yytext<< std::endl;
    return 0;
}
%}
//error-verbose si se especifica la opcion los errores sintacticos son especificados por BISON
%defines "parser.h"
%output "parser.cpp"
%error-verbose
%locations

%union{
//se especifican los tipo de valores para los no terminales y lo terminales
char TEXT [256];
}

//TERMINALES DE TIPO TEXT, SON STRINGS
%token<TEXT> entero;
%token<TEXT> cadena;
%token<TEXT> identificador;
%token<TEXT> letra;
%token<TEXT> comentario;
%token<TEXT> direccion;
%token<TEXT> igual;
%token<TEXT> mkdisk;
%token<TEXT> rmdisk;
%token<TEXT> fdisk;
%token<TEXT> mount;
%token<TEXT> unmount;
%token<TEXT> rep;

%token<TEXT> size;
%token<TEXT> fit;
%token<TEXT> unit;
%token<TEXT> path;
%token<TEXT> typep;
%token<TEXT> deletep;
%token<TEXT> name;
%token<TEXT> add;
%token<TEXT> id;

/*No terimanesl*/
%type<TEXT> PROGRAMA;
%type<TEXT> FORMATO;
%type<TEXT> CREAR;
%type<TEXT> BORRAR;
%type<TEXT> MONTAR;
%type<TEXT> DESMONTAR;
%type<TEXT> OPCION;
%type<TEXT> TERMIDIRECC;
%type<TEXT> REPORTES;





%start PROGRAMA
%%

PROGRAMA: PROGRAMA OPCION {}
	|OPCION{}
;
OPCION:CREAR
	|BORRAR
	|FORMATO
	|MONTAR
	|DESMONTAR
	|REPORTES
;

CREAR:CREAR size igual entero
	|CREAR fit igual letra letra
	|CREAR unit igual letra
	|CREAR path igual TERMIDIRECC
	|mkdisk 
;
BORRAR: rmdisk path igual TERMIDIRECC
;

TERMIDIRECC:direccion
	|cadena
;


FORMATO:FORMATO size igual entero
	|FORMATO fit igual letra letra
	|FORMATO unit igual letra
	|FORMATO path igual TERMIDIRECC
	|FORMATO typep igual letra
	|FORMATO deletep igual identificador
	|FORMATO name igual TERMIIDENTI
	|FORMATO add igual entero
	|fdisk 	
;

TERMIIDENTI:identificador
	|cadena
;

MONTAR:MONTAR path igual TERMIDIRECC
	|MONTAR name igual TERMIIDENTI
	|mount
;

DESMONTAR: unmount id igual identificador
;
REPORTES:REPORTES id igual identificador
	|REPORTES path igual TERMIDIRECC
	|REPORTES name igual identificador
	|rep {}
;

%%
