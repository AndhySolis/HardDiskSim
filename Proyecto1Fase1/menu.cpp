#include "menu.h"
#include <iostream>

#include <fstream>
//MKUSR
void Menu::MKUSR(const char *USR, const char *Pwd, const char *Grp){
    if(OpeU->HayUsuarioEnElSistema()){
        bool Root=OpeU->UsuarioActualEsRoot();
        if(Root){
            std::string Adicion=OpeU->CrearUsuario(USR,Pwd,Grp);
            EDIT("/users.txt",Adicion.data());
        }else{
            std::cout<<"Se Necesitan Permisos 'Root' Para Crear Usuarios"<<std::endl;
        }
    }
}
//RMUSR
void Menu::RMUSR(const char *USR){
    if(OpeU->HayUsuarioEnElSistema()){
        bool Root=OpeU->UsuarioActualEsRoot();
        if(Root){
            std::string Actualizar=OpeU->RemoverUsuario(USR);
            REM("/users.txt");
            MKFILE("/users.txt",'0',Actualizar.data());
        }else{
            std::cout<<"Se Necesitan Permisos 'Root' Para Eliminar Usuarios"<<std::endl;
        }
    }
}
//RMGRP
void Menu::RMGRP(const char *Nombre){
    if(OpeU->HayUsuarioEnElSistema()){
        bool Root=OpeU->UsuarioActualEsRoot();
        if(Root){
            std::string Actualizar=OpeU->RemoverGrupo(Nombre);
            REM("/users.txt");
            MKFILE("/users.txt",'0',Actualizar.data());
        }else{
            std::cout<<"Se Necesitan Permisos 'Root' Para Eliminar Grupos"<<std::endl;
        }
    }
}
//MKGRP
void Menu::MKGRP(const char *Nombre){
    if(OpeU->HayUsuarioEnElSistema()){
        bool Root=OpeU->UsuarioActualEsRoot();
        if(Root){
            std::string Adicion=OpeU->CrearGrupo(Nombre);
            EDIT("/users.txt",Adicion.data());
        }else{
            std::cout<<"Se Necesitan Permisos 'Root' Para Crear Grupos"<<std::endl;
        }
    }
}

