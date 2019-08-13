#include "menu.h"
#include <iostream>
#include <fstream>
/*
 *+++++MKDISK++++++++++++++++++++++++++++
    Terminar MkDisk Con los tamaños necesarios
    Terminar Asignación De Fechas
    Terminar Los Fits
    Terminar El Identificador Random
 *+++++RMDISK++++++++++++++++++++++++++++
    FaltaTodo
*+++++FDISK++++++++++++++++++++++++++++
* Todo
* Worsfti y Best Erroneso
* Hacer Los Fits
*Borrar Para Particiones Logicas/
//FDISK
/*
    char part_status;
    char part_fit;
    int part_start;
    int part_size;
    int part_next=-1;
    char part_name[16];
*/
/*!
    \class QCache
    \brief Busca Si El Tamaño Disponible En El Disco Danto Path Y Tamaño Requerido Del Bloque .
*/
void Menu::FDISKDelete(const char *Delete, const char *Path, const char *Name){
    PAR Part=Fun->SearchPAR(Name,Path);
    if(Part.part_status=='\0'){
       EBR Logic=Fun->SearchEBR(Name,Path);
        if(Logic.part_status=='\0'){
            std::cout<<"No Se Encontro La Particion "<<Name<<std::endl;
            return;
        }else{
            //Borrando La Partición Logica
            if(Fun->IF(Delete,"full")){
                this->DeleteFullLogic(Logic,Path);
            }else if(Fun->IF(Delete,"fast")){
                this->DeleteFastLogic(Logic,Path);
            }else{
                Fun->Out("Error Tipo Borrado Logico");
            }
        }
    }else{
        //Borrando La Partición
        if(Fun->IF(Delete,"full")){
            this->DeleteFull(Part,Path);
        }else if(Fun->IF(Delete,"fast")){
            this->DeleteFast(Part,Path);
        }else{
            Fun->Out("Error Tipo Borrado Particion");
        }
    }

}
void Menu::DeleteFastLogic(EBR InputLogic, const char *Path){
    FILE *f;
    MBR r;
    PAR Extended;
    f=fopen(Path,"r");
    if (!f){
        return;
    }
    fread(&r,sizeof(MBR),1,f);
    fclose(f);
    int ExtendIndex=Fun->HasExtended(Path);
    if(ExtendIndex==0){
        Fun->Out("Este Disco No Tiene  Ninguna Particion Extendida,No Se Puede Borrar Una Logica");
        return ;
    }else if (ExtendIndex==-1) {
        Fun->Out("Error En El Disco, En La Partición Extendida");
        return ;
    }
    Extended=r.mbr_partition[ExtendIndex-1];


    EBR Logic;
    Logic.part_next=0;
    int LogicIndex=Extended.part_start;

    f=fopen(Path,"r+");
    if (!f){
        return;
    }
    //Ver Si A Eliminar Es La Unica O Primera De Disco
    if(Extended.part_start==InputLogic.part_start){
        //Es la Unica
        if(InputLogic.part_next==-1){
            InputLogic.part_fit[0]='f';
            InputLogic.part_fit[1]='f';
            this->FillName(InputLogic.part_name,"");
            InputLogic.part_next=-1;
            InputLogic.part_size=0;
            InputLogic.part_status='f';
            fseek(f,Extended.part_start,SEEK_SET);
            fwrite(&InputLogic,sizeof(EBR),1,f);
            fclose(f);
            return;
        }//Es la primera
        else{
            fseek(f,InputLogic.part_next,SEEK_SET);
            fread(&Logic,sizeof(EBR),1,f);
            fseek(f,Extended.part_start,SEEK_SET);
            fwrite(&Logic,sizeof(EBR),1,f);
            fclose(f);
            return;
        }
    }


    while(LogicIndex!=-1){
        fseek(f,LogicIndex,SEEK_SET);
        fread(&Logic,sizeof(EBR),1,f);
        //El Siguiente Del Puntero Actual Es El Que Se Busca borrar
        if(Logic.part_next==InputLogic.part_start){
            Logic.part_next=InputLogic.part_next;
            fseek(f,Logic.part_start,SEEK_SET);
            fwrite(&Logic,sizeof(EBR),1,f);
            fclose(f);
            return;
        }
        LogicIndex=Logic.part_next;
    }
    fclose(f);
}
void Menu::DeleteFullLogic(EBR InputLogic, const char *Path){
    this->DeleteFastLogic(InputLogic,Path);
    FILE *f;
    MBR r;
    PAR Extended;
    f=fopen(Path,"r");
    if (!f){
        return;
    }
    fread(&r,sizeof(MBR),1,f);
    fclose(f);
    int ExtendIndex=Fun->HasExtended(Path);
    if(ExtendIndex==0){
        Fun->Out("Este Disco No Tiene  Ninguna Particion Extendida,No Se Puede Borrar Una Logica");
        return ;
    }else if (ExtendIndex==-1) {
        Fun->Out("Error En El Disco, En La Partición Extendida");
        return ;
    }
    Extended=r.mbr_partition[ExtendIndex-1];
    //Ver Si A Eliminar Es La Unica O Primera De Disco
    if(Extended.part_start==InputLogic.part_start){
        FillDisk(InputLogic.part_start+int(sizeof (EBR)),InputLogic.part_size,'\0',Path);
    }else{
        FillDisk(InputLogic.part_start,InputLogic.part_size,'\0',Path);
    }
}

