%{
#include "scanner.h"//se importa el header del analisis sintactico
#include <string>
#include <stdlib.h>
#include <stdio.h>
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

struct STRSEXT{
	std::string Id;
	std::string Type; 
};
struct STRSINGRE{ 
	std::string Usr;
	std::string Pwd;
	std::string Id;
};
struct STRSUSR{ 
	std::string Usr;
	std::string Pwd;
	std::string Grp;
};
struct STRSPER{
	std::string Path;
	std::string Ugo;
	std::string R; 
};
struct STRSARCH{
	std::string Path;
	std::string P;
	std::string Size;
	std::string Cont;   
};
struct STRSEDIT{
	std::string Path;
	std::string Cont;   
};
struct STRSREN{
	std::string Path;
	std::string Name;  
};
struct STRSDIR{
	std::string Path;
	std::string P;  
};
struct STRSCOP{
	std::string Path;
	std::string Dest;   
};
struct STRSMOV{
	std::string Path;
	std::string Dest; 
};
struct STRSFIN{
	std::string Path;
	std::string Name; 
};
struct STRSCHOW{
	std::string Path;
	std::string R;
	std::string Usr; 
};
struct STRSCHG{
	std::string Usr;
	std::string Grp; 
};

struct STRDITA{
	std::string Concatenar;
};

%}
//error-verbose si se especifica la opcion los errores sintacticos son especificados por BISON
%error-verbose