//REM
void Menu::REM(const char *Path){
    Disco *Ptr=this->PrimerDisco;
    if(Ptr==nullptr){
        std::cout<<"No Hay Ninguna Particion Montada En El Sistema"<<std::endl;
    }else {
        if(OpeU->HayUsuarioEnElSistema()){
            this->PrimerDisco->BorrarArchivoParticion(OpeU->IDMontado.data(),Path);
        }else{
            std::cout<<"No Hay Usuarios En El Sistema"<<std::endl;
        }
    }
}
//LOGOUT
void Menu::Logout(){
    if(OpeU->UsuarioActual==nullptr){
        std::cout<<"Error No Hay Usuario Logueado"<<std::endl;
    }else{
        std::cout<<"El Usuario '"<<OpeU->UsuarioActual->Usuario<<"' Ha Salido Del Sistema"<<std::endl;
        OpeU->Limpiar();
    }
}
//LOGIN
void Menu::LOGIN(const char *Usr, const char *Pwd, const char *Id){
    if(OpeU->HayUsuarioEnElSistema()){
        std::cout<<"Ya Hay Usuario En El Sistema"<<std::endl;
        return;
    }


    OpeU->CargarDatos(CAT("/users.txt"));
    bool Valido=OpeU->Login(Usr,Pwd);
    if(Valido){
        Disco *Ptr=this->PrimerDisco;
        if(Ptr==nullptr){
            std::cout<<"No Hay Ninguna Particion Montada En El Sistema"<<std::endl;
        }else {
            if(this->PrimerDisco->ExisteParticionMontada(Id)){
                OpeU->IDMontado=Id;
                std::cout<<"Credenciales Validas, Ingresando Como El Usuario: "<<Usr<<std::endl;
                std::cout<<"Usando La Particion Montada: "<<Id<<std::endl;
            }else{
                std::cout<<"La Particion Solicitada No Existe, Cancelando Login"<<std::endl;
                OpeU->Limpiar();
            }
        }
    }else{
        std::cout<<"Credenciales Incorrectas, Contrasenia o Usuario Erroneo"<<Id<<std::endl;
    }
}
//EDIT
void Menu::EDIT(const char *Path, const char *Contenido){
    Disco *Ptr=this->PrimerDisco;
    if(Ptr==nullptr){
        std::cout<<"No Hay Ninguna Particion Montada En El Sistema"<<std::endl;
    }else {
        if(OpeU->HayUsuarioEnElSistema()){
            this->PrimerDisco->ExpandirArchivoParticion(OpeU->IDMontado.data(),Path,Contenido);
        }else{
            std::cout<<"No Hay Usuarios En El Sistema"<<std::endl;
        }
    }
}
//CAT
std::string Menu::CAT(const char *Path){
    Disco *Ptr=this->PrimerDisco;
    std::string Lectura="";
    if(Ptr==nullptr){
        std::cout<<"No Hay Ninguna Particion Montada En El Sistema"<<std::endl;
    }else {
        if(OpeU->HayUsuarioEnElSistema()){
            Lectura= this->PrimerDisco->LeerArchivoParticion(OpeU->IDMontado.data(),Path);
        }else{
            std::cout<<"No Hay Usuarios En El Sistema"<<std::endl;
        }
    }
    return Lectura;
}
//MKDIR
void Menu::MKFILE(const char *Path, char Padre,const char *Contenido){
    Disco *Ptr=this->PrimerDisco;
    if(Ptr==nullptr){
        std::cout<<"No Hay Ninguna Particion Montada En El Sistema"<<std::endl;
    }else {
        if(OpeU->HayUsuarioEnElSistema()){
            this->PrimerDisco->CrearArchivoParticion(OpeU->IDMontado.data(),Path,Padre,Contenido);
        }else{
            std::cout<<"No Hay Usuarios En El Sistema"<<std::endl;
        }

    }
}
//MKDIR
void Menu::MKDIR(const char *Path, char Padre){
    Disco *Ptr=this->PrimerDisco;
    if(Ptr==nullptr){
        std::cout<<"No Hay Ninguna Particion Montada En El Sistema"<<std::endl;
    }else {
        if(OpeU->HayUsuarioEnElSistema()){
           this->PrimerDisco->CrearCarpetaParticion(OpeU->IDMontado.data(),Path,Padre);
        }else{
            std::cout<<"No Hay Usuarios En El Sistema"<<std::endl;
        }
    }
}
//MKFS
void Menu::MKFS(const char *Id, const char *Type, int EXT){
    std::cout<<"Falta Limpiar Particion Antes"<<std::endl;

    Disco *Ptr=this->PrimerDisco;
    if(Ptr==nullptr){
        std::cout<<"No Hay Ninguna Particion Montada En El Sistema"<<std::endl;
    }else {
        this->PrimerDisco->FormatearParticion(Id,EXT);
    }

}
//FDISK



bool Menu::DisponibleBorrarParticionMontada(const char *Id){
    if(this->PrimerDisco==nullptr){
        return true;
    }else{
        return this->PrimerDisco->ParticionLibreParaBorrar(Id);
    }

}

bool Menu::DisponibleBorrarDisco(const char *Path){
    if(this->PrimerDisco==nullptr){
            return true;
    }else{
        return this->PrimerDisco->DiscoLibreParaBorrar(Path);
    }

}
//REPORTES
void Menu::REP(const char *Id, const char *Name, const char *Path){
    Disco *Ptr=this->PrimerDisco;
    if(Ptr==nullptr){
        std::cout<<"No Hay Ninguna Particion Montada En El Sistema";
    }else {
        this->PrimerDisco->Reporte(Id,Path,Name);
    }

}

