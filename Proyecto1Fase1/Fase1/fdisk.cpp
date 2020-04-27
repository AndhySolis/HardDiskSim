#include "fdisk.h"

FDISK::FDISK(int Size,const char Fit[2],char Unit,const char *Path,char Type,const char *Name)
{
    this->Fun=new Functions();
    Type=char(tolower(Type));
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


void FDISK::NewPrimary(int Size, const char *Fit, char Unit, const char *Path,const char *Name){
    int Index=HasSlot(Path);
    int Original=Size;
    Size=Fun->Mult(Size,Unit);
    FILE *f;
    MBR r;
    f=fopen(Path,"r");
    if (!f){
        return;
    }
    fread(&r,sizeof(MBR),1,f);
    fclose(f);
    if(Index==-1){
        Fun->Out("Este Disco Ya Llego Al Limite De Particiones Primarias");
    }else{
        char SubFit [2];
        SubFit[0]=Fit[0];
        SubFit[1]=Fit[1];
        int Fit = Fun->DiskFit(SubFit,Size,Path);
           if(Fit==-1){
            Fun->Out("No Hay Espacio Suficiente Para La Particion");
        }else{
            std::cout<<"Se Creo Particion Primaria: "<<Name<< " De Tamanio:"<<Original<<Unit<<" A Partir Del Byte:"<<Fit<<" En El Disco:"<<Path<<std::endl;
            r.mbr_partition[Index-1].part_status='t';
            r.mbr_partition[Index-1].part_type='p';
            r.mbr_partition[Index-1].part_fit[0]=SubFit[0];
            r.mbr_partition[Index-1].part_fit[1]=SubFit[1];
            r.mbr_partition[Index-1].part_start=Fit;
            r.mbr_partition[Index-1].part_size=Size;
            Fun->FillName(r.mbr_partition[Index-1].part_name,Name);
            f=fopen(Path,"r+");
            if (!f)
                return ;
            fseek(f,0,SEEK_SET);
            fwrite(&r,sizeof(MBR),1,f);
            fclose(f);
            Fun->FillDisk(Fit,Fit+Size,'p',Path);
        }
    }
}
void FDISK::NewExtended(int Size, const char *Fit, char Unit, const char *Path,const char *Name){
    int Original=Size;
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
        std::cout<<"Se Creo Particion Extendida "<<Name<< " De Tamanio:"<<Original<<Unit<<" A Partir Del Byte:"<<Fit<<" En El Disco:"<<Path<<std::endl;
        if(Fit==-1){
            Fun->Out("No Hay Espacio Suficiente Para La Particion");
        }else{
            r.mbr_partition[Index-1].part_status='t';
            r.mbr_partition[Index-1].part_type='e';
            r.mbr_partition[Index-1].part_fit[0]=SubFit[0];
            r.mbr_partition[Index-1].part_fit[1]=SubFit[1];
            r.mbr_partition[Index-1].part_start=Fit;
            r.mbr_partition[Index-1].part_size=Size;
            Fun->FillName(r.mbr_partition[Index-1].part_name,Name);
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
            Fun->FillName(Logic.part_name,Name);
            fseek(f,Fit,SEEK_SET);
            fwrite(&Logic,sizeof (EBR),1,f);
            fclose(f);

            //Arreglar
            Fun->FillDisk(Fit+int(sizeof(EBR)),Fit+Size,'e',Path);
        }
    }
}

void FDISK::NewLogical(int Size, const char *Fit, char Unit, const char *Path,const char *Name){
    int Original=Size;
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
        Fun->FillName(Logic.part_name,Name);


        std::cout<<"Se Creo Particion Logica "<<Name<< " De Tamanio:"<<Original<<Unit<<" A Partir Del Byte:"<<NewLog<<" En El Disco:"<<Path<<std::endl;


        f=fopen(Path,"r+");
        fseek(f,Logic.part_start,SEEK_SET);
        fwrite(&Logic,sizeof (EBR),1,f);
        fclose(f);
        Fun->FillDisk(NewLog+int(sizeof(EBR)),NewLog+Size,'c',Path);
        return ;
    }



    if(NewLog==-1){
        Fun->Out("No Hay Espacio Para La Unidad Logica  En Esta Particion Extendida");
        //std::cout<<Size<<"---"<<Extended.part_start<<"---"<<Extended.part_start+Extended.part_size<<std::endl;
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
        Fun->FillName(NewLogic.part_name,Name);




        fseek(f,NewLog,SEEK_SET);
        fwrite(&NewLogic,sizeof (EBR),1,f);

        fclose(f);
        std::cout<<"Se Creo Particion Logica  "<<Name<< " De Tamanio:"<<Original<<Unit<<" A Partir Del Byte:"<<NewLog<<" En El Disco:"<<Path<<std::endl;


        Fun->FillDisk(NewLog+int(sizeof(EBR)),NewLog+(Size),'c',Path);
    }
}
int FDISK::HasSlot(const char *Path){
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
