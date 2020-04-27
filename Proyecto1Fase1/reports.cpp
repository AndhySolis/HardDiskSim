#include "reports.h"
#include "structsext.h"
#include "recuperacion.h"
//Journaling
void Reports::ReporteJournaling(int Inicio, const char *Disco, const char *Path){
    Recuperacion *Recu=new Recuperacion();
    std::queue<JOR> Cola =Recu->ListaDeOperaciones(Inicio,Disco);

    std::cout<<"Journaling Cola     "<<Cola.size()<<std::endl;


    std::string Salida="digraph G { \n rankdir=LR node \n [shape=plaintext] \n";
    Salida=Salida+"I"+std::to_string(0)+" [ label=< <TABLE BGCOLOR=\"white\">";

    std::string Color="cadetblue";
    Salida=Salida+"<TR>\n";
    Salida=Salida+"<TD BGCOLOR=\""+Color+"\">"+"Tipo"+"</TD><TD BGCOLOR=\""+Color+"\">"+"Parametro A"+"</TD>";
    Salida=Salida+"<TD BGCOLOR=\""+Color+"\">"+"Parametro B"+"</TD></TR>";







    Color="cadetblue2";
    JOR Actual;
    while (Cola.empty()==false) {
        Actual=Cola.front();
        Salida=Salida+"<TR>\n";
        Salida=Salida+"<TD BGCOLOR=\""+Color+"\">"+std::to_string(Actual.Tipo)+"</TD><TD BGCOLOR=\""+Color+"\">"+Actual.Contenido+"</TD>";
        Salida=Salida+"<TD BGCOLOR=\""+Color+"\">"+Actual.Direccion+"</TD></TR>";


        Cola.pop();
    }

    Salida=Salida+"</TABLE>>] \n\n"+"\n } \n";






    std::string Pth=Path;
    Pth=Pth+".dot";
    FILE *f;
    f=fopen(Pth.data(),"w");
    if (!f){
        return ;
    }else{

        fwrite(Salida.data(),Salida.length(),1,f);
        fclose(f);

        std::string CMD="dot -Tpng "+Pth+" -o ";
        CMD = CMD+Path+".png";
        const char *command = CMD.data();
        system(command);
    }
}
//LS
std::string Reports::LsInodos(int Comienzo, const char *PathReal,const char *Nombre){


    FILE *f;
    f=fopen(PathReal,"r+");
    INO Inodo;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Inodo,sizeof(Inodo),1,f);
    fclose(f);
    std::string Concatenar="";


    int Tipo;
    std::string TipoIno="Carpeta";
    if(Inodo.i_type=='1'){
        Tipo=1;
        TipoIno="Archivo";


    }
    else
        Tipo=0;



    std::string Permisos="";
    std::string MiniPer=std::to_string(Inodo.i_perm);

    for(int j=0;j<3;j++){
        for(int i=0;i<3;i++){
            int Index=i+1+j*3;
            if(MiniPer[Index]=='0'){
                Permisos=Permisos+"-";
                if(Index==3||Index==6||Index==9){
                    Permisos=Permisos+"   ";
                }
            }
            else{
                if(Index==1 || Index==4 || Index==7){
                    Permisos=Permisos+"r";
                }else if(Index==2 || Index==5 || Index==8){
                    Permisos=Permisos+"w";
                }else{
                    Permisos=Permisos+"x   ";
                }

            }
        }
    }

    std::string Owner=std::to_string(Inodo.i_uid);
    std::string Grupo=std::to_string(Inodo.i_gid);
    std::string Size=std::to_string(Inodo.i_size);
    std::string FechaM=Fun->FechaString(&Inodo.i_mtime);
    std::string FechaC=Fun->FechaString(&Inodo.i_ctime);
    std::string Name=Nombre;

    Concatenar=Concatenar+NuevaFilaLS("cadetblue2",Permisos,Owner,Grupo,Size,FechaM,FechaC,TipoIno,Name);


    for(int i=0;i<12;i++){
        int Comprobar=Inodo.i_block[i];

        if(Comprobar!=-1){
            Concatenar =Concatenar+LsIndirectos(0,0,Comprobar,PathReal,Tipo);
        }

    }
    for(int i=0;i<3;i++){
        int Comprobar=Inodo.i_block[12+i];
        if(Comprobar!=-1){
            Concatenar=Concatenar+LsIndirectos(1+i,0,Comprobar,PathReal,Tipo);
        }
    }


    return Concatenar;
}
std::string Reports::LsDirectos(int Comienzo,const char *PathReal,int Tipo){
    FILE *f;
    f=fopen(PathReal,"r+");
    BCA Carpeta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);

    std::string Concatenar="";
    for(int i=0;i<4;i++){
        CON Contenido=Carpeta.content[i];
        if(Contenido.b_inodo!=-1){
            if(Tipo==0){
                Concatenar=Concatenar+LsInodos(Contenido.b_inodo,PathReal,Contenido.b_name);
            }
        }
    }

    return Concatenar;
}

std::string Reports::LsIndirectos(int Nivel, int NivelActual, int Comienzo,  const char *PathReal,int Tipo){
    if(Nivel==NivelActual){

        return LsDirectos(Comienzo,PathReal,Tipo);
    }
    FILE *f;
    f=fopen(PathReal,"r+");
    BAP Apunta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Apunta,sizeof(Apunta),1,f);
    fclose(f);
    std::string Concatenar="";
    for(int i=0;i<16;i++){
        int Valor=Apunta.b_pointers[i];
          if(Valor!=-1){
            Concatenar=Concatenar+LsIndirectos(Nivel,NivelActual+1,Valor,PathReal,Tipo);
        }
    }

    return Concatenar;
}

void Reports::ReporteLS(int Inicio, const char *PathReal, const char *Salida,const char *Nombre){

    if(Inicio==-1)
        return;

    std::string Concatenar="digraph G { \n rankdir=LR node \n [shape=plaintext] \n";
    Concatenar=Concatenar+"I"+std::to_string(0)+" [ label=< <TABLE BGCOLOR=\"white\">";
    Concatenar=Concatenar+NuevaFilaLS("cadetblue","Permisos","Owner","Grupo","Size","Fecha Modificacion","Fecha Creacion","Tipo","Name");
    Concatenar=Concatenar+LsInodos(Inicio,PathReal,Nombre);
    Concatenar=Concatenar+"</TABLE>>] \n";
    Concatenar=Concatenar+"\n } \n";




    std::string Pth=Salida;
    Pth=Pth+".dot";
    FILE *f;
    f=fopen(Pth.data(),"w");
    if (!f){
        return ;
    }else{

        fwrite(Concatenar.data(),Concatenar.length(),1,f);
        fclose(f);

        std::string CMD="dot -Tpng "+Pth+" -o ";
        CMD = CMD+Salida+".png";
        std::cout<<CMD<<std::endl;
        const char *command = CMD.data();
        system(command);
    }
}

