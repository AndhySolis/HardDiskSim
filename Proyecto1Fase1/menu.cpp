#include "menu.h"
#include <iostream>
#include <fstream>
#include "recuperacion.h"
void Menu::Loss(std::string IDMontado){
    Disco *Ptr=this->PrimerDisco;
    if(Ptr==nullptr){
        std::cout<<"No Hay Ninguna Particion Montada En El Sistema"<<std::endl;
    }else {
        if(OpeU->HayUsuarioEnElSistema()){
            //Iniciar Perdida
            this->PrimerDisco->PerderInformacion(IDMontado.data());
        }else{
            std::cout<<"No Hay Usuarios En El Sistema"<<std::endl;
        }
    }
}
void Menu::Recuperar(std::string IDMontado){
    //FALTA AGREGAR LAS OPERACIONES EN CADA METODO
    Disco *Ptr=this->PrimerDisco;
    if(Ptr==nullptr){
        std::cout<<"No Hay Ninguna Particion Montada En El Sistema"<<std::endl;
    }else {

        std::queue<JOR> Cola=this->PrimerDisco->RecuperarInformacion(OpeU->IDMontado.data());
        std::string Backup=OpeU->IDMontado;
        OpeU->IDMontado=IDMontado;
        if(Cola.size()>0)
        SubRecuperar(Cola);
        OpeU->IDMontado=Backup;
    }
}
void Menu::SubRecuperar(std::queue<JOR> Cola){

    JOR Actual;
    IUG Tempo=OpeU->Permiso;    
    MKFS(OpeU->IDMontado.data(),1,1);


    while(Cola.empty()==false){
        Actual=Cola.front();



        OpeU->Permiso=Actual.Info;
        bool Recursivo=Actual.Recursivo;
        std::string Contenido=Actual.Contenido;
        std::string Direccion=Actual.Direccion;

        switch (Actual.Tipo) {
        case 4:{


            MKGRP(Contenido.data());
            break;
        }
        case 5:{
            RMGRP(Contenido.data());
            break;
        }
        case 6:{
            std::string s = Contenido;
            std::string delimiter = "|";
            size_t pos = 0;
            std::string token;
            std::string Usr,Pwd,Grp;
            std::string Escritura="";
            int Conta=1;
            while ((pos = s.find(delimiter)) != std::string::npos) {
                token = s.substr(0, pos);
                if(this->Fun->IF("",token)){

                }else{
                    if(Conta==1)
                        Usr=token;
                    if(Conta==2)
                        Pwd=token;
                    if(Conta==3)
                        Grp=token;
                    Conta++;
                }
                s.erase(0, pos + delimiter.length());
            }
            MKUSR(Usr.data(),Pwd.data(),Grp.data());
            break;
        }
        case 7:{
            RMUSR(Contenido.data());
            break;
        }
        case 8:{
            int Tipo=1;
            if(Recursivo)
                Tipo=2;
            CHMOD(Direccion.data(),atoi(Contenido.data()),Tipo);
            break;
        }
        case 9:{
            MKFILE(Direccion.data(),'1',Contenido.data());
            break;
        }
        case 11:{
            REM(Direccion.data());
            break;
        }
        case 12:{
            EDIT(Direccion.data(),Contenido.data());
            break;
        }
        case 13:{
            REN(Direccion.data(),Contenido.data());
            break;
        }
        case 14:{

            char Tipo='0';
            if(Recursivo)
                Tipo='1';
            MKDIR(Direccion.data(),Tipo);
            break;
        }
        case 15:{
            CP(Direccion.data(),Contenido.data());
            break;
        }
        case 16:{
            MV(Direccion.data(),Contenido.data());
            break;
        }
        case 17:{
            int Tipo=1;
            if(Recursivo)
                Tipo=2;
            CHOWN(Direccion.data(),(Contenido.data()),Tipo);
            break;
        }
        case 18:{
            CHGRP(Contenido.data(),Direccion.data());
            break;
        }
        default:{
            std::cout<<"NO PUEDE"<<Actual.Tipo<<std::endl;
            break;
        }
        }





        Cola.pop();
    }
    OpeU->Permiso=Tempo;
}
//MV
void Menu::MV(const char *PathOrigen, const char *PathDestino){
    Disco *Ptr=this->PrimerDisco;
    if(Ptr==nullptr){
        std::cout<<"No Hay Ninguna Particion Montada En El Sistema"<<std::endl;
    }else {
        if(OpeU->HayUsuarioEnElSistema()){

            this->PrimerDisco->MoverArchivoParticion(OpeU->IDMontado.data(),PathOrigen,PathDestino,OpeU->Permiso);
        }else{
            std::cout<<"No Hay Usuarios En El Sistema"<<std::endl;
        }
    }
}
//CP
void Menu::CP(const char *PathOrigen, const char *PathDestino){
    Disco *Ptr=this->PrimerDisco;
    if(Ptr==nullptr){
        std::cout<<"No Hay Ninguna Particion Montada En El Sistema"<<std::endl;
    }else {
        if(OpeU->HayUsuarioEnElSistema()){

            this->PrimerDisco->CopiarArchivoParticion(OpeU->IDMontado.data(),PathOrigen,PathDestino,OpeU->Permiso);
        }else{
            std::cout<<"No Hay Usuarios En El Sistema"<<std::endl;
        }
    }
}
//FIND
void Menu::FIND(const char *PathVirtual, const char *Nombre){
    Disco *Ptr=this->PrimerDisco;
    if(Ptr==nullptr){
        std::cout<<"No Hay Ninguna Particion Montada En El Sistema"<<std::endl;
    }else {
        if(OpeU->HayUsuarioEnElSistema()){

            this->PrimerDisco->BuscarArchivoParticion(OpeU->IDMontado.data(),PathVirtual,Nombre,OpeU->Permiso);
        }else{
            std::cout<<"No Hay Usuarios En El Sistema"<<std::endl;
        }
    }
}
//CHHGRP
void Menu::CHGRP(const char *Usr, const char *NuevoGrupo){
    if(OpeU->HayUsuarioEnElSistema()){
        bool Root=OpeU->UsuarioActualEsRoot();
        if(Root){
            std::string Actualizar=OpeU->CambiarGrupo(Usr,NuevoGrupo);
            REM("/users.txt");
            MKFILE("/users.txt",'0',Actualizar.data());
        }else{
            std::cout<<"Se Necesitan Permisos 'Root' Para Eliminar Usuarios"<<std::endl;
        }
    }else{
        std::cout<<"No Hay Usuario En El Sistema, Se Necesita Ingresar"<<std::endl;
    }
}
//REN
void Menu::REN(const char *PathVirtual, const char *NuevoNombre){
    Disco *Ptr=this->PrimerDisco;
    if(Ptr==nullptr){
        std::cout<<"No Hay Ninguna Particion Montada En El Sistema"<<std::endl;
    }else {
        if(OpeU->HayUsuarioEnElSistema()){

            this->PrimerDisco->RenombrarArchivoParticion(OpeU->IDMontado.data(),NuevoNombre,PathVirtual,OpeU->Permiso);
        }else{
            std::cout<<"No Hay Usuarios En El Sistema"<<std::endl;
        }
    }
}
//CHOWN
void Menu::CHOWN(const char *PathVirtual, std::string NuevoDuenio, int Tipo){
    Disco *Ptr=this->PrimerDisco;
    if(Ptr==nullptr){
        std::cout<<"No Hay Ninguna Particion Montada En El Sistema"<<std::endl;
    }else {
        if(OpeU->HayUsuarioEnElSistema()){
            int USR=OpeU->Uid(NuevoDuenio);
            if(USR==-1){
                std::cout<<"No Se Encontro El Usuario "<<NuevoDuenio<<std::endl;
                return;
            }
            this->PrimerDisco->PropietarioArchivoParticion(OpeU->IDMontado.data(),PathVirtual,Tipo,USR,OpeU->Permiso,NuevoDuenio.data());
        }else{
            std::cout<<"No Hay Usuarios En El Sistema"<<std::endl;
        }
    }
}
//CHMOD
void Menu::CHMOD(const char *PathVirtual, int Ugo, int Tipo){
    Disco *Ptr=this->PrimerDisco;
    if(Ptr==nullptr){
        std::cout<<"No Hay Ninguna Particion Montada En El Sistema"<<std::endl;
    }else {
        if(OpeU->HayUsuarioEnElSistema()){
            std::string Num=std::to_string(Ugo);
            std::string Entrada="2"+Fun->DecimalBinario(Num.data()[0]);
            Entrada=Entrada+Fun->DecimalBinario(Num.data()[1]);
            Entrada=Entrada+Fun->DecimalBinario(Num.data()[2]);
            Ugo=std::atoi(Entrada.c_str());
            this->PrimerDisco->PermisoArchivoParticion(OpeU->IDMontado.data(),PathVirtual,Tipo,Ugo,OpeU->Permiso,"");
        }else{
            std::cout<<"No Hay Usuarios En El Sistema"<<std::endl;
        }
    }
}
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
    }else{
        std::cout<<"No Hay Usuario En El Sistema, Se Necesita Ingresar"<<std::endl;
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
    }else{
        std::cout<<"No Hay Usuario En El Sistema, Se Necesita Ingresar"<<std::endl;
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
            std::cout<<"Se Ha Eliminado El Grupo "<<Nombre<<std::endl;
        }else{
            std::cout<<"Se Necesitan Permisos 'Root' Para Eliminar Grupos"<<std::endl;
        }
    }else{
        std::cout<<"No Hay Usuario En El Sistema, Se Necesita Ingresar"<<std::endl;
    }
}
//MKGRP
void Menu::MKGRP(const char *Nombre){
    if(OpeU->HayUsuarioEnElSistema()){
        bool Root=OpeU->UsuarioActualEsRoot();
        if(Root){

            std::string Adicion=OpeU->CrearGrupo(Nombre);
            if(!Fun->IF("",Adicion))
                EDIT("/users.txt",Adicion.data());
            std::cout<<"Se Ha Creado El Nuevo Grupo "<<Nombre<<std::endl;
        }else{
            std::cout<<"Se Necesitan Permisos 'Root' Para Crear Grupos"<<std::endl;
        }
    }else{
        std::cout<<"No Hay Usuario En El Sistema, Se Necesita Ingresar"<<std::endl;
    }
}