void Menu::DeleteFast(PAR Parti, const char *Path){
    FILE *f;
    MBR Main;
    PAR Extended;
    f=fopen(Path,"r");
    if (!f){
        return;
    }
    fread(&Main,sizeof(MBR),1,f);
    fclose(f);


}
void Menu::DeleteFull(PAR Parti, const char *Path){

}
void Menu::FDisk(int Size, const char *Fit, char Unit, const char *Path, char Type,const char *Name){
    Type=char(tolower(Type));
    Size=Fun->Mult(Size,Unit);
    switch (Type) {
        case 'p':{
            this->NewPrimary(Size,Fit,Unit,Path,Name);
            break;
        }
        case 'e':{
            this->NewExtended(Size,Fit,Unit,Path,Name);
            break;
        }
        case 'l':{
            this->NewLogical(Size,Fit,Unit,Path,Name);
            break;
        }
    }

}

void Menu::NewPrimary(int Size, const char *Fit, char Unit, const char *Path,const char *Name){
    int Index=HasSlot(Path);
    Size=Fun->Mult(Size,Unit);
    FILE *f;
    MBR r;
    f=fopen(Path,"r");
    if (!f){
        return;
    }
    fread(&r,sizeof(MBR),1,f);
    fclose(f);
    //std::cout<<r.mbr_partition[Index].part_status<<std::endl;
    if(Index==-1){
        Fun->Out("Este Disco Ya Llego Al Limite De Particiones Primarias");
    }else{
        //std::cout<<Index<<std::endl;


        char SubFit [2];
        SubFit[0]=Fit[0];
        SubFit[1]=Fit[1];
        int Fit = Fun->DiskFit(SubFit,Size,Path);
        std::cout<<Fit<<"--P--"<<Size<<std::endl;
        if(Fit==-1){
            Fun->Out("No Hay Espacio Suficiente Para La Particion");
        }else{
            r.mbr_partition[Index-1].part_status='t';
            r.mbr_partition[Index-1].part_type='p';
            r.mbr_partition[Index-1].part_fit[0]=SubFit[0];
            r.mbr_partition[Index-1].part_fit[1]=SubFit[1];
            r.mbr_partition[Index-1].part_start=Fit;
            r.mbr_partition[Index-1].part_size=Size;
            FillName(r.mbr_partition[Index-1].part_name,Name);
            f=fopen(Path,"r+");
            if (!f)
                return ;
            fseek(f,0,SEEK_SET);
            fwrite(&r,sizeof(MBR),1,f);
            fclose(f);
            this->FillDisk(Fit,Fit+Size,'p',Path);
        }
    }
}
void Menu::NewExtended(int Size, const char *Fit, char Unit, const char *Path,const char *Name){
    int Index=HasSlot(Path);
    Size=Fun->Mult(Size,Unit);
    FILE *f;
    MBR r;
    f=fopen(Path,"r");
    if (!f){
        return;
    }
    fread(&r,sizeof(MBR),1,f);
    fclose(f);
    if(Fun->HasExtended(Path)!=0){
        Fun->Out("Este Disco Ya Tiene Particion EXtendida");
        return ;
    }
    if(Index==-1){
        Fun->Out("Este Disco Ya Llego Al Limite De Particiones ");
    }else{
        char SubFit [2];
        SubFit[0]=Fit[0];
        SubFit[1]=Fit[1];
        int Fit = Fun->DiskFit(SubFit,Size,Path);
        std::cout<<Fit<<"--E--"<<Size<<std::endl;
        if(Fit==-1){
            Fun->Out("No Hay Espacio Suficiente Para La Particion");
        }else{
            r.mbr_partition[Index-1].part_status='t';
            r.mbr_partition[Index-1].part_type='e';
            r.mbr_partition[Index-1].part_fit[0]=SubFit[0];
            r.mbr_partition[Index-1].part_fit[1]=SubFit[1];
            r.mbr_partition[Index-1].part_start=Fit;
            r.mbr_partition[Index-1].part_size=Size;
            FillName(r.mbr_partition[Index-1].part_name,Name);
            f=fopen(Path,"r+");
            if (!f)
                return ;
            fseek(f,0,SEEK_SET);
            fwrite(&r,sizeof(MBR),1,f);
            fclose(f);



            f=fopen(Path,"r+");
            EBR Logic;
            Logic.part_status='f';
            Logic.part_fit[0]=SubFit[0];
            Logic.part_fit[1]=SubFit[1];
            Logic.part_start=Fit;
            Logic.part_size=0;
            Logic.part_next=-1;
            FillName(Logic.part_name,Name);
            fseek(f,Fit,SEEK_SET);
            fwrite(&Logic,sizeof (EBR),1,f);
            fclose(f);

            //Arreglar
            this->FillDisk(Fit+int(sizeof(EBR)),Fit+Size,'e',Path);
        }
    }
}
void Menu::FillName(char *Arra, const char *Input){
    Arra[0]='C';
    for(int i=0;i<16;i++){
        Arra[i]=' ';
    }
    strcpy(Arra, Input);
}
void Menu::NewLogical(int Size, const char *Fit, char Unit, const char *Path,const char *Name){
    Size=Fun->Mult(Size,Unit);
    if(Size<=int(sizeof (EBR))){
        Fun->Out("El Tamaño dado a la particion logica es muy pequeño");
        return;
    }

    FILE *f;
    MBR r;
    PAR Extended;
    f=fopen(Path,"r");
    if (!f){
        return;
    }
    fread(&r,sizeof(MBR),1,f);
    fclose(f);
    int ExtendIndex=Fun->HasExtended(Path);
    if(ExtendIndex==0){
        Fun->Out("Este Disco No Tiene  Ninguna Particion Extendida,No Se Puede Crear Una Logica");
        return ;
    }else if (ExtendIndex==-1) {
        Fun->Out("Error En El Disco, En La Partición Extendida");
        return ;
    }
    Extended=r.mbr_partition[ExtendIndex-1];


    EBR Logic;
    EBR NewLogic;
    Logic.part_next=0;
    int LogicIndex=Extended.part_start;

    f=fopen(Path,"r+");
    if (!f){
        return;
    }

    while(LogicIndex!=-1){
        fseek(f,LogicIndex,SEEK_SET);
        fread(&Logic,sizeof(EBR),1,f);

        LogicIndex=Logic.part_next;

    }
    fclose(f);
    //HACER NEW LOGIC CONTENIDO
    //Logic.part_next=Logic.part_start;
    //Hacer Recorido De La Lista
    //Calcular Si Hay Espacio para La Logica En La Extendida
    char SubFit[2];
    SubFit[0]=Fit[0];
    SubFit[1]=Fit[1];


    int NewLog=-1;

    if(Logic.part_status=='f'){
            NewLog=Fun->LogicFit(SubFit,Size-int(sizeof(EBR)),Path,Extended.part_start,Extended.part_start+Extended.part_size);
            Logic.part_status='t';
            Logic.part_fit[0]=SubFit[0];
            Logic.part_fit[1]=SubFit[1];
            Logic.part_start=Extended.part_start;
            Logic.part_size=Size;
            FillName(Logic.part_name,Name);
            Logic.part_next=-1;
            f=fopen(Path,"r+");
            fseek(f,Logic.part_start,SEEK_SET);
            fwrite(&Logic,sizeof (EBR),1,f);
            fclose(f);

            this->FillDisk(NewLog+int(sizeof(EBR)),NewLog+Size,'c',Path);
            std::cout<<(NewLog)<<"--"<<"L1"<<"--"<< NewLog+(Size)<<std::endl;
            return ;
        }

    NewLog=Fun->LogicFit(SubFit,Size,Path,Extended.part_start,Extended.part_start+Extended.part_size);

    if(NewLog==-1){
        Fun->Out("No Hay Espacio Para La Unidad Logica En Esta Particion Extendida");
        std::cout<<Size<<"---"<<Extended.part_start<<"---"<<Extended.part_start+Extended.part_size<<std::endl;
    }else{


        f=fopen(Path,"r+");
        Logic.part_next=NewLog;
        fseek(f,Logic.part_start,SEEK_SET);
        fwrite(&Logic,sizeof (EBR),1,f);
        NewLogic.part_status='t';
        NewLogic.part_fit[0]=SubFit[0];
        NewLogic.part_fit[1]=SubFit[1];
        NewLogic.part_start=NewLog;
        NewLogic.part_size=Size;
        FillName(NewLogic.part_name,Name);
        NewLogic.part_next=-1;
        fseek(f,NewLog,SEEK_SET);
        fwrite(&NewLogic,sizeof (EBR),1,f);

        fclose(f);
        std::cout<<NewLog<<"--"<<"L2"<<"--"<<NewLog+(Size)<<std::endl;

        this->FillDisk(NewLog+int(sizeof(EBR)),NewLog+(Size),'c',Path);
    }
}
int Menu::HasSlot(const char *Path){
    FILE *f;
    MBR r;
    f=fopen(Path,"r");
    if (!f){

        return -1;
    }
    fread(&r,sizeof(MBR),1,f);
    fclose(f);
    if(r.mbr_partition[0].part_status=='f')
    {
        return 1;

    }
    else if(r.mbr_partition[1].part_status=='f')
        return 2;
    else if(r.mbr_partition[2].part_status=='f')
        return 3;
    else if(r.mbr_partition[3].part_status=='f')
        return 4;
    else {
        return -1;
    }
}
//RMDISK Y Utilidades

