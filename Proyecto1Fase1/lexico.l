%option noyywrap
%option caseless
%{
#include "parser.h"
#include <iostream>
#include <QString>
int columna=0;
int anterior=0;
%}

comentario  #[^\r\n]*[^\r\n]
identificador (letra|"_")({letra}|{numero}|"_")*
letra [a-zñA-ZÑ]+
numero [0-9]+

cadena \"[^"\""]*\"
direccion \\(identificador\\)*identificador\.disk

igual =
mkdisk mkdisk
rmdisk rmdisk
mount mount
unmount unmount
rep rep

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
{comentario}  {    }

{igual}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return igual;}
{mkdisk}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return mkdisk;}
{rmdisk}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return rmdisk;}
{mount}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return mount;}
{unmount}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return unmount;}
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
{letra}          {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return letra;}
[[:blank:]]     { /*Se ignoran*/ }
.               {std::cout <<yytext<<"Error Lexico "<< std::endl;}
%%