//Metodos Auxiliares
void Menu::LimpiarDiscosVacios(){
    Disco *Temporal=this->PrimerDisco;
    if(Temporal==nullptr)return;
    if(Temporal->Lista.count()==0){
        this->PrimerDisco=Temporal->Siguiente;
        return;
    }

    while(Temporal->Siguiente!=nullptr){
        if(Temporal->Siguiente->Lista.count()==0){
            Temporal->Siguiente=Temporal->Siguiente->Siguiente;
        }
        Temporal=Temporal->Siguiente;
    }
    if(Temporal->Lista.count()==0){
        this->PrimerDisco=Temporal->Siguiente;
        return;
    }

}

//UNMOUNT
void Menu::UNMOUNT(const char *Name){
    if(this->PrimerDisco==nullptr){
        std::cout<<"No Hay Ningún Disco En El Sistema"<<std::endl;
    }else{
        this->PrimerDisco->BorrarParticion(Name);
        this->LimpiarDiscosVacios();
    }

}
//MOUNT
void Menu::MOUNT(const char *Path,const char *Name){

    if(this->PrimerDisco==nullptr){        
        this->PrimerDisco=new Disco(Path,nullptr);       
        this->PrimerDisco->AgregarParticion(Name);
        this->LimpiarDiscosVacios();
    }else{
        Disco *Temporal=this->PrimerDisco;
        while(Temporal!=nullptr){

            if(Fun->IF(Temporal->Path,Path)){
                Temporal->AgregarParticion(Name);
                this->LimpiarDiscosVacios();
                return;
            }
            Temporal=Temporal->Siguiente;
        }



        this->PrimerDisco=new Disco(Path,this->PrimerDisco);
        this->PrimerDisco->AgregarParticion(Name);
        this->LimpiarDiscosVacios();
    }

}