//REM
void Menu::REM(const char *Path){
    Disco *Ptr=this->PrimerDisco;
    if(Ptr==nullptr){
        std::cout<<"No Hay Ninguna Particion Montada En El Sistema"<<std::endl;
    }else {
        if(OpeU->HayUsuarioEnElSistema()){
            this->PrimerDisco->BorrarArchivoParticion(OpeU->IDMontado.data(),Path,OpeU->Permiso);
        }else{
            std::cout<<"No Hay Usuarios En El Sistema"<<std::endl;
        }
    }
}
//LOGOUT
void Menu::Logout(){
    if(OpeU->UsuarioActual.Uid==-1){
        std::cout<<"Error No Hay Usuario Logueado"<<std::endl;
    }else{
        this->PrimerDisco->Contar(OpeU->IDMontado.data(),false);

        std::cout<<"El Usuario '"<<OpeU->UsuarioActual.Usuario<<"' Ha Salido Del Sistema"<<std::endl;
        OpeU->Limpiar();
    }
}

//LOGIN
void Menu::LOGIN(const char *Usr, const char *Pwd, const char *Id){
    if(OpeU->HayUsuarioEnElSistema()){
        std::cout<<"Ya Hay Usuario En El Sistema"<<std::endl;
        return;
    }
    if(!this->PrimerDisco->ExisteParticionMontada(Id)){
        std::cout<<"La Particion Solicitada No Existe, Cancelando Login"<<std::endl;
        OpeU->Limpiar();
        return;
    }

    this->PrimerDisco->Contar(Id,true);

    IUG PermisoFalso;
    PermisoFalso.Gid=1;
    PermisoFalso.Uid=1;
    OpeU->CargarDatos(this->PrimerDisco->LeerArchivoParticion(Id,"/users.txt",PermisoFalso));
    bool Valido=OpeU->Login(Usr,Pwd);
    if(Valido){
        Disco *Ptr=this->PrimerDisco;
        if(Ptr==nullptr){
            std::cout<<"No Hay Ninguna Particion Montada En El Sistema"<<std::endl;
        }else {

                OpeU->IDMontado=Id;

                std::cout<<"Credenciales Validas, Ingresando Como El Usuario: "<<Usr<<std::endl;
                std::cout<<"Usando La Particion Montada: "<<Id<<std::endl;



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
            this->PrimerDisco->ExpandirArchivoParticion(OpeU->IDMontado.data(),Path,Contenido,OpeU->Permiso);
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
            Lectura= this->PrimerDisco->LeerArchivoParticion(OpeU->IDMontado.data(),Path,OpeU->Permiso);
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
            this->PrimerDisco->CrearArchivoParticion(OpeU->IDMontado.data(),Path,Padre,Contenido,OpeU->Permiso);
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
           this->PrimerDisco->CrearCarpetaParticion(OpeU->IDMontado.data(),Path,Padre,OpeU->Permiso);
        }else{
            std::cout<<"No Hay Usuarios En El Sistema"<<std::endl;
        }
    }
}
//MKFS
void Menu::MKFS(const char *Id, int Type,int Tipo){
    std::cout<<"Falta Limpiar Particion Antes"<<std::endl;

    Disco *Ptr=this->PrimerDisco;
    if(Ptr==nullptr){
        std::cout<<"No Hay Ninguna Particion Montada En El Sistema"<<std::endl;
    }else {
        int A=OpeU->Permiso.Gid;
        int B=OpeU->Permiso.Uid;
        OpeU->Permiso.Gid=1;
        OpeU->Permiso.Uid=1;
        this->PrimerDisco->FormatearParticion(Id,OpeU->Permiso,Type,Tipo);
        OpeU->Permiso.Gid=A;
        OpeU->Permiso.Uid=B;
    }

}





