%{
#include "scanner.h"//se importa el header del analisis sintactico

#include <iostream> //libreria para imprimir en cosola de C
#include <QString> //libreria para manejo de STRINGS de QT
#include "sistema.h"


extern int yylineno; //linea actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern int columna; //columna actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern char *yytext; //lexema actual donde esta el parser (analisis lexico) lo maneja BISON
Sistema *Ope = new Sistema();
std::string toString(const char *TEXT){
	std::string Salida="";
	Salida=TEXT;
	return Salida;
}

int yyerror(const char* mens){
//metodo que se llama al haber un error sintactico
//SE IMPRIME EN CONSOLA EL ERROR
std::cout <<mens<<" "<<yytext<< std::endl;
return 0;
}






struct STRCREAR{
	std::string Path;
	int Size;
	char Unit='m';
	char Fit[2]={'b','f'};
	bool BSize=false;
	bool BUnit=false;
	bool BPath=false;
	
};

struct STRFORMATO{
	int Realizar=-1;
	int Size;
	bool BSize=false;
	char Unit='m';
	std::string Path;
	bool BPath=false;
	char Type='p';
	char Fit[2]={'b','f'};
	std::string Delete;
	std::string Name;
	bool BName=false;
	int Add;	
};

struct STRMONTAR{
	std::string Path;
	bool BPath=false;
	std::string Name;
	bool BName=false;	
};

struct STRREPORTE{
	std::string Path;
	bool BPath=false;
	std::string NameRep;
	bool BNameRep=false;
	std::string Id;
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
%type<TEXT> EJECUTAR;
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
%token<TEXT> exec;

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
OPCION:CREAR {  if($1->BSize && $1->BUnit && $1->BPath){Ope->Crear($1->Size,$1->Unit,$1->Fit,$1->Path);}else{std::cout << "MKDISK No Cumple Con Los Parametros Necesarios "<< std::endl;}}
	|BORRAR {/*Se implementa Desde Produccion*/}
	|FORMATO {
		if($1->BName && $1->BPath){
				if($1->Realizar==0){
					if($1->BSize){  Ope->Formato($1->Size,$1->Fit,$1->Unit,$1->Path,$1->Type,$1->Name);	}
					else{std::cout << "Para Crear Es Necesario Dar Un Tamanio "<< std::endl;}
				}else if($1->Realizar==1){
						Ope->Borrar($1->Delete,$1->Path,$1->Name);
				}else if($1->Realizar==2){
						Ope->Aumentar($1->Add,$1->Path,$1->Name,$1->Unit);
				}else{
					std::cout << " No Se Ha Indicado Ninguna Operacion En El FDISK "<< std::endl;
				}
		}
		else{std::cout << "FDISK No Cumple Con Los Parametros Necesarios "<< std::endl;}
	}
	|MONTAR {
		if($1->BName && $1->BPath){
			Ope->Montar($1->Path,$1->Name);
		}else{
			std::cout << "MOUNT No Cumple Con Los Parametros Necesarios "<< std::endl;
		}

	}
	|DESMONTAR {/*Se implementa Desde Produccion*/}
	|REPORTES {
		if($1->BNameRep && $1->BPath && $1->BId){
			Ope->Reportes($1->Id,$1->NameRep,$1->Path);
		}else{
			std::cout << "REP No Cumple Con Los Parametros Necesarios "<< std::endl;
		}

	}
	|EJECUTAR {/*Desde Produ*/}
;

CREAR:CREAR size igual entero{$$=$1; $$->Size=atoi($4); $$->BSize=true;  }
	|CREAR fit igual identificador{$$=$1;  $$->Fit[0]=$4[0]; $$->Fit[1]=$4[1]; }
	|CREAR unit igual letra{$$=$1; $$->Unit=$4[0]; $$->BUnit=true;}
	|CREAR path igual TERMIDIRECC {$$=$1;  $$->Path=toString($4);  $$->BPath=true; }
	|mkdisk {$$ = new STRCREAR();} 
;
BORRAR: rmdisk path igual TERMIDIRECC{Ope->BorrarDisco(toString($4));}
;

TERMIDIRECC:direccion{std::copy(std::begin($1), std::end($1), std::begin($$));}
	|cadena{std::copy(std::begin($1), std::end($1), std::begin($$));}
;


FORMATO:FORMATO size igual entero{$$=$1; $$->Size=atoi($4); $$->BSize=true; 	if($$->Realizar==-1)$$->Realizar=0;}
	|FORMATO fit igual identificador{$$=$1; $$->Fit[0]=$4[0]; $$->Fit[1]=$4[1];}
	|FORMATO unit igual letra{$$=$1; $$->Unit=$4[0];}
	|FORMATO path igual TERMIDIRECC{$$=$1;   $$->Path=toString($4);   $$->BPath=true; }
	|FORMATO typep igual letra{$$=$1; $$->Type=$4[0];}
	|FORMATO deletep igual TERMIIDENTI{$$=$1; $$->Delete=toString($4);   if($$->Realizar==-1)$$->Realizar=1;}
	|FORMATO name igual TERMIIDENTI{$$=$1; $$->Name=toString($4); $$->BName=true;}
	|FORMATO add igual entero{$$=$1; $$->Add=atoi($4);    if($$->Realizar==-1)$$->Realizar=2;}
	|fdisk{$$= new STRFORMATO();} 	
;

TERMIIDENTI:identificador{std::copy(std::begin($1), std::end($1), std::begin($$));}
	|cadena{std::copy(std::begin($1), std::end($1), std::begin($$));}
;

MONTAR:MONTAR path igual TERMIDIRECC{$$=$1;  $$->Path=toString($4);   $$->BPath=true; }
	|MONTAR name igual TERMIIDENTI{$$=$1;  $$->BName=true; $$->Name=toString($4);}
	|mount{ $$ = new STRMONTAR();}
;

DESMONTAR: unmount id igual identificador{Ope->Desmontar(toString($4));}
;
REPORTES:REPORTES id igual TERMIIDENTI{$$=$1; $$->BId=true; $$->Id=toString($4);}
	|REPORTES path igual TERMIDIRECC{$$=$1;  $$->Path=toString($4);  $$->BPath=true; }
	|REPORTES name igual TERMIIDENTI{$$=$1;  $$->BNameRep=true; $$->NameRep=toString($4);;}
	|rep { $$ = new STRREPORTE();}
;
EJECUTAR: exec path igual TERMIDIRECC{Ope->Ejecutar(toString($4));}
;
%%
