#include "recuperacion.h"
void Recuperacion::RecuCHGRP(int Comienzo, const char *Path, const char *Grp, const char *Usr,IUG Inf){
    JOR Nuevo;
    Nuevo.Tipo=18;
    Nuevo.Info=Inf;
    strcpy(Nuevo.Direccion,Grp);
    strcpy(Nuevo.Contenido,Usr);
    NuevoRegistro(Comienzo,Path,Nuevo);
}
void Recuperacion::RecuCHOWN(int Comienzo, const char *Path, const char *PathVirtual, const char *Usr, bool Recursivo,IUG Inf){
    JOR Nuevo;
    Nuevo.Tipo=17;
    Nuevo.Info=Inf;
    strcpy(Nuevo.Direccion,PathVirtual);
    strcpy(Nuevo.Contenido,Usr);
    Nuevo.Recursivo=Recursivo;
    NuevoRegistro(Comienzo,Path,Nuevo);
}
void Recuperacion::RecuMV(int Comienzo, const char *Path, const char *PathOrigen, const char *PathDestino,IUG Inf){
    JOR Nuevo;
    Nuevo.Tipo=16;
    Nuevo.Info=Inf;
    strcpy(Nuevo.Direccion,PathOrigen);
    strcpy(Nuevo.Contenido,PathDestino);
    NuevoRegistro(Comienzo,Path,Nuevo);
}
void Recuperacion::RecuCP(int Comienzo, const char *Path, const char *PathOrigen, const char *PathDestino,IUG Inf){
    JOR Nuevo;
    Nuevo.Tipo=15;
    Nuevo.Info=Inf;
    strcpy(Nuevo.Direccion,PathOrigen);
    strcpy(Nuevo.Contenido,PathDestino);
    NuevoRegistro(Comienzo,Path,Nuevo);
}
void Recuperacion::RecuMKDIR(int Comienzo, const char *Path, const char *PathVirtual, bool Recursivo,IUG Inf){
    JOR Nuevo;
    Nuevo.Tipo=14;
    Nuevo.Info=Inf;
    strcpy(Nuevo.Direccion,PathVirtual);
    Nuevo.Recursivo=Recursivo;
    NuevoRegistro(Comienzo,Path,Nuevo);
}
void Recuperacion::RecuREN(int Comienzo, const char *Path, const char *PathVirtual, const char *NuevoNombre,IUG Inf){
    JOR Nuevo;
    Nuevo.Tipo=13;
    Nuevo.Info=Inf;
    strcpy(Nuevo.Direccion,PathVirtual);
    strcpy(Nuevo.Contenido,NuevoNombre);
    NuevoRegistro(Comienzo,Path,Nuevo);
}
void Recuperacion::RecuEDIT(int Comienzo, const char *Path, const char *PathVirtual, bool Recursivo, int Tamanio, int PosiArchivo,IUG Inf){
    JOR Nuevo;
    Nuevo.Tipo=12;
    Nuevo.Info=Inf;
    strcpy(Nuevo.Direccion,PathVirtual);
    Nuevo.TamanioArchivo=Tamanio;
    Nuevo.UbicacionArchivo=PosiArchivo;
    Nuevo.Recursivo=Recursivo;
    NuevoRegistro(Comienzo,Path,Nuevo);
}
void Recuperacion::RecuREM(int Comienzo, const char *Path, const char *PathVirtual,IUG Inf){
    JOR Nuevo;
    Nuevo.Tipo=11;
    strcpy(Nuevo.Direccion,PathVirtual);
    NuevoRegistro(Comienzo,Path,Nuevo);
    Nuevo.Info=Inf;
}
void Recuperacion::RecuMKFILE(int Comienzo, const char *Path, const char *PathVirtual, bool Recursivo, int Tamanio, int PosiArchivo,IUG Inf){
    JOR Nuevo;
    Nuevo.Tipo=9;
    strcpy(Nuevo.Direccion,PathVirtual);
    Nuevo.TamanioArchivo=Tamanio;
    Nuevo.UbicacionArchivo=PosiArchivo;
    Nuevo.Recursivo=Recursivo;
    Nuevo.Info=Inf;
    NuevoRegistro(Comienzo,Path,Nuevo);
}
void Recuperacion::RecuCHMOD(int Comienzo, const char *Path, const char *PathVirtual, const char *Ugo, bool Recursivo,IUG Inf){
    JOR Nuevo;
    Nuevo.Tipo=8;
    strcpy(Nuevo.Direccion,PathVirtual);
    strcpy(Nuevo.Contenido,Ugo);
    Nuevo.Recursivo=Recursivo;
    Nuevo.Info=Inf;
    NuevoRegistro(Comienzo,Path,Nuevo);
}
void Recuperacion::RecuRMUSR(int Comienzo, const char *Path, const char *Usr,IUG Inf){
    JOR Nuevo;
    Nuevo.Tipo=7;
    strcpy(Nuevo.Contenido,Usr);
    Nuevo.Info=Inf;
    NuevoRegistro(Comienzo,Path,Nuevo);
}
void Recuperacion::RecuMKUSR(int Comienzo, const char *Path, const char *Usr, const char *Pwd, const char *Grp,IUG Inf){
    JOR Nuevo;
    Nuevo.Tipo=6;
    std::string Concatenar="";
    Concatenar=Concatenar+Usr+"|"+Pwd+"|"+Grp+"|";
    strcpy(Nuevo.Contenido,Concatenar.c_str());
    Nuevo.Info=Inf;
    NuevoRegistro(Comienzo,Path,Nuevo);
}
void Recuperacion::RecuRMGRP(int Comienzo, const char *Path,const char *Nombre,IUG Inf){
    JOR Nuevo;
    Nuevo.Tipo=5;
    strcpy(Nuevo.Contenido,Nombre);
    Nuevo.Info=Inf;
    NuevoRegistro(Comienzo,Path,Nuevo);
}
void Recuperacion::RecuMKGRP(int Comienzo, const char *Path,const char *Nombre,IUG Inf){
    JOR Nuevo;
    Nuevo.Tipo=4;
    strcpy(Nuevo.Contenido,Nombre);
    Nuevo.Info=Inf;
    NuevoRegistro(Comienzo,Path,Nuevo);
}
void Recuperacion::NuevoRegistro(int Comienzo, const char *Path, JOR Recu){
    FILE *f;
    f=fopen(Path,"r+");
    int Numero;
    SPB Super;
    //Leer El Super Bloque
    fseek(f,Comienzo,SEEK_SET);
    fread(&Super,sizeof (Super),1,f);
    //Leer El Primero De Recuperación
    //Ver Si Tiene Espacio
    fseek(f,Comienzo+int(sizeof (SPB)),SEEK_SET);
    fread(&Numero,sizeof (Numero),1,f);
    fclose(f);

    if(Numero==-1){
        std::cout<<"Alerta EL Journaling Se Ha Quedado Sin Espacio, Las Siguientes Operaciones No Seran Recuperables"<<std::endl;
        return;
    }

    f=fopen(Path,"r+");
    //Guardar El Espacio Donde Se Va A Escribir
    int Antes=Numero;
    //Actualizar El Ultimo Numero
    Numero=Numero+int(sizeof (JOR));
    if(Numero>=Super.s_bm_inode_start)
        Numero=-1;
    //Escribir Ultimo Numero
    fseek(f,Comienzo+int(sizeof (SPB)),SEEK_SET);
    fwrite(&Numero,sizeof (Numero),1,f);
    /*JOR Recu;
    //Leer Recu
    fseek(f,Antes,SEEK_SET);
    fread(&Recu,sizeof (Recu),1,f);
    //Llenar Recu
    Recu.Tipo=TipoOperacion;
    strcpy(Recu.Direccion,PathVirtual);
    strcpy(Recu.Contenido,Contenido);
    Recu.Recursivo=Recursivo;*/
    Recu.Siguiente=Numero;
    //Escribir Recu
    fseek(f,Antes,SEEK_SET);
    fwrite(&Recu,sizeof (Recu),1,f);
    //Si No Es EL Ultimo Recu
    if(Numero!=-1){
        // Tope
        //Recu Siguiente
        JOR Tope;
        //Llenar Recu
        Tope.Tipo=-1;
        strcpy(Tope.Direccion,"....");
        strcpy(Tope.Contenido,"....");
        Tope.Siguiente=-1;
        //Escribir Recu
        fseek(f,Numero,SEEK_SET);
        fwrite(&Tope,sizeof (Tope),1,f);
    }
    fclose(f);
}
void Recuperacion::IniciarJOUR(int Comienzo, const char *Path){
    FILE *f;
    f=fopen(Path,"r+");
    SPB Super;
    //Leer El Super Bloque
    fseek(f,Comienzo,SEEK_SET);
    fread(&Super,sizeof (Super),1,f);
    //GenerarNumeroParaColocarJour
    int Numero=Comienzo+int(sizeof (SPB));
    if(Numero>=Super.s_bm_inode_start)
        Numero=-1;
    fseek(f,Comienzo+int(sizeof (SPB)),SEEK_SET);
    fwrite(&Numero,sizeof (Numero),1,f);

    //Recu Siguiente
    JOR Tope;
    //Llenar Recu
    Tope.Tipo=-1;
    strcpy(Tope.Direccion,"....");
    strcpy(Tope.Contenido,"....");
    Tope.Siguiente=-1;
    //Escribir Recu
    fseek(f,Numero,SEEK_SET);
    fwrite(&Tope,sizeof (Tope),1,f);
    fclose(f);
}
Recuperacion::Recuperacion()
{

}
std::queue<JOR> Recuperacion::ListaDeOperaciones(int Comienzo, const char *Path){
    FILE *f;
    f=fopen(Path,"r+");
    SPB Super;
    //Leer El Super Bloque
    fseek(f,Comienzo,SEEK_SET);
    fread(&Super,sizeof (Super),1,f);
    //IniciarPuntero
    int Puntero=Comienzo+int(sizeof (Super))+int(sizeof (int));
    std::queue<JOR> Cola;
    for (int i=0;i<Super.s_inodes_count;i++) {

        //Leer El JOR
        JOR Actual;
        fseek(f,Puntero,SEEK_SET);
        fread(&Actual,sizeof(Actual),1,f);
        //Meter Si Es Valido
        if(Actual.Tipo!=-1)
        {
            Cola.push(Actual);
        }
        //Actualizar Puntero
        Puntero=Actual.Siguiente;
        //Ver Si Hay Siguiente
        if(Puntero==-1)
            break;
    }

    fclose(f);
    return Cola;
}