std::string Reports::NuevaFilaLS(std::string Color,std::string Permiso, std::string Owner, std::string Grupo, std::string Size, std::string Fecha, std::string Hora, std::string Tipo, std::string Name){
    std::string Salida="";

    Salida=Salida+"<TR>\n";
    Salida=Salida+"<TD BGCOLOR=\""+Color+"\">"+Permiso+"</TD><TD BGCOLOR=\""+Color+"\">"+Owner+"</TD>";
    Salida=Salida+"<TD BGCOLOR=\""+Color+"\">"+Grupo+"</TD><TD BGCOLOR=\""+Color+"\">"+Size+"</TD>";
    Salida=Salida+"<TD BGCOLOR=\""+Color+"\">"+Fecha+"</TD><TD BGCOLOR=\""+Color+"\">"+Hora+"</TD>";
    Salida=Salida+"<TD BGCOLOR=\""+Color+"\">"+Tipo+"</TD><TD BGCOLOR=\""+Color+"\">"+Name+"</TD>";
    Salida=Salida+"</TR>\n";

    return Salida;
}
//File
void Reports::ReporteFile(const char *Path, const char *Contenido){

    std::string Salida=Contenido;
    if(Fun->IF(Salida,""))
    {
        std::cout<<"Error No Se Encontro Contenido O El Archivo Que Se BUscaba Reporte File"<<std::endl;
        return;
    }

    FILE *f;
    char Cop[1+Salida.length()];
    strcpy(Cop,Salida.c_str());
    std::string Pth=Path;
    Pth=Pth+".txt";

    f=fopen(Pth.data(),"w");
    if (!f){
        return ;
    }else{
        fwrite(&Cop,sizeof(Cop),1,f);
        fclose(f);
    }


}
//
std::string Reports::RecorrerInodos(int Comienzo, const char *PathReal){
    ColaI.push(Comienzo);

    FILE *f;
    f=fopen(PathReal,"r+");
    INO Inodo;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Inodo,sizeof(Inodo),1,f);
    fclose(f);
    std::string Concatenar="";


    int Tipo;
    if(Inodo.i_type=='1')
        Tipo=1;
    else
        Tipo=0;
    for(int i=0;i<12;i++){
        int Comprobar=Inodo.i_block[i];

        if(Comprobar!=-1){
            Concatenar =Concatenar+RecorrerIndirectos(0,0,Comprobar,PathReal,Tipo);
        }

    }
    for(int i=0;i<3;i++){
        int Comprobar=Inodo.i_block[12+i];
        if(Comprobar!=-1){
            Concatenar=Concatenar+RecorrerIndirectos(1+i,0,Comprobar,PathReal,Tipo);
        }
    }


    return Concatenar;
}
std::string Reports::RecorrerDirectos(int Comienzo,const char *PathReal,int Tipo){
    Cola.push(Comienzo);

    FILE *f;
    f=fopen(PathReal,"r+");
    BCA Carpeta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);

    std::string Concatenar="";
    Concatenar=Concatenar+"B"+std::to_string(Comienzo)+" [ label=< <TABLE BGCOLOR=\"white\">";
    Concatenar=Concatenar+"<TR><TD COLSPAN=\"2\" BGCOLOR=\"chartreuse4\" > Bloque_"+std::to_string((Comienzo-Contador)/sizeof (BCA))+"</TD></TR>\n";

    std::string Punteros="";
    for(int i=0;i<4;i++){
        CON Conte=Carpeta.content[i];
        std::string Prueba=Conte.b_name;
        Prueba=Prueba.substr(0,12);


        Concatenar=Concatenar+NuevaFila("darkseagreen3","darkolivegreen1","b_name",Prueba)+"\n";
        Concatenar=Concatenar+"<TR>"+"<TD  BGCOLOR=\""+"darkseagreen3"+"\">"+"b_inodo"+std::to_string(i)+"</TD><TD PORT=\"P"+std::to_string(i)+"\" BGCOLOR=\""+"darkolivegreen1"+"\">"+std::to_string(Conte.b_inodo)+"</TD>  </TR> \n";

    }
    Concatenar=Concatenar+"</TABLE>>] \n";
    Concatenar=Concatenar+Punteros;
    for(int i=0;i<4;i++){
        CON Contenido=Carpeta.content[i];
        if(Contenido.b_inodo!=-1){




            if(Tipo==0){
                Concatenar=Concatenar+RecorrerInodos(Contenido.b_inodo,PathReal);
            }else{
                Concatenar=Concatenar+RecorrerBloqueContenido(Contenido.b_inodo,PathReal);
            }
        }
    }

    return Concatenar;
}
std::string Reports::RecorrerBloqueContenido(int Comienzo, const char *PathReal){
    Cola.push(Comienzo);
    FILE *f;
    f=fopen(PathReal,"r+");
    BAR Dato;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Dato,sizeof(Dato),1,f);
    fclose(f);
    std::string Concatenar="";
    Concatenar=Concatenar+"B"+std::to_string(Comienzo)+" [ label=< <TABLE BGCOLOR=\"white\">";
    Concatenar=Concatenar+"<TR><TD COLSPAN=\"2\" BGCOLOR=\"deeppink3\" > Bloque_"+std::to_string((Comienzo-Contador)/sizeof (BCA))+"</TD></TR>\n";


    std::string Prueba=Dato.b_content;
    Prueba=Prueba.substr(0,64);
    Concatenar=Concatenar+NuevaFila("deeppink","floralwhite","Contenido",Prueba)+"\n";
    Concatenar=Concatenar+"</TABLE>>] \n";


    return Concatenar;
}
std::string Reports::RecorrerIndirectos(int Nivel, int NivelActual, int Comienzo,  const char *PathReal,int Tipo){
    if(Nivel==NivelActual){

        return RecorrerDirectos(Comienzo,PathReal,Tipo);
    }
    Cola.push(Comienzo);
    FILE *f;
    f=fopen(PathReal,"r+");
    BAP Apunta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Apunta,sizeof(Apunta),1,f);
    fclose(f);
    std::string Concatenar="";
    std::string Punteros="";
    //Graficando El Inodo
    Concatenar=Concatenar+"B"+std::to_string(Comienzo)+" [ label=< <TABLE BGCOLOR=\"white\">";
    Concatenar=Concatenar+"<TR><TD COLSPAN=\"2\" BGCOLOR=\"darkgoldenrod4\" > Bloque_Indirecto_"+std::to_string((Comienzo-Contador)/sizeof (BCA))+"</TD></TR>\n";



    for(int i=0;i<16;i++){
        int Valor=Apunta.b_pointers[i];

        Concatenar=Concatenar+"<TR>"+"<TD  BGCOLOR=\""+"darkgoldenrod1"+"\">"+"Puntero"+std::to_string(i)+"</TD><TD PORT=\"P"+std::to_string(i)+"\" BGCOLOR=\""+"gold"+"\">"+std::to_string(Apunta.b_pointers[i])+"</TD>  </TR> \n";
        if(Valor!=-1){

            Punteros=Punteros+RecorrerIndirectos(Nivel,NivelActual+1,Valor,PathReal,Tipo);
        }
    }
    Concatenar=Concatenar+"</TABLE>>] \n";
    Concatenar=Concatenar+Punteros;

    return Concatenar;
}




