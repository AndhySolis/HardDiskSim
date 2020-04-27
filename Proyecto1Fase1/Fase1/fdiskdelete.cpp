#include "fdiskdelete.h"

FDISKDELETE::FDISKDELETE(const char *Delete,const char *Path,const char *Name,Disco *Primero)
{
    this->Primero=Primero;
    Fun = new Functions();
    FILE *f;
    MBR Main;
    f=fopen(Path,"r+");
    if (!f){
        return;
    }
    fread(&Main,sizeof(MBR),1,f);
    fclose(f);
    if(this->DisponibleBorrarParticionMontada(Name)==false){
        std::cout<<"No Se Puede Borrar La Partición:"<<Name<<" Debido a que esta montada en memoria"<<std::endl;
        return ;
    }

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

void FDISKDELETE::DeleteFastLogic(EBR InputLogic, const char *Path){
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
            Fun->FillName(InputLogic.part_name,"");
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
void FDISKDELETE::DeleteFullLogic(EBR InputLogic, const char *Path){
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
        Fun->FillDisk(InputLogic.part_start+int(sizeof (EBR)),InputLogic.part_size,'\0',Path);
    }else{
        Fun->FillDisk(InputLogic.part_start,InputLogic.part_size,'\0',Path);
    }
}
void FDISKDELETE::DeleteFast(PAR Parti, const char *Path){

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
            Fun->FillPAR(&Extended);
            //std::cout<<Extended.part_status<<" {*}"<<std::endl;

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
void FDISKDELETE::DeleteFull(PAR Parti, const char *Path){
    this->DeleteFast(Parti,Path);
    Fun->FillDisk(Parti.part_start,Parti.part_size,'\0',Path);
}
bool FDISKDELETE::DisponibleBorrarParticionMontada(const char *Id){
    if(this->Primero==nullptr){
        return true;
    }else{
        return this->Primero->ParticionLibreParaBorrar(Id);
    }

}
