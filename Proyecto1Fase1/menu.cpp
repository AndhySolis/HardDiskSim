#include "menu.h"
#include <iostream>

#include <fstream>
/*
 * Falta El Raid
 *+++++MKDISK++++++++++++++++++++++++++++
    Terminar MkDisk Con los tamaños necesarios
    Terminar Asignación De Fechas
    Terminar Los Fits
    Terminar El Identificador Random
 *+++++RMDISK++++++++++++++++++++++++++++
    Falta Implementar Eliminación Del Raid
*+++++FDISK++++++++++++++++++++++++++++
* Todo
* Worsfti y Best Erroneso
* Hacer Los Fits
*Borrar Para Particiones Logicas/
* Graficar no lo hace bien si se borra la primera particion logica
* Borrar el primero de las particiones logicas
* FDIsk Add problema con buscar desde hasta donde, especial el hasta
* Falta poner número a los reportes
* Guardar en ubicación correcta reportes
* LLamar A Los Reportes
//FDISK
*/

//UNMOUNT
void Menu::UNMOUNT(const char *Name){
    if(this->PrimerDisco==nullptr){
        std::cout<<"No Hay Ningún Disco En El Sistema"<<std::endl;
    }else{
        this->PrimerDisco->BorrarParticion(Name);

    }

}
//MOUNT
void Menu::MOUNT(const char *Path,const char *Name){
    if(this->PrimerDisco==nullptr){
        this->PrimerDisco=new Disco(Path,nullptr);
    }else{
        Disco *Temporal=this->PrimerDisco;
        while(Temporal!=nullptr){
            if(Fun->IF(Temporal->Path,Path)){
                Temporal->AgregarParticion(Name);
                return;
            }
            Temporal=Temporal->Siguiente;
        }
        this->PrimerDisco=new Disco(Path,this->PrimerDisco);
        this->PrimerDisco->AgregarParticion(Name);
    }

}

