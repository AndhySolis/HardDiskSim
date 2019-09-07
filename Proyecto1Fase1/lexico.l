%option noyywrap
%option caseless
%{
#include "parser.h"
#include <iostream>
#include <QString>
int columna=0;
int anterior=0;
int salto=1;
%}
direccion \/({identificador}\/)*{identificador}\.(disk|png|pdf|sh|txt)
comentario  #[^\r\n]*[^\r\n]
identificador ({letra}|"_")({letra}|{numero}|"_")*
letra [a-zñA-ZÑ]
numero (-)?[0-9]+
salto [\n]
cadena \"[^"\""]*\"

igual =
mkdisk mkdisk
rmdisk rmdisk
fdisk fdisk
mount mount
unmount unmount
rep rep
exec exec

size -size
fit -fit
unit -unit
path -path
typep -type
deletep -delete
name -name
add -add
id -id


%%
{salto} {columna=0;salto=salto+1;}
{comentario}  {    }
{direccion}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return direccion;}
{exec}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return exec;}
{igual}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return igual;}
{mkdisk}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return mkdisk;}
{fdisk}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return fdisk;}
{rmdisk}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return rmdisk;}
{mount}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return mount;}
{unmount}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return unmount;}
{rep}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return rep;}
{letra}          {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return letra;}
{size}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return size;}
{fit}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return fit;}
{unit}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return unit;}
{path}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return path;}
{typep}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return typep;}
{deletep}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return deletep;}
{name}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return name;}
{add}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return add;}
{id}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return id;}
{numero}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return entero;}

{cadena}          {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return cadena;}
{identificador}          {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return identificador;}

[[:blank:]]     { /*Se ignoran*/ }
.               {std::cout <<yytext<<"Error Lexico "<<salto <<"  "<<columna<<std::endl;}
%%