%union{

//se especifican los tipo de valores para los no terminales y lo terminales
char TEXT [256];
struct STRDITA *TEXT2 ;
struct STRCREAR   *SCREAR;
struct STRFORMATO *SFORMA;
struct STRMONTAR  *SMONTA;
struct STRREPORTE *SREPOR;
//FASE2
struct STRSEXT* SEXT;
struct STRSINGRE* SINGRE;
struct STRSUSR* SUSR;
struct STRSPER* SPER;
struct STRSARCH* SARCH;
struct STRSEDIT* SEDIT;
struct STRSREN* SREN;
struct STRSDIR* SDIR;
struct STRSCOP* SCOP;
struct STRSMOV* SMOV;
struct STRSFIN* SFIN;
struct STRSCHOW* SCHOW;
struct STRSCHG* SCHG;
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
//FASE2
%type<SEXT> EXT3;
%type<SINGRE> INGRE;
%type<TEXT> SALIR;
%type<TEXT> HACERGRUPO;
%type<TEXT> BORRARGRUPO;
%type<SUSR> HACERUSUARIO;
%type<TEXT> BORRARUSUARIO;
%type<SPER> PERMISO;
%type<SARCH> NUEVOARCHIVO;
%type<TEXT> VERCONTE;
%type<TEXT> REMOVER;
%type<SEDIT> EDITARCHIVO;
%type<SREN> RENOMBRAR;
%type<SDIR> NUEVACARPETA;
%type<SCOP> COPIAR;
%type<SMOV> MOVER;
%type<SFIN> FIN;
%type<SCHOW> CAMBIARPROP;
%type<SCHG> CAMBIARGRUPO;
%type<TEXT> PAUSA;
%type<TEXT> RECUPERAR;
%type<TEXT> MATAR;
%type<TEXT2> TERMIMUC;
%type<TEXT2> MUCHO;
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
//FASE2
%token<TEXT> fs;
%token<TEXT> dest;
%token<TEXT> usr;
%token<TEXT> pwd;
%token<TEXT> logout;
%token<TEXT> login;
%token<TEXT> mkfs;
%token<TEXT> mkgrp;
%token<TEXT> rmgrp;
%token<TEXT> grp;
%token<TEXT> mkusr;
%token<TEXT> rmusr;
%token<TEXT> chmodp;
%token<TEXT> ugo;
%token<TEXT> r;
%token<TEXT> p;
%token<TEXT> cont;
%token<TEXT> mkfile;
%token<TEXT> cat;
%token<TEXT> file;
%token<TEXT> rem;
%token<TEXT> edit;
%token<TEXT> ren;
%token<TEXT> mkdirp;
%token<TEXT> cp;
%token<TEXT> mv;
%token<TEXT> find;
%token<TEXT> chownp;
%token<TEXT> chgrp;
%token<TEXT> pausep;
%token<TEXT> recovery;
%token<TEXT> loss;


%start PROGRAMA
%%
TERMIIDENTI:identificador{std::copy(std::begin($1), std::end($1), std::begin($$));}
	|cadena{std::string Tempo=$1; Tempo=Tempo.substr(1,Tempo.length()-1); strcpy($$,Tempo.c_str());}
;


TERMIMUC:TERMIMUC MUCHO{($1->Concatenar)=($1->Concatenar)+($2->Concatenar); $$=$1;}
	|MUCHO {$$=$1;}
;
MUCHO:id{STRDITA *Temp = new STRDITA(); Temp->Concatenar=$1;$$=Temp;}
	|entero{STRDITA *Temp = new STRDITA(); Temp->Concatenar=$1; $$=Temp;}
;
MATAR: loss igual TERMIIDENTI{}
;

RECUPERAR: recovery igual TERMIIDENTI{}
;

PAUSA:pausep{}
;

CAMBIARGRUPO:CAMBIARGRUPO grp igual TERMIIDENTI{$1->Grp=$4; $$=$1;}
    |CAMBIARGRUPO usr igual TERMIIDENTI{$1->Usr=$4; $$=$1;}
    |chgrp{$$= new STRSCHG();}
;

CAMBIARPROP:CAMBIARPROP r igual TERMIIDENTI{$1->R=$4; $$=$1;}
    |CAMBIARPROP usr igual TERMIIDENTI{$1->Usr=$4; $$=$1;}
    |CAMBIARPROP path igual TERMIDIRECC{$1->Path=$4; $$=$1;}
    |chownp{$$= new STRSCHOW();}
;

FIN:FIN name igual TERMIIDENTI{$1->Name=$4; $$=$1;}
    |FIN path igual TERMIDIRECC{$1->Path=$4; $$=$1;}
    |find{$$=new STRSFIN();}
;

MOVER:MOVER dest igual TERMIDIRECC{$1->Dest=$4; $$=$1;}
    |MOVER path igual TERMIDIRECC{$1->Path=$4; $$=$1;}
    |mv {$$=new STRSMOV();}
;

COPIAR:COPIAR dest igual TERMIDIRECC{$1->Dest=$4; $$=$1;}
    |COPIAR path igual TERMIDIRECC{$1->Path=$4; $$=$1;}
    |cp {$$=new STRSCOP();}
;

NUEVACARPETA:NUEVACARPETA p igual TERMIIDENTI{$1->P=$4; $$=$1;}
    |NUEVACARPETA path igual TERMIDIRECC{$1->Path=$4; $$=$1;}
    |mkdirp{$$= new STRSDIR();}
;

RENOMBRAR:RENOMBRAR name igual TERMIIDENTI{$1->Name=$4; $$=$1;}
    |RENOMBRAR path igual TERMIDIRECC{$1->Path=$4; $$=$1;}
    |ren{$$= new STRSREN();}
;

EDITARCHIVO:EDITARCHIVO path igual TERMIDIRECC{$1->Path=$4; $$=$1;}
    |EDITARCHIVO cont igual TERMIMUC{$1->Cont=$4->Concatenar; $$=$1;}
    |edit{$$= new STRSEDIT();}
;

REMOVER:rem path igual TERMIDIRECC{}
;

VERCONTE: cat file igual TERMIDIRECC {}
;

NUEVOARCHIVO:NUEVOARCHIVO path igual TERMIDIRECC {$1->Path=$4; $$=$1;}
    |NUEVOARCHIVO p igual TERMIIDENTI {$1->P=$4; $$=$1;}
    |NUEVOARCHIVO size igual TERMIIDENTI {$1->Size=$4; $$=$1;}
    |NUEVOARCHIVO cont igual TERMIDIRECC {$1->Cont=$4; $$=$1;}
    |mkfile{$$=new STRSARCH();}
;

PERMISO:PERMISO path igual TERMIDIRECC{$1->Path=$4; $$=$1;}
    |PERMISO ugo igual TERMIIDENTI{$1->Ugo=$4; $$=$1;}
    |PERMISO r igual TERMIIDENTI{$1->R=$4; $$=$1;}
    |chmodp{$$ = new STRSPER();}
;

BORRARUSUARIO: rmusr usr igual TERMIIDENTI{}
;

HACERUSUARIO:HACERUSUARIO pwd igual TERMIIDENTI{$1->Pwd=$4; $$=$1;}
    |HACERUSUARIO grp igual TERMIIDENTI{$1->Grp=$4; $$=$1;}
    |HACERUSUARIO usr igual TERMIIDENTI{$1->Usr=$4; $$=$1;}
    |mkusr{$$ = new STRSUSR();}
;
BORRARGRUPO: rmgrp name igual TERMIIDENTI{}
;
HACERGRUPO: mkgrp name igual TERMIIDENTI{}
;

SALIR: logout{}
;

INGRE:INGRE usr igual TERMIIDENTI{$1->Usr=$4; $$=$1;}
	|INGRE pwd igual TERMIIDENTI{$1->Pwd=$4; $$=$1;}
	|INGRE id igual TERMIIDENTI{$1->Id=$4; $$=$1;}
	|login{$$= new STRSINGRE();}
;
EXT3:EXT3 id igual TERMIIDENTI{$1->Id=$4; $$=$1;}
	|EXT3 typep igual TERMIIDENTI{$1->Type=$4; $$=$1;}
	|EXT3 fs{}
	|mkfs{$$= new STRSEXT();}
;	

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


	|EXT3{}
    |INGRE{}
    |SALIR{}
    |HACERGRUPO{}
    |BORRARGRUPO{}
    |HACERUSUARIO{}
    |BORRARUSUARIO{}
    |PERMISO{}
    |NUEVOARCHIVO{}
    |VERCONTE{}
    |REMOVER{}
    |EDITARCHIVO{}
    |RENOMBRAR{}
    |NUEVACARPETA{}
    |COPIAR{}
    |MOVER{}
    |FIN{}
    |CAMBIARPROP{}
    |CAMBIARGRUPO{}
    |PAUSA{}
    |RECUPERAR{}
    |MATAR{}




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
	|cadena{std::string Tempo=$1; Tempo=Tempo.substr(1,Tempo.length()-1); strcpy($$,Tempo.c_str());}
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