//REMOVE DISK
void Menu::RMDISK(const char *Path){
    if(Fun->ExisteArchivo(Path)==false){
        std::cout<<"No Existe La Ubicacion "<<Path<<std::endl;
        return;
    }

    if(this->DisponibleBorrarDisco(Path)==false){
        std::cout<<"No se puede borrar disco porque esta montado en memoria"<<std::endl;
        return;
    }

       if(remove(Path)== 0) {
          std::cout<<"Disco Borrado"<<std::endl;
       } else {
         std::cout<<"No Se Pudo Borrar El Disco El Archivo Esta En Uso "<<std::endl;
       }

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
        FillName(Logic.part_name,Name);


        std::cout<<"Se Creo Particion Logica "<<Name<< " De Tamanio:"<<Original<<Unit<<" A Partir Del Byte:"<<NewLog<<" En El Disco:"<<Path<<std::endl;


        f=fopen(Path,"r+");
        fseek(f,Logic.part_start,SEEK_SET);
        fwrite(&Logic,sizeof (EBR),1,f);
        fclose(f);
        this->FillDisk(NewLog+int(sizeof(EBR)),NewLog+Size,'c',Path);
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
        FillName(NewLogic.part_name,Name);




        fseek(f,NewLog,SEEK_SET);
        fwrite(&NewLogic,sizeof (EBR),1,f);

        fclose(f);
        std::cout<<"Se Creo Particion Logica  "<<Name<< " De Tamanio:"<<Original<<Unit<<" A Partir Del Byte:"<<NewLog<<" En El Disco:"<<Path<<std::endl;


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



    if(true){
    Fun->Out("-----------------NewMenu--------------");
    Mkdisk(2,"ff",'M',"I:\\Disco.disk");
    FDisk(1,"ff",'M',"I:\\Disco.disk",'p',"a");
    MOUNT("I:\\Disco.disk","a");
    MKFS("vda1","full",1);
    MKDIR("/Carpeta/Ubuntu/Wayland/Limite/K/M",'1');
    MKDIR("/Carpeta3/Ubuntu/Wayland/Limite/K/M/Nueva",'1');
    MKFILE("/Carpeta3/Ubuntu/Wayland/Limite/K/M/Nueva/Hola.txt",'0',"y El vídeo proporciona una manera eficaz para ayudarle a demostrar el punto.Cuando haga clic en Vídeo en línea, puede pegar el código para ");
    MKFILE("/Dita.txt",'0',"El vídeo proporciona una manera eficaz para ayudarle a demostrar el punto.Cuando haga clic en Vídeo en línea, puede pegar el código para insertar del vídeo que desea agregar. ");
    EDIT("/Dita.txt","ContenidoMASContenidoMAS");

    REM("/users.txt");
    std::cout<<"HOLA"<<std::endl;





    REP("vda1","bm_inode","I:\\bm_inodo.txt");
    REP("vda1","bm_block","I:\\bm_bloque.txt");
    REP("vda1","tree","I:\\Arbol.png");
    //UNMOUNT("vda1");
    //RMDISK("Disco.disk");
    }
}
/*!
    \class QCache
    \brief Crea Disco Nuevo.
*/
void Menu::Mkdisk(int Size, const char *Fit, char Unit, const char *Path){
    int Origi=Size;
    FILE *f;
    MBR r;
    f=fopen(Path,"w");
    Size=Fun->Mult(Size,Unit);
    if (!f){
        std::cout<<"No Se Pudo Crear El Disco En La Ubicacion "<<Path<<std::endl;
        return ;
    }else{
        r.mbr_tamano=Size;
        Fun->Fecha(&r.mbr_fecha_creacion);
        r.mbr_disk_signature=Fun->GenerarNumeroRandom();
        FillPAR(&r.mbr_partition[0]);
        FillPAR(&r.mbr_partition[1]);
        FillPAR(&r.mbr_partition[2]);
        FillPAR(&r.mbr_partition[3]);
        r.disk_fit[0]=char(tolower(Fit[0]));
        r.disk_fit[1]=char(tolower(Fit[1]));
        fwrite(&r,sizeof(MBR),1,f);
        fclose(f);
        FillDisk(sizeof(MBR),Size-int(sizeof(MBR)),'\0',Path);
    }
    if(Fun->ExisteArchivo(Path)){
        std::cout<<"Se Creo Creo Disco Duro Tamanio:"<<Origi<<Unit<<" En:"<<Path<<std::endl;
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
    /*FILE *f;
    f=fopen(Path,"r+");
    int Kilo=Size/1024;
    if(Kilo>0){
        char Buffi[1024];
        for (int i=0;i<1024;i++) {
            Buffi[i]=Character;
        }

        fseek(f,Begin,SEEK_SET);
        for(int i=0;i<Kilo;i++){
            fwrite(&Buffi,sizeof (Buffi),1,f);
        }

    }
    Begin=Begin+(Kilo*1024);
    fseek(f,Begin,SEEK_SET);
    for(int i=Begin;i<Size;i++){
        fwrite(&Character,sizeof (Character),1,f);
    }
    fclose(f);*/
    FILE *f;
    f=fopen(Path,"r+");
    int Kilo=Size/1024;
    if(Kilo>0){
        char Buffi[1024];
        for (int i=0;i<1024;i++) {
            Buffi[i]=Character;
        }

        fseek(f,Begin,SEEK_SET);
        for(int i=0;i<Kilo;i++){

            fwrite(&Buffi,sizeof (Buffi),1,f);
        }

    }
    Size=Size-Kilo*1024;
    Begin=Begin+(Kilo*1024);
    fseek(f,Begin,SEEK_SET);
    for(int i=0;i<Size;i++){

        fwrite(&Character,sizeof (Character),1,f);
    }
    fclose(f);
}

Menu::Menu()
{
    this->NewMenu();
}
