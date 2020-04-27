#include "find.h"

FIND::FIND(int Comienzo, std::string PathVirtual, const char *PathReal,IUG Permiso)
{
    this->Permiso=Permiso;
    Find(Comienzo,PathVirtual,PathReal);
}
//FIND Arbol
void FIND::Find(int Comienzo, std::string PathVirtual, const char *PathReal){
    int Buscar=BuscarActual(Comienzo,PathVirtual,PathReal);
    if(Buscar==-1){
        std::cout<<"No Se Encontro El Archivo O Carpeta En "<<PathVirtual<<std::endl;
        return ;
    }
    if(TienePermiso(Buscar,PathReal,"100",Permiso)==false){
        std::cout<<"No Tiene Permisos De Lectura Para "<<PathVirtual<<" No se puede aplicar comando Find"<<std::endl;
        return;
    }

    FindInodo(Comienzo,PathReal,"");

}

void FIND::FindDirectos(int Comienzo, const char *PathReal,int Tipo,std::string Expansion){
    FILE *f;
    f=fopen(PathReal,"r+");
    BCA Carpeta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);

    for(int i=0;i<4;i++){
        CON Contenido=Carpeta.content[i];
        if(Contenido.b_inodo!=-1){

            if(Tipo==0){//Carpeta
                std::cout<<Expansion<<"|_"<<Contenido.b_name<<std::endl;
                Expansion=Expansion+" ";
                FindInodo(Contenido.b_inodo,PathReal,Expansion);

            }else{
                std::cout<<Expansion<<"||_"<<Contenido.b_name<<std::endl;
            }
        }
    }

}
void FIND::FindIndirectos(int Nivel, int NivelActual, int Comienzo,  const char *PathReal,int Tipo,std::string Expansion){
    if(Nivel==NivelActual){
        FindDirectos(Comienzo,PathReal,Tipo,Expansion);
    }
    FILE *f;
    f=fopen(PathReal,"r+");
    BAP Apunta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Apunta,sizeof(Apunta),1,f);
    fclose(f);


    for(int i=0;i<16;i++){
        int Valor=Apunta.b_pointers[i];
        if(Valor!=-1){
           FindIndirectos(Nivel,NivelActual+1,Valor,PathReal,Tipo,Expansion);
        }
    }
}
void FIND::FindInodo(int Comienzo, const char *PathReal,std::string Expansion){
    if(TienePermiso(Comienzo,PathReal,"100",Permiso)==false){
        return ;
    }


    FILE *f;
    f=fopen(PathReal,"r+");
    INO Carpeta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);

    int Tipo=1;
    if(Carpeta.i_type=='0')
        Tipo=0;
    for(int i=0;i<12;i++){
        int Apuntador=Carpeta.i_block[i];
        if(Apuntador!=-1){
            FindIndirectos(0,0,Apuntador,PathReal,Tipo,Expansion);

        }
    }

    for(int i=0;i<3;i++){
        int Apuntador=Carpeta.i_block[i+12];
        if(Apuntador!=-1){
            FindIndirectos(1+i,0,Apuntador,PathReal,Tipo,Expansion);
        }
    }

}
