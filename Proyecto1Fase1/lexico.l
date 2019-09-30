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

fs -fs
usr -usr
pwd -pwd
logout logout
login login
mkfs mkfs
mkgrp mkgrp
rmgrp rmgrp
grp -grp
mkusr mkusr
rmusr rmusr
chmodp chmod
ugo -ugo
r -r
p -p
cont -cont
dest -dest
mkfile mkfile
cat cat
file -file
rem rem
edit edit
ren ren
mkdirp mkdir
cp cp
mv mv
find find
chownp chown
chgrp chgrp
pausep pause
recovery recovery
loss loss

%%
{salto} {columna=0;salto=salto+1;}
{comentario}  {    }

{fs}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return fs;}
{usr}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return usr;}
{pwd}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pwd;}
{logout}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return logout;}
{login}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return login;}
{mkfs}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return mkfs;}
{mkgrp}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return mkgrp;}
{grp}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return grp;}
{mkusr}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return mkusr;}
{chmodp}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return chmodp;}
{ugo}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return ugo;}
{r}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return r;}
{p}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return p;}
{cont}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return cont;}
{mkfile}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return mkfile;}
{cat}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return cat;}
{file}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return file;}
{rem}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return rem;}
{edit}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return edit;}
{ren}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return ren;}
{mkdirp}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return mkdirp;}
{cp}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return cp;}
{mv}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return mv;}
{find}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return find;}
{chownp}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return chownp;}
{chgrp}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return chgrp;}
{pausep}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pausep;}
{recovery}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return recovery;}
{loss}          {  columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return loss;}






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