Reports::Reports()
{

}

std::string Reports::InodoAString(INO Inodo, int Comienzo,int Nombre){
    std::string Concatenar="";

    Concatenar=Concatenar+"I"+std::to_string(Comienzo)+" [ label=< <TABLE BGCOLOR=\"white\">";
    Concatenar=Concatenar+"<TR><TD COLSPAN=\"2\" BGCOLOR=\"darkturquoise\" > Inodo_"+std::to_string(Nombre)+"</TD></TR>\n";
    Concatenar=Concatenar+NuevaFila("darkslategray1","deepskyblue4","i_uid",std::to_string(Inodo.i_uid))+"\n";
    Concatenar=Concatenar+NuevaFila("darkslategray1","deepskyblue4","i_gid",std::to_string(Inodo.i_gid))+"\n";
    Concatenar=Concatenar+NuevaFila("darkslategray1","deepskyblue4","i_size",std::to_string(Inodo.i_size))+"\n";
    Concatenar=Concatenar+NuevaFila("darkslategray1","deepskyblue4","i_atime",Fun->FechaString(&Inodo.i_atime))+"\n";
    Concatenar=Concatenar+NuevaFila("darkslategray1","deepskyblue4","i_ctime",Fun->FechaString(&Inodo.i_ctime))+"\n";
    Concatenar=Concatenar+NuevaFila("darkslategray1","deepskyblue4","i_mtime",Fun->FechaString(&Inodo.i_mtime))+"\n";
    for(int i=0;i<15;i++){
        Concatenar=Concatenar+"<TR>"+"<TD  BGCOLOR=\""+"darkslategray1"+"\">"+"i_block"+std::to_string(i)+"</TD><TD PORT=\"P"+std::to_string(i)+"\" BGCOLOR=\""+"deepskyblue4"+"\">"+std::to_string(Inodo.i_block[i])+"</TD>  </TR> \n";
    }
    std::string Type="";
    Type+=Inodo.i_type;
    Concatenar=Concatenar+NuevaFila("darkslategray1","deepskyblue4","i_type",Type)+"\n";
    Concatenar=Concatenar+NuevaFila("darkslategray1","deepskyblue4","i_perm",std::to_string(Inodo.i_perm))+"\n";





    Concatenar=Concatenar+"</TABLE>>] \n";

    return Concatenar;
}
//SuperBloque
void Reports::ReporteSB(int Inicio, const char *Disco, const char *Path){


    FILE *f;
    f=fopen(Disco,"r+");
    SPB Leer;
    fseek(f,Inicio,SEEK_SET);
    fread(&Leer,sizeof(Leer),1,f);
    fclose(f);



    std::string Graphviz="";


    std::queue <int> NuevaCola;
    Cola=NuevaCola;
    std::queue <int> NuevaColaI;
    ColaI=NuevaColaI;
    Contador=Leer.s_first_blo;
    RecorrerInodos(Leer.s_first_ino,Disco)+"\n";


    Leer.s_free_blocks_count=Leer.s_blocks_count-Cola.size();
    Leer.s_free_inodes_count=Leer.s_inodes_count-ColaI.size();

    f=fopen(Disco,"r+");
    fseek(f,Inicio,SEEK_SET);
    fwrite(&Leer,sizeof(Leer),1,f);
    fclose(f);




    std::string Concatenar="digraph G { \n rankdir=LR node \n [shape=plaintext] \n";

    Concatenar=Concatenar+"SB"+std::to_string(0)+" [ label=< <TABLE BGCOLOR=\"white\">";
    Concatenar=Concatenar+"<TR><TD COLSPAN=\"2\" BGCOLOR=\"darkturquoise\" > Super Bloque"+"</TD></TR>\n";
    Concatenar=Concatenar+NuevaFila("darkslategray1","deepskyblue4","s_inodes_count",std::to_string(Leer.s_inodes_count))+"\n";
    Concatenar=Concatenar+NuevaFila("darkslategray1","deepskyblue4","s_blocks_count",std::to_string(Leer.s_blocks_count))+"\n";
    Concatenar=Concatenar+NuevaFila("darkslategray1","deepskyblue4","s_free_blocks_count",std::to_string(Leer.s_free_blocks_count))+"\n";
    Concatenar=Concatenar+NuevaFila("darkslategray1","deepskyblue4","s_free_inodes_count",std::to_string(Leer.s_free_inodes_count))+"\n";
    Concatenar=Concatenar+NuevaFila("darkslategray1","deepskyblue4","s_mtime",(Fun->FechaString(&Leer.s_mtime)))+"\n";
    Concatenar=Concatenar+NuevaFila("darkslategray1","deepskyblue4","s_umtime",(Fun->FechaString(&Leer.s_umtime)))+"\n";
    Concatenar=Concatenar+NuevaFila("darkslategray1","deepskyblue4","s_mnt_count",std::to_string(Leer.s_mnt_count))+"\n";
    Concatenar=Concatenar+NuevaFila("darkslategray1","deepskyblue4","s_magic","0xEF53")+"\n";

    Concatenar=Concatenar+NuevaFila("darkslategray1","deepskyblue4","s_inode_size",std::to_string(Leer.s_inode_size))+"\n";
    Concatenar=Concatenar+NuevaFila("darkslategray1","deepskyblue4","s_block_size",std::to_string(Leer.s_block_size))+"\n";
    Concatenar=Concatenar+NuevaFila("darkslategray1","deepskyblue4","s_first_ino",std::to_string(Leer.s_first_ino))+"\n";
    Concatenar=Concatenar+NuevaFila("darkslategray1","deepskyblue4","s_first_blo",std::to_string(Leer.s_first_blo))+"\n";
    Concatenar=Concatenar+NuevaFila("darkslategray1","deepskyblue4","s_bm_inode_start",std::to_string(Leer.s_bm_inode_start))+"\n";
    Concatenar=Concatenar+NuevaFila("darkslategray1","deepskyblue4","s_bm_block_start",std::to_string(Leer.s_bm_block_start))+"\n";
    Concatenar=Concatenar+NuevaFila("darkslategray1","deepskyblue4","s_inode_start",std::to_string(Leer.s_inode_start))+"\n";
    Concatenar=Concatenar+NuevaFila("darkslategray1","deepskyblue4","s_block_start",std::to_string(Leer.s_block_start))+"\n";





    Concatenar=Concatenar+"</TABLE>>] \n}\n";





    char Cop[1+Concatenar.length()];
    strcpy(Cop,Concatenar.c_str());
    std::string Pth=Path;
    Pth=Pth+".dot";
    f=fopen(Pth.data(),"w");
    if (!f){
        return ;
    }else{
        fwrite(&Cop,sizeof(Cop),1,f);
        fclose(f);

        std::string CMD="dot -Tpng "+Pth+" -o ";
        CMD = CMD+Path+".png";
        std::cout<<CMD<<std::endl;
        const char *command = CMD.data();
        system(command);
    }
}
//Inode
void Reports::ReporteInode(int Inicio, const char *Disco, const char *Path){


    FILE *f;
    f=fopen(Disco,"r+");
    SPB Leer;
    //Leer Super Bloque De La Particion
    fseek(f,Inicio,SEEK_SET);
    fread(&Leer,sizeof(Leer),1,f);
    //Tamaño Y Ubicacion
    int Ubi=Leer.s_bm_inode_start;
    int Tamanio=Leer.s_inodes_count;

    char Lectura;
    INO InoReporte;
    int InodoPtr=Leer.s_first_ino;

    std::string Salida="digraph G { \n rankdir=LR node \n [shape=plaintext] \n";
    int Anterior=-1;
    for(int i=0;i<Tamanio;i++){
        //Ubicarse En el BM
        fseek(f,Ubi+i,SEEK_SET);
        fread(&Lectura,sizeof(Lectura),1,f);
        if(Lectura=='1'){
            //Localizarse En Los Inodos
            int Pos=InodoPtr+i*sizeof (INO);
            fseek(f,Pos,SEEK_SET);
            fread(&InoReporte,sizeof(InoReporte),1,f);
            Salida=Salida+this->InodoAString(InoReporte,Pos,i);
            if(Anterior!=-1)
                Salida=Salida+"I"+std::to_string(Anterior)+"->"+"I"+std::to_string(Pos)+"[dir=both arrowtail = diamond]\n";
            Anterior=Pos;
        }

    }
    fclose(f);
    Salida=Salida+"\n }";
    char Cop[1+Salida.length()];
    strcpy(Cop,Salida.c_str());
    std::string Pth=Path;
    Pth=Pth+".dot";
    f=fopen(Pth.data(),"w");
    if (!f){
        return ;
    }else{
        fwrite(&Cop,sizeof(Cop),1,f);
        fclose(f);

        std::string CMD="dot -Tpng "+Pth+" -o ";
        CMD = CMD+Path+".png";
        std::cout<<CMD<<std::endl;
        const char *command = CMD.data();
        system(command);
    }

}
//Block
void Reports::ReporteBlock(int Inicio, const char *Disco, const char *Path){


    FILE *f;
    f=fopen(Disco,"r+");
    SPB Leer;
    //Leer Super Bloque De La Particion
    fseek(f,Inicio,SEEK_SET);
    fread(&Leer,sizeof(Leer),1,f);
    fclose(f);
    int ComienzoInodo=Leer.s_first_ino;
    std::string Graphviz="";


    std::queue <int> NuevaCola;
    Cola=NuevaCola;
    Contador=Leer.s_first_blo;

    Graphviz=Graphviz+"digraph G { \n rankdir=LR node \n [shape=plaintext] \n";
    Graphviz=Graphviz+ RecorrerInodos(ComienzoInodo,Disco)+"\n";






    int Tamanio=Cola.size();
    int Anterior=-1;
    for(int i=0;i<Tamanio;i++){
        if(Anterior!=-1)
        Graphviz=Graphviz+"B"+std::to_string(Anterior)+"->"+"B"+std::to_string(Cola.front())+"[dir=both arrowtail = diamond]\n";

        Anterior=Cola.front();
        Cola.pop();
    }

    Graphviz=Graphviz+"} \n";
    std::string Pth=Path;
    Pth=Pth+".dot";
    f=fopen(Pth.data(),"w");
    if (!f){
        return ;
    }else{

        fwrite(Graphviz.data(),Graphviz.length(),1,f);
        fclose(f);

        std::string CMD="dot -Tpng "+Pth+" -o ";
        CMD = CMD+Path+".png";
        std::cout<<CMD<<std::endl;
        const char *command = CMD.data();
        system(command);
    }
}

