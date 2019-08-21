%{
#include "scanner.h"//se importa el header del analisis sintactico

#include <iostream> //libreria para imprimir en cosola de C
#include "menu.h"
#include <QString> //libreria para manejo de STRINGS de QT
#include "structs.h"



extern int yylineno; //linea actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern int columna; //columna actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern char *yytext; //lexema actual donde esta el parser (analisis lexico) lo maneja BISON
//Menu *Ope = new Menu();
int yyerror(const char* mens){
//metodo que se llama al haber un error sintactico
//SE IMPRIME EN CONSOLA EL ERROR
std::cout <<mens<<" "<<yytext<< std::endl;
return 0;
}






struct STRCREAR{
	int Size;
	char Unit;
	char Fit[2]={'f','f'};
	bool BSize=false;
	bool BUnit=false;
	bool BPath=false;
	const char *Path;
};

struct STRFORMATO{
	int Realizar=-1;
	int Size;
	bool BSize=false;
	char Unit='b';
	const char *Path;
	bool BPath=false;
	char Type;
	char Fit[2]={'f','f'};
	const char *Delete;
	const char *Name;
	bool BName=false;
	int Add;	
};

struct STRMONTAR{
	const char *Path;
	bool BPath=false;
	const char *Name;
	bool BName=false;	
};

struct STRREPORTE{
	const char *Path;
	bool BPath=false;
	const char *NameRep;
	bool BNameRep=false;
	const char *Id;
	bool BId=false;		
};


%}
//error-verbose si se especifica la opcion los errores sintacticos son especificados por BISON
%error-verbose

%union{
//se especifican los tipo de valores para los no terminales y lo terminales
char TEXT [256];
struct STRCREAR   *SCREAR;
struct STRFORMATO *SFORMA;
struct STRMONTAR  *SMONTA;
struct STRREPORTE *SREPOR;
}

/*No terimanesl*/
%type<TEXT> PROGRAMA;
%type<SFORMA> FORMATO;
%type<SCREAR> CREAR;
%type<TEXT> BORRAR;
%type<SMONTA> MONTAR;
%type<TEXT> DESMONTAR;
%type<TEXT> OPCION;
%type<TEXT> TERMIDIRECC;
%type<TEXT> TERMIIDENTI;
%type<SREPOR> REPORTES;
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




%start PROGRAMA
%%


PROGRAMA: PROGRAMA OPCION {}
	|OPCION{}
;
OPCION:CREAR {if($1->BSize && $1->BUnit && $1->BPath){/*	CREAR	*/}else{std::cout << "MKDISK No Cumple Con Los Parametros Necesarios "<< std::endl;}}
	|BORRAR {/*Se implementa Desde Produccion*/}
	|FORMATO {
		if($1->BName && $1->BPath){
				if($1->Realizar==0){
					if($1->BSize){  /*	Hace Formato	*/		}
					else{std::cout << "Para Crear Es Necesario Dar Un Tamanio "<< std::endl;}
				}else if($1->Realizar==1){
						/*  Eliminar Particion*/
				}else if($1->Realizar==2){
						/* Aumentar Particion*/
				}else{
					std::cout << " No Se Ha Indicado Ninguna Operacion En El FDISK "<< std::endl;
				}
		}
		else{std::cout << "FDISK No Cumple Con Los Parametros Necesarios "<< std::endl;}
	}
	|MONTAR {
		if($1->BName && $1->BPath){
			/* Montar En Memoria */
		}else{
			std::cout << "MOUNT No Cumple Con Los Parametros Necesarios "<< std::endl;
		}

	}
	|DESMONTAR {/*Se implementa Desde Produccion*/}
	|REPORTES {
		if($1->BNameRep && $1->BPath && $1->Id){
			/* Montar En Memoria */
		}else{
			std::cout << "REP No Cumple Con Los Parametros Necesarios "<< std::endl;
		}

	}
;

CREAR:CREAR size igual entero{$$=$1; $$->Size=atoi($4); $$->BSize=true;}
	|CREAR fit igual letra letra{$$=$1; $$->Fit[0]=$4[0]; $$->Fit[1]=$5[0];}
	|CREAR unit igual letra{$$=$1; $$->Unit=$4[0]; $$->BUnit=true;}
	|CREAR path igual TERMIDIRECC {$$=$1; $$->Path=$4; $$->BPath=true;}
	|mkdisk {$$ = new STRCREAR();} 
;
BORRAR: rmdisk path igual TERMIDIRECC{/*BORRA DEL DISCO*/}
;

TERMIDIRECC:direccion{std::copy(std::begin($1), std::end($1), std::begin($$));}
	|cadena{std::copy(std::begin($1), std::end($1), std::begin($$));}
;


FORMATO:FORMATO size igual entero{$$=$1; $$->Size=atoi($4); $$->BSize=true; 	if($$->Realizar==-1)$$->Realizar=0;}
	|FORMATO fit igual letra letra{$$=$1; $$->Fit[0]=$4[0]; $$->Fit[1]=$5[0];}
	|FORMATO unit igual letra{$$=$1; $$->Unit=$4[0];}
	|FORMATO path igual TERMIDIRECC{$$=$1; $$->Path=$4; $$->BPath=true;}
	|FORMATO typep igual letra{$$=$1; $$->Type=$4[0];}
	|FORMATO deletep igual TERMIIDENTI{$$=$1; $$->Delete=$4;   if($$->Realizar==-1)$$->Realizar=1;}
	|FORMATO name igual TERMIIDENTI{$$=$1; $$->Name=$4; $$->BName=true;}
	|FORMATO add igual entero{$$=$1; $$->Add=atoi($4);    if($$->Realizar==-1)$$->Realizar=2;}
	|fdisk{$$= new STRFORMATO();} 	
;

TERMIIDENTI:identificador{std::copy(std::begin($1), std::end($1), std::begin($$));}
	|cadena{std::copy(std::begin($1), std::end($1), std::begin($$));}
;

MONTAR:MONTAR path igual TERMIDIRECC{$$=$1; $$->BPath=true; $$->Name=$4;  }
	|MONTAR name igual TERMIIDENTI{$$=$1;  $$->BName=true; $$->Name=$4;}
	|mount{ $$ = new STRMONTAR();}
;

DESMONTAR: unmount id igual identificador{/*DESMONTA DE MEMORIA*/}
;
REPORTES:REPORTES id igual TERMIIDENTI{$$=$1; $$->BId=true; $$->Id=$4;}
	|REPORTES path igual TERMIDIRECC{$$=$1; $$->BPath=true; $$->Path=$4;}
	|REPORTES name igual TERMIIDENTI{$$=$1;  $$->BNameRep=true; $$->NameRep=$4;}
	|rep { $$ = new STRREPORTE();}
;

%%