//REMOVE DISK
void Menu::RMDISK(const char *Path){
       if(remove(Path)== 0) {
          std::cout<<"Disco Borrado"<<std::endl;
       } else {
         std::cout<<"No Se Pudo Borrar El Disco"<<std::endl;
       }
    std::cout<<"No Esta Implementado Para El Raid"<<std::endl;
}
//FDISKADD
/*!
    \class QCache
    \brief Busca Si El Tamaño Disponible En El Disco Danto Path Y Tamaño Requerido Del Bloque .
*/
void Menu::FDISKAdd(int Size, const char *Path, const char *Name){
    if(Size>0){
        AgregarMas(Size,Path,Name);
    }else{
        AgregarMenos(Size,Path,Name);
    }
}
void Menu::AgregarMas(int Size, const char *Path, const char *Name){
    FILE *f;
    MBR Main;
    f=fopen(Path,"r+");
    if (!f){
        return;
    }
    fread(&Main,sizeof(MBR),1,f);
    fclose(f);
    //fseek(f,0,SEEK_SET);
    //fwrite(&r,sizeof(MBR),1,f);

    int ParIndex=Fun->SearchPAR(Name,Path);
    if(ParIndex==-1){
       EBR Logic=Fun->SearchEBR(Name,Path);
        if(Logic.part_status=='\0'){
            std::cout<<"No Se Encontro La Particion "<<Name<<std::endl;
            return;
        }else{
          int ExtendIndex =Fun->HasExtended(Path);
          PAR ExtendPart = Main.mbr_partition[ExtendIndex-1];
          bool Add=Fun->LogicLimit(ExtendPart.part_start+ExtendPart.part_size,ExtendPart.part_start,Size,Path);
          if(Add==false){
              std::cout<<"No Se Pudo Agregar Espacio A La Particion Logica "<<Name<<" No Hay suficiente espacio en Particion extendida"<<std::endl;
          }else{
              f=fopen(Path,"r+");
              if (!f){
                  return;
              }
              fseek(f,Logic.part_start,SEEK_SET);
              fread(&Logic,sizeof(EBR),1,f);
              Logic.part_size=Logic.part_size+Size;
              fseek(f,Logic.part_start,SEEK_SET);
              fwrite(&Logic,sizeof(EBR),1,f);
              fclose(f);

              std::cout<<"Se Agrego Un Espacio De "<<Size<<" A La Paricion Logica '"<<Name<<"'"<<std::endl;
          }
        }
    }else{
        bool Add=Fun->DiskLimit(Main,ParIndex,Size,Path);
        if(Add==false){
            std::cout<<"No Se Pudo Agregar Espacio A La Particion Primaria O Extendida "<<Name<<" No Hay suficiente espacio en Disco"<<std::endl;
        }else{
            f=fopen(Path,"r+");
            if (!f){
                return;
            }
            PAR Part= Main.mbr_partition[ParIndex];;
            Part.part_size=Part.part_size+Size;
            Main.mbr_partition[ParIndex]=Part;
            fseek(f,0,SEEK_SET);
            fwrite(&Main,sizeof(MBR),1,f);
            fclose(f);

            std::cout<<"Se Agrego Un Espacio De "<<Size<<" A La Paricion Primaria|Extendida '"<<Name<<"'"<<Name<<std::endl;

        }
    }


}
void Menu::AgregarMenos(int Size, const char *Path, const char *Name){
    FILE *f;
    MBR Main;
    f=fopen(Path,"r+");
    if (!f){
        return;
    }
    fread(&Main,sizeof(MBR),1,f);
    fclose(f);
    int ParIndex=Fun->SearchPAR(Name,Path);
    if(ParIndex==-1){
       EBR Logic=Fun->SearchEBR(Name,Path);
        if(Logic.part_status=='\0'){
            std::cout<<"No Se Encontro La Particion "<<Name<<std::endl;
            return;
        }else{
           ReducirLogica(Size,Path,Logic,Name);
        }
    }else{
          ReducirPrimaria(Size,Path,ParIndex);
    }


}
void Menu::ReducirLogica(int Size, const char *Path, EBR Ext,const char *Name){
    FILE *f;
    f=fopen(Path,"r+");
    if (!f){
        return;
    }
    if(Ext.part_size-Size>int(sizeof (EBR))){
        Ext.part_size=Ext.part_size-Size;
        fseek(f,Ext.part_start,SEEK_SET);
        fwrite(&Ext,sizeof(EBR),1,f);
        std::cout<<"Se Redujo La Partición "<<Name<<" Un Tamanio De "<<Size<<std::endl;
    }else{
        std::cout<<"No Se Reducir El Tamanio A La Particion Logica "<<Name<<" Quedaria Muy Pequenha"<<std::endl;
    }
    fclose(f);

}
void Menu::ReducirPrimaria(int Size, const char *Path, int Indice){
    FILE *f;
    MBR Main;
    f=fopen(Path,"r+");
    if (!f){
        return;
    }
    fread(&Main,sizeof(MBR),1,f);
    PAR Actual=Main.mbr_partition[Indice];
    if(Actual.part_type=='e'){
        int UltimaLogica =Fun->LogicaFinal(Actual,Path);
        if(UltimaLogica>Actual.part_size-Size){
            std::cout<<"No Se Puede Borrar De La Particion Extendida "<<Actual.part_name<<" Se Quedaria sin espacio para particiones extendidas"<<std::endl;
            fclose(f);
            return;
        }
    }else{
        if(int(sizeof (PAR))>Actual.part_size-Size){
            std::cout<<"No Se Puede Borrar De La Particion Primaria "<<Actual.part_name<<" Se Quedaria el espacio necesario"<<std::endl;
            fclose(f);
            return;
        }
    }
    Actual.part_size=Actual.part_size-Size;
    Main.mbr_partition[Indice]=Actual;
    fseek(f,0,SEEK_SET);
    fwrite(&Main,sizeof(MBR),1,f);
    fclose(f);
    std::cout<<"Se Redujo La Partición "<<Actual.part_name<<" Un Tamanio De "<<Size<<std::endl;
}
//FDISKDELETE
void Menu::FDISKDelete(const char *Delete, const char *Path, const char *Name){
    FILE *f;
    MBR Main;
    f=fopen(Path,"r+");
    if (!f){
        return;
    }
    fread(&Main,sizeof(MBR),1,f);
    fclose(f);
    int ParIndex=Fun->SearchPAR(Name,Path);

    if(ParIndex==-1){
       EBR Logic=Fun->SearchEBR(Name,Path);
        if(Logic.part_status=='\0'){
            std::cout<<"No Se Encontro La Particion "<<Name<<std::endl;
            return;
        }else{
            //Borrando La Partición Logica
            if(Fun->IF(Delete,"full")){
                std::cout<<"Borrado 'FULL' De Particion Logica "<<Logic.part_name<<" Que Empieza En "<<Logic.part_start<<" Con Tamanio "<<Logic.part_size<<std::endl;
                this->DeleteFullLogic(Logic,Path);
            }else if(Fun->IF(Delete,"fast")){
                std::cout<<"Borrado 'FAST' De Particion Logica "<<Logic.part_name<<" Que Empieza En "<<Logic.part_start<<" Con Tamanio "<<Logic.part_size<<std::endl;
                this->DeleteFastLogic(Logic,Path);
            }else{
                Fun->Out("Error Tipo Borrado Logico");
            }
        }
    }else{
        //Borrando La Partición
        PAR Part=Main.mbr_partition[ParIndex];
        if(Fun->IF(Delete,"full")){
            std::cout<<"Borrado 'FULL' De Particion "<<Part.part_name<<" Que Empieza En "<<Part.part_start<<" Con Tamanio "<<Part.part_size<<std::endl;
            this->DeleteFull(Part,Path);
        }else if(Fun->IF(Delete,"fast")){
            std::cout<<"Borrado 'FAST' De Particion "<<Part.part_name<<" Que Empieza En "<<Part.part_start<<" Con Tamanio "<<Part.part_size<<std::endl;
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
            fseek(f,Extended.part_start,SEEK_SET);
            fread(&Logic,sizeof(EBR),1,f);
            fseek(f,Extended.part_start,SEEK_SET);
            Logic.part_status='f';
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
            EBR Aux;//PRIMER EBR
            fseek(f,Extended.part_start,SEEK_SET);
            fread(&Aux,sizeof(EBR),1,f);
            Logic.part_next=InputLogic.part_next;
            fseek(f,Logic.part_start,SEEK_SET);
            fwrite(&Logic,sizeof(EBR),1,f);
            fclose(f);
            return;
        }
        LogicIndex=Logic.part_next;
    }
    std::cout<<"Error En DeleteFastLogico"<<std::endl;
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
    f=fopen(Path,"r+");
    if (!f){
        return;
    }
    fread(&Main,sizeof(MBR),1,f);

    for (int i=0;i<4;i++) {
        Extended=Main.mbr_partition[i];
        if(Fun->IF(Parti.part_name,Extended.part_name)){
            this->FillPAR(&Extended);
            std::cout<<Extended.part_status<<" {*}"<<std::endl;

            for (int j=i;j<3;j++) {
                Main.mbr_partition[j]=Main.mbr_partition[j+1];

            }
            Main.mbr_partition[3]=Extended;
            fseek(f,0,SEEK_SET);
            fwrite(&Main,sizeof(MBR),1,f);
            fclose(f);
            return;
        }

    }
    fclose(f);
    std::cout<<"Error En DeleteFast"<<std::endl;

}
void Menu::DeleteFull(PAR Parti, const char *Path){
    this->DeleteFast(Parti,Path);
    FillDisk(Parti.part_start,Parti.part_size,'\0',Path);
}
//
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
    int NewLog=-1;
    char SubFit[2];
    SubFit[0]=Fit[0];
    SubFit[1]=Fit[1];

    NewLog=Fun->LogicFit(SubFit,Size,Path,Extended.part_start,Extended.part_start+Extended.part_size);

    while(LogicIndex!=-1){
        fseek(f,LogicIndex,SEEK_SET);
        fread(&Logic,sizeof(EBR),1,f);
        LogicIndex=Logic.part_next;
        if(Logic.part_next>NewLog && NewLog!=-1 && Logic.part_next !=-1){
            break;
        }
    }
    fclose(f);
    //HACER NEW LOGIC CONTENIDO
    //Logic.part_next=Logic.part_start;
    //Hacer Recorido De La Lista
    //Calcular Si Hay Espacio para La Logica En La Extendida




    //Es el primero

    if(Logic.part_status=='f'){
        NewLog=Fun->LogicFit(SubFit,Size-int(sizeof(EBR)),Path,Extended.part_start,Extended.part_start+Extended.part_size);
        Logic.part_status='t';
        Logic.part_fit[0]=SubFit[0];
        Logic.part_fit[1]=SubFit[1];
        Logic.part_start=Extended.part_start;
        Logic.part_size=Size;
        FillName(Logic.part_name,Name);

        if(Logic.part_next==-1){
            std::cout<<(NewLog)<<"--"<<"L1"<<"--"<< NewLog+(Size)<<std::endl;            
        }   else{
            //No se Cambia Logic.par t_next=-1;
            std::cout<<(NewLog)<<"--"<<"L1S"<<"--"<< NewLog+(Size)<<std::endl;
        }


        f=fopen(Path,"r+");
        fseek(f,Logic.part_start,SEEK_SET);
        fwrite(&Logic,sizeof (EBR),1,f);
        fclose(f);
        this->FillDisk(NewLog+int(sizeof(EBR)),NewLog+Size,'c',Path);
        return ;
    }



    if(NewLog==-1){
        Fun->Out("No Hay Espacio Para La Unidad Logica En Esta Particion Extendida");
        std::cout<<Size<<"---"<<Extended.part_start<<"---"<<Extended.part_start+Extended.part_size<<std::endl;
    }else{

        f=fopen(Path,"r+");

        NewLogic.part_next=Logic.part_next;
        Logic.part_next=NewLog;
        fseek(f,Logic.part_start,SEEK_SET);
        fwrite(&Logic,sizeof (EBR),1,f);
        NewLogic.part_status='t';
        NewLogic.part_fit[0]=SubFit[0];
        NewLogic.part_fit[1]=SubFit[1];
        NewLogic.part_start=NewLog;
        NewLogic.part_size=Size;
        FillName(NewLogic.part_name,Name);




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
    Fun->Out("-----------------NewMenu--------------");
    Mkdisk(1024,"ff",'q',"Disco.disk");
    FDisk(50,"ff",'q',"Disco.disk",'p',"a");
    this->FDISKAdd(100,"Disco.disk","a");
    FDisk(100,"ff",'q',"Disco.disk",'p',"b");


    FDisk(100,"ff",'q',"Disco.disk",'p',"c");
    //FDISKDelete("fast","Disco.disk","a");//ELIMINANDO PARTICIONES PRIMARIAS|EXTENDIDA
    //FDISKDelete("fast","Disco.disk","b");//ELIMINANDO PARTICIONES PRIMARIAS|EXTENDIDA
    FDisk(300,"ff",'q',"Disco.disk",'e',"d");
    //FDISKDelete("fast","Disco.disk","d");//ELIMINANDO PARTICIONES PRIMARIAS|EXTENDIDA


    FDisk(50,"ff",'q',"Disco.disk",'l',"e");
    FDisk(50,"ff",'q',"Disco.disk",'l',"f");
    FDisk(50,"ff",'q',"Disco.disk",'l',"g");
    FDisk(50,"ff",'q',"Disco.disk",'l',"h");
    FDisk(50,"ff",'q',"Disco.disk",'l',"i");
    FDisk(50,"ff",'q',"Disco.disk",'l',"j");

    /*FDISKDelete("fast","Disco.disk","e");//ELIMINANDO PARTICIONES LOGICAS}
    FDISKDelete("fast","Disco.disk","f");//ELIMINANDO PARTICIONES LOGICAS}
    FDISKDelete("fast","Disco.disk","h");//ELIMINANDO PARTICIONES LOGICAS}*/
    Fun->Out("-----------------Graficar--------------");
    //RMDISK("Disco.disk");
    Repo->Graphviz("Disco.disk");





    RMDISK("Disco.disk");
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
        fwrite(&Character,sizeof (Character),1,f);
    }
    fclose(f);
}

Menu::Menu()
{
    this->NewMenu();
}