//Partes Del Tree
std::string Reports::GraficarInodos(int Comienzo, const char *PathReal){


    FILE *f;
    f=fopen(PathReal,"r+");
    INO Inodo;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Inodo,sizeof(Inodo),1,f);
    fclose(f);
    std::string Concatenar="";
    Concatenar=Concatenar+InodoAString(Inodo,Comienzo,Comienzo);


    int Tipo;
    if(Inodo.i_type=='1')
        Tipo=1;
    else
        Tipo=0;


    for(int i=0;i<12;i++){
        int Comprobar=Inodo.i_block[i];

        if(Comprobar!=-1){

            Concatenar =Concatenar+GraficarIndirectos(0,0,Comprobar,PathReal,Tipo);
        }

    }
    for(int i=0;i<3;i++){
        int Comprobar=Inodo.i_block[12+i];
        if(Comprobar!=-1){
            Concatenar=Concatenar+GraficarIndirectos(1+i,0,Comprobar,PathReal,Tipo);

        }
    }

    for(int i=0;i<15;i++){
            if(Inodo.i_block[i]!=-1)
                Concatenar=Concatenar+"I"+std::to_string(Comienzo)+":P"+std::to_string(i)+"->B"+std::to_string(Inodo.i_block[i])+"[dir=both arrowtail = diamond]\n";
    }
    return Concatenar;
}
std::string Reports::GraficarDirectos(int Comienzo,const char *PathReal,int Tipo){
    FILE *f;
    f=fopen(PathReal,"r+");
    BCA Carpeta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Carpeta,sizeof(Carpeta),1,f);
    fclose(f);

    std::string Concatenar="";
    Concatenar=Concatenar+"B"+std::to_string(Comienzo)+" [ label=< <TABLE BGCOLOR=\"white\">";
    Concatenar=Concatenar+"<TR><TD COLSPAN=\"2\" BGCOLOR=\"chartreuse4\" > Bloque_"+std::to_string(Comienzo)+"</TD></TR>\n";
    std::string Punteros="";
    for(int i=0;i<4;i++){
        CON Conte=Carpeta.content[i];
        std::string Prueba=Conte.b_name;
        Prueba=Prueba.substr(0,12);

        /*if(Comienzo==37120136)
        {
            std::cout<<Prueba<<std::endl;

        }
        for(int x=0;x<12;x++){
            if(Prueba[x]>127)
                Prueba[x]='*';
        }*/
        Concatenar=Concatenar+NuevaFila("darkseagreen3","darkolivegreen1","b_name",Prueba)+"\n";
        Concatenar=Concatenar+"<TR>"+"<TD  BGCOLOR=\""+"darkseagreen3"+"\">"+"b_inodo"+std::to_string(i)+"</TD><TD PORT=\"P"+std::to_string(i)+"\" BGCOLOR=\""+"darkolivegreen1"+"\">"+std::to_string(Conte.b_inodo)+"</TD>  </TR> \n";
        if(Conte.b_inodo!=-1){
            if(Tipo==0)
                Punteros=Punteros+"B"+std::to_string(Comienzo)+":P"+std::to_string(i)+"->I"+std::to_string(Conte.b_inodo)+" [dir=both arrowtail = diamond] \n";
            else
                Punteros=Punteros+"B"+std::to_string(Comienzo)+":P"+std::to_string(i)+"->B"+std::to_string(Conte.b_inodo)+" [dir=both arrowtail = diamond] \n";
        }
    }
    Concatenar=Concatenar+"</TABLE>>] \n";
    Concatenar=Concatenar+Punteros;
    for(int i=0;i<4;i++){
        CON Contenido=Carpeta.content[i];
        if(Contenido.b_inodo!=-1){

            if(Tipo==0){
                Concatenar=Concatenar+GraficarInodos(Contenido.b_inodo,PathReal);
            }else{
                Concatenar=Concatenar+GraficarBloqueContenido(Contenido.b_inodo,PathReal);
            }
        }
    }

    return Concatenar;
}
std::string Reports::GraficarBloqueContenido(int Comienzo, const char *PathReal){
    FILE *f;
    f=fopen(PathReal,"r+");
    BAR Dato;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Dato,sizeof(Dato),1,f);
    fclose(f);
    std::string Concatenar="";
    Concatenar=Concatenar+"B"+std::to_string(Comienzo)+" [ label=< <TABLE BGCOLOR=\"white\">";
    Concatenar=Concatenar+"<TR><TD COLSPAN=\"2\" BGCOLOR=\"deeppink3\" > Bloque_"+std::to_string(Comienzo)+"</TD></TR>\n";


    std::string Prueba=Dato.b_content;
    Prueba=Prueba.substr(0,64);
    Concatenar=Concatenar+NuevaFila("deeppink","floralwhite","Contenido",Prueba)+"\n";
    Concatenar=Concatenar+"</TABLE>>] \n";


    return Concatenar;
}
std::string Reports::GraficarIndirectos(int Nivel, int NivelActual, int Comienzo,  const char *PathReal,int Tipo){
    if(Nivel==NivelActual){

        return GraficarDirectos(Comienzo,PathReal,Tipo);
    }
    FILE *f;
    f=fopen(PathReal,"r+");
    BAP Apunta;
    fseek(f,Comienzo,SEEK_SET);
    fread(&Apunta,sizeof(Apunta),1,f);
    fclose(f);
    std::string Concatenar="";
    std::string Punteros="";
    //Graficando El Inodo
    Concatenar=Concatenar+"B"+std::to_string(Comienzo)+" [ label=< <TABLE BGCOLOR=\"white\">";
    Concatenar=Concatenar+"<TR><TD COLSPAN=\"2\" BGCOLOR=\"darkgoldenrod4\" > Bloque_Indirecto_"+std::to_string(Comienzo)+"</TD></TR>\n";

    for(int i=0;i<16;i++){
        int Valor=Apunta.b_pointers[i];

        Concatenar=Concatenar+"<TR>"+"<TD  BGCOLOR=\""+"darkgoldenrod1"+"\">"+"Puntero"+std::to_string(i)+"</TD><TD PORT=\"P"+std::to_string(i)+"\" BGCOLOR=\""+"gold"+"\">"+std::to_string(Apunta.b_pointers[i])+"</TD>  </TR> \n";
        if(Valor!=-1){
            Punteros=Punteros+"B"+std::to_string(Comienzo)+":P"+std::to_string(i)+"->B"+std::to_string(Valor)+" [dir=both arrowtail = diamond] \n";
            //Graficando Punteros
            Punteros=Punteros+GraficarIndirectos(Nivel,NivelActual+1,Valor,PathReal,Tipo);
        }
    }
    Concatenar=Concatenar+"</TABLE>>] \n";
    Concatenar=Concatenar+Punteros;

    return Concatenar;
}