/*!
    \class QCache
    \brief Aquí Se Inicia El Menú.
*/
void Menu::NewMenu(){
    Mkdisk(1024,"ff",'q',"Disco.disk");
    FDisk(100,"ff",'q',"Disco.disk",'p',"m");
    FDisk(100,"ff",'q',"Disco.disk",'p',"a");
    FDisk(100,"ff",'q',"Disco.disk",'p',"a");
    FDisk(300,"ff",'q',"Disco.disk",'e',"a");
    FDisk(50,"ff",'q',"Disco.disk",'l',"b");
    FDisk(50,"ff",'q',"Disco.disk",'l',"c");
    FDisk(50,"ff",'q',"Disco.disk",'l',"d");
    FDisk(50,"ff",'q',"Disco.disk",'l',"e");
    FDisk(50,"ff",'q',"Disco.disk",'l',"f");
    FDisk(50,"ff",'q',"Disco.disk",'l',"g");
    //FDisk(100,"ff",'q',"Disco.disk",'p');

}
/*!
    \class QCache
    \brief Crea Disco Nuevo.
*/
void Menu::Mkdisk(int Size, const char *Fit, char Unit, const char *Path){
    FILE *f;
    MBR r;
    f=fopen(Path,"w");
    Size=Fun->Mult(Size,Unit);
    if (!f){
        return ;
    }else{


        const char *Date="07/08/2019";

        r.mbr_tamano=Size;
        //Date(&r.mbr_fecha_creacion);
        //Random(&r.mbr_disk_signature);
        FillPAR(&r.mbr_partition[0]);
        FillPAR(&r.mbr_partition[1]);
        FillPAR(&r.mbr_partition[2]);
        FillPAR(&r.mbr_partition[3]);
        r.disk_fit[0]=char(tolower(Fit[0]));
        r.disk_fit[1]=char(tolower(Fit[1]));
        fwrite(&r,sizeof(MBR),1,f);
        fclose(f);
        FillDisk(sizeof(MBR),Size,'\0',Path);
    }
  // std::cout<<BlockSize((sizeof(MBR)),Path)<<std::endl;
}
void Menu::FillPAR(PAR *NPAR){
    NPAR->part_status='f';
    NPAR->part_type='p';
    NPAR->part_fit[0]='f';
    NPAR->part_fit[1]='f';
    NPAR->part_start=0;
    NPAR->part_size=0;
}
/*!
    \class QCache
    \brief Llena El Disco Con Cierto Caracter(r+ Es para Actualizar W es para borrar y escribir).
*/
void Menu::FillDisk(int Begin, int Size, char Character,const char *Path){
    FILE *f;
    f=fopen(Path,"r+");
    fseek(f,Begin,SEEK_SET);
    for(int i=Begin;i<Size;i++){
        char Buffer=Character;
        //std::cout<<Begin<<std::endl;
        fwrite(&Buffer,sizeof (Buffer),1,f);
    }
    fclose(f);
/*
    f=fopen(Path,"r");
    if (!f){
        return;
    }
    char r;
    for(int i=Begin;i<Size;i++){
        fread(&r,sizeof(char),1,f);
        std::cout<<r<<"--"<<i<<std::endl;
    }

    fclose(f);*/
}

Menu::Menu()
{
    this->NewMenu();
}