//FASE1

//REPORTES
void Menu::REP(const char *Id, const char *Name, const char *Path,const char *Ruta){
    Disco *Ptr=this->PrimerDisco;
    if(Ptr==nullptr){
        std::cout<<"No Hay Ninguna Particion Montada En El Sistema";
    }else {
        this->PrimerDisco->Reporte(Id,Path,Name,Ruta);
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
void Menu::Rmdisk(const char *Path){
    new RMDISK(Path);

}
//FDISKADD
/*!
    \class QCache
    \brief Busca Si El Tamaño Disponible En El Disco Danto Path Y Tamaño Requerido Del Bloque .
*/
void Menu::FDISKAdd(int Size, const char *Path, const char *Name){
    new FDISKADD(Size,Path,Name);
}
//FDISKDELETE
void Menu::FDISKDelete(const char *Delete, const char *Path, const char *Name){
    new FDISKDELETE(Delete,Path,Name,this->PrimerDisco);

}

//FDISK
void Menu::FDisk(int Size, const char *Fit, char Unit, const char *Path, char Type,const char *Name){
    new FDISK(Size,Fit,Unit,Path,Type,Name);
}


//RMDISK Y Utilidades

/*!
    \class QCache
    \brief Aquí Se Inicia El Menú.
*/
void Menu::NewMenu(){



    if(false){
    Fun->Out("-----------------NewMenu--------------");
    Mkdisk(2,"ff",'M',"/home/pc/Documents/Archivos/Prueba/Disco.disk");
    FDisk(1,"ff",'M',"/home/pc/Documents/Archivos/Prueba/Disco.disk",'p',"a");
    MOUNT("/home/pc/Documents/Archivos/Prueba/Disco.disk","a");
    MKFS("vda1",0,1);
    LOGIN("root","123","vda1");
    MKFILE("/Dita.txt",'0',"El vídeo proporciona una manera eficaz para ayudarle a demostrar el punto.Cuando haga clic en Vídeo en línea, puede pegar el código para insertar del vídeo que desea agregar. ");
    EDIT("/Dita.txt","ContenidoMASContenidoMAS");
    MKDIR("/Carpeta/Ubuntu/Wayland/Limite/K/M",'1');
    MKDIR("/Carpeta/Ubuntu/Wayland/Limite/K/M/Nueva",'1');
    MKFILE("/Carpeta/Ubuntu/Wayland/Limite/K/M/Nueva/Hola.txt",'0',"y El vídeo proporciona una manera eficaz para ayudarle a demostrar el punto.Cuando haga clic en Vídeo en línea, puede pegar el código para ");
    MKFILE("/Carpeta/Ubuntu/Wayland/Limite/K/M/Nueva/Hola.txt",'0',"y El vídeo proporciona una manera eficaz para ayudarle a demostrar el punto.Cuando haga clic en Vídeo en línea, puede pegar el código para ");

    CHMOD("/users.txt",233,1);
    REM("/dita.txt");


    //CAT("/users.txt");



    REP("vda1","bm_inode","/home/pc/Documents/Archivos/Prueba/bm_inodo.txt","");
    REP("vda1","bm_block","/home/pc/Documents/Archivos/Prueba/bm_bloque.txt","");
    REP("vda1","tree","/home/pc/Documents/Archivos/Prueba/Arbol.png","");
    std::cout<<"FIN DE EJECUCION"<<std::endl;
    //UNMOUNT("vda1");
    //RMDISK("Disco.disk");
    }
}
/*!
    \class QCache
    \brief Crea Disco Nuevo.
*/
void Menu::Mkdisk(int Size, const char *Fit, char Unit, const char *Path){
    new MKDISK(Size,Fit,Unit,Path);
}

/*!
    \class QCache
    \brief Llena El Disco Con Cierto Caracter(r+ Es para Actualizar W es para borrar y escribir).
*/


Menu::Menu()
{
    this->NewMenu();
}