//Tree
void Reports::ReporteArbol(int Inicio, const char *Disco, const char *Path){
    FILE *f;
    f=fopen(Disco,"r+");
    SPB Leer;
    //Leer Super Bloque De La Particion
    fseek(f,Inicio,SEEK_SET);
    fread(&Leer,sizeof(Leer),1,f);
    fclose(f);
    int ComienzoInodo=Leer.s_first_ino;
    std::string Graphviz="";

    Graphviz=Graphviz+"digraph G { \n rankdir=LR node \n [shape=plaintext] \n";
    Graphviz=Graphviz+ GraficarInodos(ComienzoInodo,Disco)+"\n";
    Graphviz=Graphviz+"} \n";


    std::string Pth=Path;
    Pth=Pth+".dot";
    f=fopen(Pth.data(),"w");
    if (!f){
        return ;
    }else{
    //Leer Super Bloque De La Particion

    fwrite(Graphviz.data(),Graphviz.length(),1,f);
    fclose(f);

    std::string CMD="dot -Tpng "+Pth+" -o ";
    CMD = CMD+Path+".png";
    std::cout<<CMD<<std::endl;
    const char *command = CMD.data();
    system(command);
    }
}

std::string Reports::NuevaFila(std::string Color1, std::string Color2, std::string Contenido1, std::string Contenido2){
    std::string Salida="";
    Salida=Salida+"<TR>"+"<TD BGCOLOR=\""+Color1+"\">"+Contenido1+"</TD><TD BGCOLOR=\""+Color2+"\">"+Contenido2+"</TD>  </TR>";
    return Salida;
}
void Reports::Reportebm_Inodo(int Inicio, const char *Disco, const char *Path){
    FILE *f;
    f=fopen(Disco,"r+");
    SPB Leer;
    //Leer Super Bloque De La Particion
    fseek(f,Inicio,SEEK_SET);
    fread(&Leer,sizeof(Leer),1,f);
    //Tamaño Y Ubicacion
    int Ubi=Leer.s_bm_inode_start;
    int Tamanio=Leer.s_inodes_count;
    //Ubicarse En el BM
    fseek(f,Ubi,SEEK_SET);
    char Lectura;
    std::string Salida="";
    int Contador=1;
    for(int i=0;i<Tamanio;i++){
        Contador++;
        fread(&Lectura,sizeof(Lectura),1,f);
        Salida=Salida+Lectura;
        if(Contador>20){
            Salida=Salida+'\n';
            Contador=1;
        }
    }
    std::string Pth=Path;
    Pth=Pth+".txt";
    fclose(f);
    char Cop[1+Salida.length()];
    strcpy(Cop,Salida.c_str());
    f=fopen(Pth.data(),"w");
    if (!f){
        return ;
    }else{
        fwrite(&Cop,sizeof(Cop),1,f);
        fclose(f);
    }

}
void Reports::Reportebm_Bloque(int Inicio, const char *Disco, const char *Path){

    FILE *f;
    f=fopen(Disco,"r+");
    SPB Leer;
    //Leer Super Bloque De La Particion
    fseek(f,Inicio,SEEK_SET);
    fread(&Leer,sizeof(Leer),1,f);
    //Tamaño Y Ubicacion
    int Ubi=Leer.s_bm_block_start;
    int Tamanio=Leer.s_blocks_count;
    //Ubicarse En el BM
    fseek(f,Ubi,SEEK_SET);
    char Lectura;
    std::string Salida="";
    int Contador=1;
    for(int i=0;i<Tamanio;i++){
        Contador++;
        fread(&Lectura,sizeof(Lectura),1,f);
        Salida=Salida+Lectura;
        if(Contador>20){
            Salida=Salida+'\n';
            Contador=1;
        }
    }
    fclose(f);
    char Cop[1+Salida.length()];
    strcpy(Cop,Salida.c_str());
    std::string Pth=Path;
    Pth=Pth+".txt";
    f=fopen(Pth.data(),"w");
    if (!f){
        return ;
    }else{
        fwrite(&Cop,sizeof(Cop),1,f);
        fclose(f);
    }

}
std::string Reports::TablaPAR(PAR Parti,int Num){
    std::string  Reporte="";
    Reporte = Reporte+"\n <TR>  <TD> "+"par_status_"+std::to_string(Num)+" </TD><TD> "+Parti.part_status+"</TD> </TR> \n";
    Reporte = Reporte+"\n <TR>  <TD> "+"par_type_"+std::to_string(Num)+" </TD><TD> "+Parti.part_type+"</TD> </TR> \n";
    Reporte = Reporte+"\n <TR>  <TD> "+"par_fit_"+std::to_string(Num)+" </TD><TD> "+Parti.part_fit[0]+Parti.part_fit[1]+"</TD> </TR> \n";
    Reporte = Reporte+"\n <TR>  <TD> "+"par_start_"+std::to_string(Num)+" </TD><TD> "+std::to_string(Parti.part_start)+"</TD> </TR> \n";
    Reporte = Reporte+"\n <TR>  <TD> "+"par_size_"+std::to_string(Num)+" </TD><TD> "+std::to_string(Parti.part_size)+"</TD> </TR> \n";
    Reporte = Reporte+"\n <TR>  <TD> "+"par_name_"+std::to_string(Num)+" </TD><TD> "+Parti.part_name+"</TD> </TR> \n";
    return Reporte;
}
void Reports::ReporteTablaMBR(const char *Path,const char *Guardar,int Num){
    FILE *f;
    MBR Main;
    f=fopen(Path,"r+");
    if (!f){
        return;
    }
    fread(&Main,sizeof(MBR),1,f);
    fclose(f);

    int ExtendIndex=Fun->HasExtended(Path);
    std::string ReportEBR="";
    if(ExtendIndex!=0 && ExtendIndex !=-1){

        PAR Extend=Main.mbr_partition[ExtendIndex-1];

        std::queue <RDI> Cola= this->LlenarLogicas(Path,Extend.part_start,Extend.part_start+Extend.part_size);


        f=fopen(Path,"r+");
        if (!f){
            return;
        }
        EBR Sub;

        int Cont=0;
        while(!Cola.empty()){
            Cont++;
            RDI NewAva=Cola.front();
            if(NewAva.Size>0){
                switch (NewAva.Type) {
                case 3:{
                    fseek(f,NewAva.Begin,SEEK_SET);
                    fread(&Sub,sizeof(EBR),1,f);
                    ReportEBR=ReportEBR+TablaEBR(Sub,Cont);
                }

                }
            }
            Cola.pop();
        }
        fclose(f);

    }

    std::string Reporte="";
    Reporte =Reporte+"digraph Gr { \n graph [ratio=fill]; \n graph [bb=\"0,0,352,154\"];"+ "node [label=\"\\N\", fontsize=15, shape=plaintext]; ";
    Reporte =Reporte+"labelloc=\"t\"  \n label="+"MBR_"+";";
    Reporte =Reporte+"Conte [label=< <TABLE BORDER=\"1\" ALIGN=\"center\" COLOR=\"#03fc20\">";
    Reporte = Reporte+"\n <TR>  <TD> Nombre </TD><TD> Valor </TD> </TR> \n";
    //Contenido MBR
    Reporte = Reporte+"\n <TR>  <TD> mbr_tamaño </TD><TD>"+ std::to_string(Main.mbr_tamano) +"</TD> </TR> \n";
    Reporte = Reporte+"\n <TR>  <TD> mbr_fecha_creacion </TD><TD>" + Fun->FechaString(&Main.mbr_fecha_creacion) + "</TD> </TR> \n";
    Reporte = Reporte+"\n <TR>  <TD> mbr_disk_signature </TD><TD> " + std::to_string(Main.mbr_disk_signature) + " </TD> </TR> \n";
    Reporte = Reporte+"\n <TR>  <TD> Disk_fit </TD><TD> " + Main.disk_fit[0] +Main.disk_fit[1]+ " </TD> </TR> \n";
    for (int i=0;i<4;i++) {
        PAR Parti =Main.mbr_partition[i];
        if(Parti.part_status=='t'){
            Reporte = Reporte+this->TablaPAR(Parti,i+1);
        }
    }

    Reporte = Reporte+"\n </TABLE> \n >];"+ ReportEBR+"\n}";

    char Cop[1+Reporte.size()];
    strcpy(Cop,Reporte.c_str());
    f=fopen("G.dot","w");
    if (!f){
        return ;
    }else{
        fwrite(&Cop,sizeof(Cop),1,f);
        fclose(f);
    }
    std::string CMD="dot -Tpng G.dot -o ";
    CMD = CMD+Guardar;
    const char *command = CMD.data();
    system(command);

}


