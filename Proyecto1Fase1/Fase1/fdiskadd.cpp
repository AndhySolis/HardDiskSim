#include "fdiskadd.h"
FDISKADD::FDISKADD(int Size, const char *Path, const char *Name){
    Fun = new Functions();
    std::cout<<"Operacion Sobre:"<<std::endl<<Path<<std::endl;
    if(Size>0){
        AgregarMas(Size,Path,Name);
    }else{

        AgregarMenos(Size,Path,Name);
    }
}

void FDISKADD::AgregarMas(int Size, const char *Path, const char *Name){
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

              std::cout<<"Se Agrego Un Espacio De "<<Size<<" A La Particion Logica '"<<Name<<"'"<<std::endl;
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

            std::cout<<"Se Agrego Un Espacio De "<<Size<<" A La Particion Primaria|Extendida '"<<Name<<"'"<<std::endl;

        }
    }


}
void FDISKADD::AgregarMenos(int Size, const char *Path, const char *Name){
    if(Size<0){
        Size=Size*-1;
    }

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
void FDISKADD::ReducirLogica(int Size, const char *Path, EBR Ext,const char *Name){
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
void FDISKADD::ReducirPrimaria(int Size, const char *Path, int Indice){
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