std::string Reports::TablaEBR(EBR Extendida,int Num){
    std::string  Reporte="\n \n";
    Reporte =Reporte+"Conte"+std::to_string(Num)+"[label=< <TABLE BORDER=\"1\" ALIGN=\"center\" COLOR=\"#03fc20\">";
    Reporte = Reporte+"\n <TR>  <TD> Nombre </TD><TD> Valor </TD> </TR> \n";
    //Contenido MBR

    std::string Exte=Extendida.part_fit;
    if(Exte.length()>2){
        Exte=Exte.substr(0,2);
    }


    Reporte = Reporte+"\n <TR>  <TD> "+"par_status_"+std::to_string(Num)+" </TD><TD> "+Extendida.part_status+"</TD> </TR> \n";
    Reporte = Reporte+"\n <TR>  <TD> "+"par_fit_"+std::to_string(Num)+" </TD><TD> "+Exte+"</TD> </TR> \n";
    Reporte = Reporte+"\n <TR>  <TD> "+"par_start_"+std::to_string(Num)+" </TD><TD> "+std::to_string(Extendida.part_start)+"</TD> </TR> \n";
    Reporte = Reporte+"\n <TR>  <TD> "+"par_size_"+std::to_string(Num)+" </TD><TD> "+std::to_string(Extendida.part_size)+"</TD> </TR> \n";
    Reporte = Reporte+"\n <TR>  <TD> "+"par_next_"+std::to_string(Num)+" </TD><TD> "+std::to_string(Extendida.part_next)+"</TD> </TR> \n";
    Reporte = Reporte+"\n <TR>  <TD> "+"par_name_"+std::to_string(Num)+" </TD><TD> "+Extendida.part_name+"</TD> </TR> \n";
    Reporte = Reporte+"\n </TABLE> \n >]; \n";
    return Reporte;
}
void Reports::ReporteTablaEBR(EBR Extendida, const char *Guardar,int Num){
    FILE *f;


    std::string Reporte="";
    Reporte =Reporte+"digraph Gr { \n graph [ratio=fill]; \n graph [bb=\"0,0,352,154\"];"+ "node [label=\"\\N\", fontsize=15, shape=plaintext]; ";
    Reporte =Reporte+"labelloc=\"t\"  \n label="+"EBR_"+Extendida.part_name+";";
    Reporte =Reporte+"Conte [label=< <TABLE BORDER=\"1\" ALIGN=\"center\" COLOR=\"#03fc20\">";
    Reporte = Reporte+"\n <TR>  <TD> Nombre </TD><TD> Valor </TD> </TR> \n";
    //Contenido MBR

    Reporte = Reporte+this->TablaEBR(Extendida,Num);

    Reporte = Reporte+"\n </TABLE> \n >]; \n}";
    char Cop[1+Reporte.size()];
    strcpy(Cop,Reporte.c_str());
    f=fopen("G.dot","w");
    if (!f){
        return ;
    }else{
        fwrite(&Cop,sizeof(Cop),1,f);
        fclose(f);
    }

    std::string CMD="dot -Tpng G.dot -o ";
    CMD = CMD+Guardar;
    const char *command = CMD.data();
    system(command);
}
std::string Reports::GraphE(RDI Dita,const char *Path,std::queue <RDI> Que){
    std::string Retu="";
    Retu="\n <TD> <TABLE BORDER=\"1\" > ";
    Retu=Retu+" <TR  ><TD  BORDER=\"1\" > Extendida: "+Dita.Info+ " </TD></TR>";
    // std::string Num=std::to_string((Dita.Size)/Fun->FileSize(Path)*100);
    Retu=Retu+" <TR  ><TD   > <TABLE BORDER=\"0\" > <TR > "+GraphL(Path,Que)+ " </TR> </TABLE> </TD></TR>";
    Retu=Retu+"</TABLE> </TD>";
    return Retu;
}
std::string Reports::GraphL(const char *Path, std::queue<RDI> Que){
    std::string Retu="";
    if(Que.empty()){
        FILE *f;
        MBR Main;
        f=fopen(Path,"r+");
        if (!f){
            return "<TD></TD>";
        }
        fread(&Main,sizeof(MBR),1,f);
        fclose(f);
        int Index=Fun->HasExtended(Path)-1;
        PAR Ext=Main.mbr_partition[Index];
        std::string Salida="<TD> Espacio Libre";
        std::ostringstream Str;
        Str << std::fixed;
        Str << std::setprecision(2);
        double Calc=double((int((Ext.part_size))))*100/double(Fun->FileSize(Path));
        Str << Calc;
        std::string Num = Str.str();
        Salida = Salida+Num+"</TD>";
        return Salida;

    }
    while(!Que.empty()){

        RDI NewAva=Que.front();
        if(NewAva.Size>0){
            switch (NewAva.Type) {
            case 3:{
                Retu=Retu+"\n <TD> <TABLE BORDER=\"1\" > ";
                Retu=Retu+" <TR  ><TD  BORDER=\"1\" > EBR "+ " </TD></TR>";
                Retu=Retu+" <TR  ><TD   >  "+NewAva.Info+" </TD></TR>";
                Retu=Retu+"</TABLE> </TD>";


                Retu=Retu+"\n <TD> <TABLE BORDER=\"1\" > ";
                Retu=Retu+" <TR  ><TD  BORDER=\"1\" > Logica: "+NewAva.Info+ " </TD></TR>";
                std::ostringstream Str;
                Str << std::fixed;
                Str << std::setprecision(2);
                double Calc=double((int((NewAva.Size))))*100/double(Fun->FileSize(Path));
                Str << Calc;
                std::string Num = Str.str();
                Retu=Retu+" <TR  ><TD   >  "+Num+ " </TD></TR>";
                Retu=Retu+"</TABLE> </TD>";
                break;
            }
            case 4:{
                Retu=Retu+"\n <TD> <TABLE BORDER=\"1\" > ";
                Retu=Retu+" <TR  ><TD  BORDER=\"1\" > Espacio Libre: "+" </TD></TR>";
                std::ostringstream Str;
                Str << std::fixed;
                Str << std::setprecision(2);
                double Calc=double((int((NewAva.Size))))*100/double(Fun->FileSize(Path));
                Str << Calc;
                std::string Num = Str.str();
                Retu=Retu+" <TR  ><TD   >  "+Num+ " </TD></TR>";
                Retu=Retu+"</TABLE> </TD>";
                break;
            }
            }
        }
        Que.pop();
    }
    return Retu;
}
std::string Reports::GraphP(RDI Dita,const char *Path){
    std::string Retu="";
    Retu="\n <TD> <TABLE BORDER=\"1\" > ";
    Retu=Retu+" <TR  ><TD   BORDER=\"1\"> Primaria: "+Dita.Info+ " </TD></TR>";
    std::ostringstream Str;
    Str << std::fixed;
    Str << std::setprecision(2);
    double Calc=double((int((Dita.Size))))*100/double(Fun->FileSize(Path));
    Str << Calc;
    std::string Num = Str.str();
    Retu=Retu+" <TR  ><TD   >  "+Num+ " </TD></TR>";
    Retu=Retu+"</TABLE> </TD>";
    return Retu;
}
std::string Reports::GraphEmpty(RDI Dita,const char *Path){
    std::string Retu="";
    Retu="\n <TD> <TABLE BORDER=\"1\" > ";
    Retu=Retu+" <TR  ><TD  BORDER=\"1\" >  "+"Espacio Libre"+ " </TD></TR>";
    std::ostringstream Str;
    Str << std::fixed;
    Str << std::setprecision(2);
    double Calc=double((int((Dita.Size))))*100/double(Fun->FileSize(Path));
    Str << Calc;
    std::string Num = Str.str();
    Retu=Retu+" <TR  ><TD   >  "+Num+ " </TD></TR>";
    Retu=Retu+"</TABLE> </TD>";
    return Retu;
}
void Reports::Graphviz(const char *Path,const char *Guardar){
    std::queue <RDI> Dita=this->PARTReport(Path);
    std::string M;
    M="\n labelloc=\"t\"";
    M=M+"\n label=\""+Path+"\";";
    std::string Graph="digraph Gr { \n  graph [ratio=fill];\n  graph [bb=\"0,0,352,154\"];\n node [label=\"\\N\", fontsize=15, shape=plaintext]; \n "+M+"Conte [label=< <TABLE BORDER=\"0\" ALIGN=\"center\" COLOR=\"#0CB7F2\"> \n <TR> \n";
    Graph=Graph+"\n <TD> <TABLE BORDER=\"1\" > ";
    Graph=Graph+" <TR  ><TD   BORDER=\"1\"> MBR "+ " </TD></TR>";


    std::ostringstream Str;
    Str << std::fixed;
    Str << std::setprecision(2);
    double Calc=double((int(sizeof (MBR))))*100/double(Fun->FileSize(Path));
    Str << Calc;
    std::string Num = Str.str();
    Graph=Graph+" <TR  ><TD   >  "+Num+ " </TD></TR>";
    Graph=Graph+"</TABLE> </TD>";

    while(!Dita.empty()){
        RDI NewAva=Dita.front();
        if(NewAva.Size>0){
            switch (NewAva.Type) {
            case 0:{
                Graph=Graph+this->GraphEmpty(NewAva,Path);
                break;
            }
            case 1:{
                Graph=Graph+this->GraphP(NewAva,Path);
                break;
            }
            case 2:{
                Graph=Graph+this->GraphE(NewAva,Path,this->LogicReport(Path,NewAva.Begin,NewAva.End));
                break;
            }
            }

            //std::cout<<NewAva.Begin<<"***"<<NewAva.Size<<"***"<<NewAva.Type<<"***"<<NewAva.Info<<std::endl;
        }
        Dita.pop();
    }
    Graph= Graph+"\n </TR> </TABLE> \n >]; \n}";
    char Cop[1+Graph.size()];
    strcpy(Cop,Graph.c_str());
    FILE *f;
    f=fopen("G.dot","w");
    if (!f){
        return ;
    }else{
        fwrite(&Cop,sizeof(Cop),1,f);
        fclose(f);
    }

    std::string CMD="dot -Tpng G.dot -o ";
    CMD = CMD+Guardar;
    const char *command = CMD.data();
    system(command);

    // std::cout<<Graph<<std::endl;
}
//Llena Cola De Primarias Y Extendidas
std::queue <RDI> Reports::PARTReport(const char *Path){
    std::string Out;
    FILE *f;
    f=fopen(Path,"r");
    std::queue <RDI> Dita;
    if (!f)
        return Dita;
    //fseek(f,Num,SEEK_SET);
    //Cola para los fit

    MBR Main;
    fseek(f,0,SEEK_SET);
    fread(&Main,sizeof(MBR),1,f);
    fclose(f);
    int Beg=int(sizeof (MBR));
    int End=Fun->FileSize(Path);

    for (int i=0;i<4;i++) {
        RDI NewAva;
        NewAva.Begin=Beg;
        NewAva.End=Main.mbr_partition[i].part_start;
        NewAva.Size=NewAva.End-NewAva.Begin;
        NewAva.Type=0;
        NewAva.Info="";
        Dita.push(NewAva);
        if(NewAva.End!=0)
            Beg=NewAva.End+Main.mbr_partition[i].part_size;
        {
            RDI NewAva;
            NewAva.Begin=Main.mbr_partition[i].part_start;
            NewAva.End=Main.mbr_partition[i].part_start+Main.mbr_partition[i].part_size;
            NewAva.Size=Main.mbr_partition[i].part_size;
            if(Main.mbr_partition[i].part_type!='e'){
                NewAva.Type=1;
            }else{
                NewAva.Type=2;
            }
            NewAva.Info=Main.mbr_partition[i].part_name;
            Dita.push(NewAva);
            /*
            if(NewAva.Type==2){
               this->FillQueue(&Dita,this->LogicReport(Path,NewAva.Begin,NewAva.End));
            }
            */
        }
    }
    RDI NewAva;

    NewAva.Begin=Beg;
    NewAva.End=End;
    NewAva.Size=NewAva.End-NewAva.Begin;
    NewAva.Type=0;
    NewAva.Info="";
    Dita.push(NewAva);
    /*while(!Dita.empty()){
        NewAva=Dita.front();
        if(NewAva.Size>0){

            if(NewAva.Type==2){
                this->LogicReport(Path,NewAva.Begin,NewAva.End);
            }
            std::cout<<NewAva.Begin<<"***"<<NewAva.Size<<"***"<<NewAva.Type<<std::endl;
        }
        Dita.pop();
    }*/
    return Dita;

}
//Vacia Una Cola EN Otra
void Reports::FillQueue(std::queue<RDI> *Q1, std::queue<RDI> Q2){
    std::queue <RDI> Retu;
    while(!Q2.empty()){
        RDI NewAva=Q2.front();
        if(NewAva.Size>0){
            Q1->push(NewAva);
        }
        Q2.pop();
    }
}
std::queue <RDI> Reports::LlenarLogicas(const char *Path, int Begin, int End){


    std::queue <RDI> Dita;
    FILE *f;
    EBR Cur;
    //Logic.part_next=0;
    int LogicIndex=Begin;
    f=fopen(Path,"r+");
    if (!f){
        return Dita;
    }
    RDI Nueva;
    while(LogicIndex!=-1){


        fseek(f,LogicIndex,SEEK_SET);
        fread(&Cur,sizeof(EBR),1,f);

        LogicIndex=Cur.part_next;


        if(Cur.part_status=='t'){
            Nueva.Begin=Cur.part_start;
            Nueva.End=Cur.part_start+Cur.part_size;
            Nueva.Size=Nueva.End-Nueva.Begin;
            Nueva.Info=Cur.part_name;
            Nueva.Type=3;
            Dita.push(Nueva);
            Begin=Cur.part_start+Cur.part_size;
        }
    }
    fclose(f);
    return Dita;
}
//Llena Cola De Logicas
std::queue <RDI> Reports::LogicReport(const char *Path, int Begin, int End){
    std::queue <RDI> Dita;
    FILE *f;
    EBR Cur;
    //Logic.part_next=0;
    int LogicIndex=Begin;
    f=fopen(Path,"r+");
    if (!f){
        return Dita;
    }

    //Cola para los fit
    //std::queue <EBR> Dita;

    RDI Nueva;
    while(LogicIndex!=-1){
        fseek(f,LogicIndex,SEEK_SET);
        fread(&Cur,sizeof(EBR),1,f);
        LogicIndex=Cur.part_next;

        Nueva.Begin=Begin;
        Nueva.End=Cur.part_start;
        Nueva.Size=Nueva.End-Nueva.Begin;
        Nueva.Info="Espacio Disponible";
        Nueva.Type=4;
        if(Nueva.Size>0){
            Dita.push(Nueva);
        }


        if(Cur.part_status=='t'){





            Nueva.Begin=Cur.part_start;
            Nueva.End=Cur.part_start+Cur.part_size;
            Nueva.Size=Nueva.End-Nueva.Begin;
            Nueva.Info=Cur.part_name;
            Nueva.Type=3;
            Dita.push(Nueva);



            Begin=Cur.part_start+Cur.part_size;
        }
    }
    Nueva.Begin=Begin;
    Nueva.End=End;
    Nueva.Size=Nueva.End-Nueva.Begin;
    Nueva.Info="Espacio Disponible";
    Nueva.Type=4;
    if(Nueva.Size>0){
        Dita.push(Nueva);
    }


    fclose(f);
    return Dita;

}
