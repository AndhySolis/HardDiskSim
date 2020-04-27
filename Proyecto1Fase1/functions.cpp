#include "functions.h"

#include "functionsext.h"
Functions::Functions()
{

}

void Functions::IniciarBloqueCarpeta(BCA *Bloque){
    for(int i=0;i<4;i++){
        Bloque->content[i].b_inodo=-1;
        for(int j=0;j<12;j++){
        Bloque->content[i].b_name[j]='*';
        }
    }
}
void Functions::IniciarInodo(INO *Inodo, int i_uid, int i_gid, int i_size, int PrimerBloque, char Tipo,int Perm){
    Inodo->i_uid=i_uid;
    Inodo->i_gid=i_gid;
    Inodo->i_size=i_size;
    Fecha(&Inodo->i_atime);
    Fecha(&Inodo->i_ctime);
    Fecha(&Inodo->i_mtime);
    Inodo->i_block[0]=PrimerBloque;
    for(int i=1;i<16;i++){
        Inodo->i_block[i]=-1;
    }
    Inodo->i_type=Tipo;
    Inodo->i_perm=2110110010;
}
void Functions::LlenarVacio(int Begin, int Size, char Character,const char *Path){
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

int Functions::CalcularCantidad(int Tamanio,int Tipo){

    int PesoEstructuras=0;
    //Tipo  0 EXT2  Tipo 1 EXT3
    PesoEstructuras=4+3*int(sizeof (BCA))+int(sizeof (INO))+(int(sizeof (JOR))*Tipo);
    Tamanio = Tamanio-int(sizeof (SPB));
    int Sal=Tamanio/PesoEstructuras;
    //std::cout<<"QQ "<<Tamanio <<"   "<<Tamanio%PesoEstructuras<<std::endl;
    return Sal;
}
SPB Functions::LlenarSuperBloque(int Tipo,int Comienzo,int Cantidad){
    SPB Nuevo;
    //TipoDeFormato
    Nuevo.s_filesystem_type=Tipo;
    //Cantidad Inodos
    Nuevo.s_inodes_count=Cantidad;
    //Cantidad Bloques
    Nuevo.s_blocks_count=Cantidad*3;
    //Cantidad Inodos Libre
    Nuevo.s_free_inodes_count=Cantidad;
    //Cantidad Bloques Libre
    Nuevo.s_free_blocks_count=Cantidad*3;
    //Fecha Montado
    Fecha(&Nuevo.s_mtime);
    //Fecha Desmontado
    Fecha(&Nuevo.s_umtime);
    //VecesMontado
    Nuevo.s_mnt_count=0;
    //NumeroMagico
    Nuevo.s_magic=0xEF53;
    //Tamaño Inodo
    Nuevo.s_inode_size=int(sizeof (INO));
    //Tamaño Bloque
    Nuevo.s_block_size=int(sizeof (BAP));
    //Primer Inodo Libre
    //Primer Bloque Libre
    //Inicio BMInodo
    Nuevo.s_bm_inode_start=Comienzo+int(sizeof (SPB))+Cantidad*int(sizeof (JOR))*Tipo;
    //Inicio BMBloque
    Nuevo.s_bm_block_start=Nuevo.s_bm_inode_start+Cantidad;
    //Inicio Inodo
    Nuevo.s_inode_start=Nuevo.s_bm_block_start+Cantidad*3;
    Nuevo.s_first_ino=Nuevo.s_inode_start;
    //Inicio Bloque
    Nuevo.s_block_start= Nuevo.s_inode_start+Cantidad*(int(sizeof (INO)));
    Nuevo.s_first_blo=Nuevo.s_block_start;
    return Nuevo;
}









void Functions::FillName(char *Arra, const char *Input){
    Arra[0]='C';
    for(int i=0;i<16;i++){
        Arra[i]=' ';
    }
    strcpy(Arra, Input);
}
void Functions::FillPAR(PAR *NPAR){
    NPAR->part_status='f';
    NPAR->part_type='p';
    NPAR->part_fit[0]='f';
    NPAR->part_fit[1]='f';
    NPAR->part_start=0;
    NPAR->part_size=0;
}
void Functions::FillDisk(int Begin, int Size, char Character,const char *Path){
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
std::string Functions::DecimalBinario(char Decimal){
    std::string Retorno="";
    switch (Decimal) {
    case '0':{
        Retorno="000";
        break;
    }
    case '1':{
        Retorno="001";
        break;
    }
    case '2':{
        Retorno="010";
        break;
    }
    case '3':{
        Retorno="011";
        break;
    }
    case '4':{
        Retorno="100";
        break;
    }
    case '5':{
        Retorno="101";
        break;
    }
    case '6':{
        Retorno="110";
        break;
    }
    case '7':{
        Retorno="111";
        break;
    }
    }
    return Retorno;
}
void Functions::EscribirRandom(int Num){
    Functions *F = new Functions();
    std::ifstream t("Dita.txt");
    std::stringstream buffer ;
    buffer << t.rdbuf();
    std::string s = buffer.str();
    std::string delimiter = ",";
    size_t pos = 0;
    std::string token;
    std::string Escritura="";
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        if(F->IF(Escritura,"")){
        Escritura=token;
        }
        else{
        Escritura=Escritura+","+token;
        }
        s.erase(0, pos + delimiter.length());
    }
    Escritura=Escritura+","+s+","+std::to_string(Num);


    std::ofstream myfile;
      myfile.open ("Dita.txt");
      myfile << Escritura;
      myfile.close();
    //std::cout<<Escritura<<std::endl;
}
bool Functions::Valido(int Num){
    std::ifstream t("Dita.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string s = buffer.str();
    std::string delimiter = ",";
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);

        if(atoi(token.data())==Num){
            return false;
        }

        s.erase(0, pos + delimiter.length());
    }

    if(atoi(s.data())==Num){
        return false;
    }

    return true;
}
int Functions::GenerarNumeroRandom(){

    if(this->ExisteArchivo("Dita.txt")==false){
        FILE *f;
        char D;
        f=fopen("Dita.txt","w");
        D='0';
        fwrite(&D,sizeof(D),1,f);
        D=',';
        fwrite(&D,sizeof(D),1,f);
        D='0';
        fwrite(&D,sizeof(D),1,f);
        fclose(f);
    }

    bool Salir=false;
    int R =0;
    while (Salir==false) {
        srand(time(0));

        R= (rand() % 1024*1024) + 1;
        Salir =Valido(R);
    }
    EscribirRandom(R);
    return R;
}
void Functions::Fecha(struct tm *Dita){
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    now->tm_mon=now->tm_mon+1;
    now->tm_year=now->tm_year + 1900;
    *Dita=*now;
}
std::string Functions::FechaString(struct tm *Dita){
    std::string Fecha="";
    Fecha=std::to_string(Dita->tm_mday)+"/"+std::to_string(Dita->tm_mon)+"/"+std::to_string(Dita->tm_year);
    std::string Hora="";
    Hora=std::to_string(Dita->tm_hour)+":"+std::to_string(Dita->tm_min)+"/"+std::to_string(Dita->tm_sec);
    return Fecha+"  "+Hora;
}
int Functions::LogicaFinal(PAR Extendida,const char *Path ){
    FILE *f;
    EBR Cur;
    //Logic.part_next=0;
    int LogicIndex=Extendida.part_start;
    f=fopen(Path,"r+");
    if (!f){
        return-1;
    }
    int Salida=Extendida.part_start+ int(sizeof (EBR));
    while(LogicIndex!=-1){
        fseek(f,LogicIndex,SEEK_SET);
        fread(&Cur,sizeof(EBR),1,f);
        LogicIndex=Cur.part_next;
    }
    if(Cur.part_status=='t'){
        Salida=Cur.part_start+Cur.part_size;
    }
    fclose(f);
    return Salida;
}
/*!
    \class QCache
    \brief Devuelve true si hay espacio contiguo
*/
bool Functions::DiskLimit(MBR Main, int Index,int Size,const char *Path){
    PAR Cur=Main.mbr_partition[Index];
    int Primera=-1;
    int Ultima=-1;
    int PosCercana=-1;

    for (int i=0;i<4;i++) {
        PAR Actual =Main.mbr_partition[i];
        if((Primera==-1|| Actual.part_start<Primera) && Actual.part_start!=0){
            Primera=Actual.part_start;
        }

        if(Ultima==-1|| Actual.part_start>Ultima){
            Ultima=Actual.part_start+Actual.part_size;
        }


        if(Cur.part_start<Actual.part_start){
            if(PosCercana==-1|| PosCercana>Actual.part_start){
                PosCercana=Actual.part_start;
            }
        }
    }
    if(PosCercana==-1){
        int Tope = this->FileSize(Path);
        if((Tope-(Cur.part_size+Cur.part_start))>=Size){
            return true;
        }
    }
    if((PosCercana-(Cur.part_size+Cur.part_start))>=Size){
        return true;
    }else{
        return false;
    }
}
/*!
    \class QCache
    \brief Devuelve true si hay espacio
*/
bool Functions::LogicLimit(int EBRLimit, int Ini, int Size, const char *Path){
    FILE *f;
    EBR Cur;
    f=fopen(Path,"r");
    if (!f)
        return false;
    fseek(f,Ini,SEEK_SET);
    fread(&Cur,sizeof(EBR),1,f);
    fclose(f);
    int Next =Cur.part_next;
    //Si no tiene siguiente
    if(Next==-1)
    {
        if(EBRLimit-(Cur.part_start+Cur.part_size)>=Size){
            return true;
        }else{
            return false;
        }
    }
    else{
        if(Next-(Cur.part_start+Cur.part_size)>=Size){
            return true;
        }else{
            return false;
        }
    }
}
/*!
    \class QCache
    \brief Devuelve Un Struct EBR Si No Lo Encuentra Devuelve el char '\0'
*/
EBR Functions::SearchEBR(const char *Name,const char *Path ){
    EBR Findi;
    Findi.part_status='\0';
    FILE *f;
    MBR Main;
    f=fopen(Path,"r");
    if (!f)
        return Findi;
    fseek(f,0,SEEK_SET);
    fread(&Main,sizeof(MBR),1,f);
    fclose(f);

    int Index =this->HasExtended(Path);
    if(Index==0 || Index==-1)
    {
        //this->Out("Este Disco No Tiene Particion extendida");
        return Findi;
    }
    PAR Extend=Main.mbr_partition[Index-1];
    int LogicIndex=Extend.part_start;

    f=fopen(Path,"r+");
    if (!f){
        return Findi;
    }

    while(LogicIndex!=-1){
        fseek(f,LogicIndex,SEEK_SET);
        fread(&Findi,sizeof(EBR),1,f);

        LogicIndex=Findi.part_next;
        if(IF(Name,Findi.part_name)){
            return Findi;
        }
    }
    if(IF(Name,Findi.part_name)){
        return Findi;
    }
    Findi.part_status='\0';
    return Findi;
}
/*!
    \class QCache
    \brief Devuelve Un Struct EBR Si No Lo Encuentra Devuelve el char '\0'
*/
int Functions::SearchPAR(const char *Name,const char *Path ){
    PAR FinPAR;
    FILE *f;
    MBR Main;
    f=fopen(Path,"r");
    if (!f)
        return -1;
    fseek(f,0,SEEK_SET);
    fread(&Main,sizeof(MBR),1,f);
    fclose(f);

    for(int i=0;i<4;i++){
        FinPAR=Main.mbr_partition[i];
        if(IF(Name,FinPAR.part_name)){
            return i;
        }
    }
    return -1;
}
/*!
    \class QCache
    \brief Devuelve true si es verdadero
*/
bool Functions::IF(const char *a, const char *b){
    std::string A = a;
    std::string B = b;

    if (A.size() != B.size()) {
            return false;
        }
        for (std::string::const_iterator c1 = A.begin(), c2 = B.begin(); c1 != A.end(); ++c1, ++c2) {
            if (tolower(*c1) != tolower(*c2)) {
                return false;
            }
        }
        return true;

}
/*!
    \class QCache
    \brief Devuelve true si es verdadero
*/
bool Functions::IFEspecial(std::string A , std::string B ){
    if (A.size() != B.size()) {
            return false;
        }
        for (std::string::const_iterator c1 = A.begin(), c2 = B.begin(); c1 != A.end(); ++c1, ++c2) {
            if ((*c1) != (*c2)) {
                return false;
            }
        }
        return true;

}
/*!
    \class QCache
    \brief Devuelve true si es verdadero
*/
bool Functions::IF(std::string A , std::string B ){
    if (A.size() != B.size()) {
            return false;
        }
        for (std::string::const_iterator c1 = A.begin(), c2 = B.begin(); c1 != A.end(); ++c1, ++c2) {
            if (tolower(*c1) != tolower(*c2)) {
                return false;
            }
        }
        return true;

}
/*!
    \class QCache
    \brief Devuelve Posicion Inicial Dependiendo El Tipo De Fit, Sin Espacio Retorna 1
*/
int Functions::LogicFit(char *Fit, int Size, const char *Path, int Begin, int End){
    Fit[0]=char(tolower(Fit[0]));
    Fit[1]=char(tolower(Fit[1]));


    if(strncmp (Fit,"bf",2) == 0){
      return  this->LogicalBestFit(Size,Path,Begin,End);
    }else if(strncmp (Fit,"ff",2) == 0){
      return   this->LogicalFirstFit(Size,Path,Begin,End);
    }else if(strncmp (Fit,"wf",2) == 0){
      return   this->LogicalWorstFit(Size,Path,Begin,End);
    }
    std::cout<<"ERROR EN LOS FIT"<<std::endl;
    return -1;


}
/*!
    \class QCache
    \brief Devuelve Posicion Inicial Dependiendo El Tipo De Fit, Sin Espacio Retorna 1
*/
int Functions::DiskFit( char Fit[2],int Size,const char *Path){
    Fit[0]=char(tolower(Fit[0]));
    Fit[1]=char(tolower(Fit[1]));
    if(strncmp (Fit,"bf",2) == 0){
      return  this->BestFit(Size,Path);
    }else if(strncmp (Fit,"ff",2) == 0){
      return   this->FirstFit(Size,Path);
    }else if(strncmp (Fit,"wf",2) == 0){
      return   this->WorstFit(Size,Path);
    }

    std::cout<<"ERROR EN LOS FIT"<<std::endl;
    return -1;
}
/*!
    \class QCache
    \brief Busca Si EL Disco Tiene Particion Extendida Un 0 Indica No Encontrado Un -1 Error En El Archivo.
*/
int Functions::HasExtended(const char *Path){
    FILE *f;
    MBR r;
    f=fopen(Path,"r");
    if (!f){
        return -1;
    }
    fread(&r,sizeof(MBR),1,f);
    fclose(f);
    if(r.mbr_partition[0].part_type=='e')
    {
        return 1;
    }
    else if(r.mbr_partition[1].part_type=='e')
        return 2;
    else if(r.mbr_partition[2].part_type=='e')
        return 3;
    else if(r.mbr_partition[3].part_type=='e')
        return 4;
    else {
        return 0;
    }

}
/*!
    \class QCache
    \brief Busca Si El Tamaño Disponible En El Disco Danto Path Y Tamaño Requerido Del Bloque .
*/
int Functions::BestFit(int Size, const char *Path){
    FILE *f;
    f=fopen(Path,"r");
    if (!f)
        return -1;
    //fseek(f,Num,SEEK_SET);
    //Cola para los fit
    //std::queue <AVA> Dita;
    MBR Main;
    fseek(f,0,SEEK_SET);
    fread(&Main,sizeof(MBR),1,f);
    fclose(f);
    int Beg=int(sizeof (MBR));
    int End=FileSize(Path);

    int Tamanio=-1;
    int Inicio=-1;
    for (int i=0;i<4;i++) {
        AVA NewAva;
        NewAva.Begin=Beg;
        NewAva.End=Main.mbr_partition[i].part_start;
        NewAva.Size=NewAva.End-NewAva.Begin;
        if(NewAva.Size>0){
            if(NewAva.Size>=Size){
                if(Tamanio==-1 || NewAva.Size<Tamanio){
                    Tamanio =NewAva.Size;
                    Inicio=NewAva.Begin;
                }
            }
        }
        //Dita.push(NewAva);
        if(NewAva.End!=0)
            Beg=NewAva.End+Main.mbr_partition[i].part_size;
    }
    AVA NewAva;

    NewAva.Begin=Beg;
    NewAva.End=End;
    NewAva.Size=NewAva.End-NewAva.Begin;
    if(NewAva.Size>0){
        if(NewAva.Size>=Size){
            if(Tamanio==-1 || NewAva.Size<Tamanio){
                Tamanio =NewAva.Size;
                Inicio=NewAva.Begin;
            }
        }
    }
    return Inicio;
}
/*!
    \class QCache
    \brief Busca Si El Tamaño Disponible En El Disco Danto Path Y Tamaño Requerido Del Bloque .
*/
int Functions::WorstFit(int Size, const char *Path){
    FILE *f;
    f=fopen(Path,"r");
    if (!f)
        return -1;
    //fseek(f,Num,SEEK_SET);
    //Cola para los fit
    //std::queue <AVA> Dita;
    MBR Main;
    fseek(f,0,SEEK_SET);
    fread(&Main,sizeof(MBR),1,f);
    fclose(f);
    int Beg=int(sizeof (MBR));
    int End=FileSize(Path);

    int Tamanio=-1;
    int Inicio=-1;
    for (int i=0;i<4;i++) {
        AVA NewAva;
        NewAva.Begin=Beg;
        NewAva.End=Main.mbr_partition[i].part_start;
        NewAva.Size=NewAva.End-NewAva.Begin;
        if(NewAva.Size>0){
            if(NewAva.Size>=Size){
                if(Tamanio==-1 || NewAva.Size>Tamanio){
                    Tamanio =NewAva.Size;
                    Inicio=NewAva.Begin;
                }
            }
        }
        //Dita.push(NewAva);
        if(NewAva.End!=0)
            Beg=NewAva.End+Main.mbr_partition[i].part_size;
    }
    AVA NewAva;

    NewAva.Begin=Beg;
    NewAva.End=End;
    NewAva.Size=NewAva.End-NewAva.Begin;
    if(NewAva.Size>0){
        if(NewAva.Size>=Size){
            if(Tamanio==-1 || NewAva.Size>Tamanio){
                Tamanio =NewAva.Size;
                Inicio=NewAva.Begin;
            }
        }
    }
    return Inicio;
}
/*!
    \class QCache
    \brief Busca Si El Tamaño Disponible En El Disco Danto Path Y Tamaño Requerido Del Bloque .
*/
int Functions::FirstFit(int Size, const char *Path){

    FILE *f;
    f=fopen(Path,"r");
    if (!f)
        return -1;
    MBR Main;
    fseek(f,0,SEEK_SET);
    fread(&Main,sizeof(MBR),1,f);
    fclose(f);
    int Beg=int(sizeof (MBR));
    int End=FileSize(Path);

    for (int i=0;i<4;i++) {
        AVA NewAva;
        NewAva.Begin=Beg;
        NewAva.End=Main.mbr_partition[i].part_start;
        NewAva.Size=NewAva.End-NewAva.Begin;
        if(NewAva.Size>0){
            if(NewAva.Size>=Size){
                return NewAva.Begin;
            }
        }
        if(NewAva.End!=0)
            Beg=NewAva.End+Main.mbr_partition[i].part_size;
    }
    AVA NewAva;

    NewAva.Begin=Beg;
    NewAva.End=End;
    NewAva.Size=NewAva.End-NewAva.Begin;
    if(NewAva.Size>0){
        if(NewAva.Size>=Size){
            return NewAva.Begin;
        }
    }
    return -1;

}
/*!
    \class QCache
    \brief Busca Si El Tamaño Disponible En El Disco Danto Path Y Tamaño Requerido Del Bloque .
*/
int Functions::LogicalBestFit(int Size, const char *Path, int Begin, int End){
    FILE *f;
    EBR Cur;
    int LogicIndex=Begin;
    f=fopen(Path,"r+");
    if (!f){
        return-1;
    }
    int Out=-1;
    int Retu=-1;
    while(LogicIndex!=-1){
        fseek(f,LogicIndex,SEEK_SET);
        fread(&Cur,sizeof(EBR),1,f);
        LogicIndex=Cur.part_next;
        if(Cur.part_status=='t'){
           int Sz=Cur.part_start-Begin;
           if(Sz>0){
               if(Sz>=Size){
                   if(Sz<Out ||Out==-1){
                       Retu=Begin;
                       Out=Sz;
                   }
               }
           }
           Begin=Cur.part_start+Cur.part_size;
        }
    }
    if(End-Begin>=Size){
        if(End-Begin<Out ||Out==-1){
            Retu=Begin;
            Out=End-Begin;
        }
    }
    fclose(f);
 return Retu;
}
/*!
    \class QCache
    \brief Busca Si El Tamaño Disponible En El Disco Danto Path Y Tamaño Requerido Del Bloque .
*/
int Functions::LogicalWorstFit(int Size, const char *Path, int Begin, int End){
    FILE *f;
    EBR Cur;
    //Logic.part_next=0;
    int LogicIndex=Begin;
    f=fopen(Path,"r+");
    if (!f){
        return-1;
    }
    //Cola para los fit
    //std::queue <EBR> Dita;
    int Out=-1;
    int Retu=-1;
    while(LogicIndex!=-1){
        fseek(f,LogicIndex,SEEK_SET);
        fread(&Cur,sizeof(EBR),1,f);
        LogicIndex=Cur.part_next;
        if(Cur.part_status=='t'){
           int Sz=Cur.part_start-Begin;
           if(Sz>0){
               if(Sz>=Size){
                   if(Sz>Out ||Out==-1){
                       Retu=Begin;
                       Out=Sz;
                   }
               }
           }
           Begin=Cur.part_start+Cur.part_size;
        }
    }
    if(End-Begin>=Size){
        if(End-Begin>Out ||Out==-1){
            Retu=Begin;
            Out=End-Begin;
        }
    }
    fclose(f);
 return Retu;
}
/*!
    \class QCache
    \brief Verifica si el archivo existe.
*/
bool Functions::ExisteArchivo(const char *Path){
    FILE *f;
    f=fopen(Path,"r+");
    if (!f){
        return false;
    }
    fclose(f);
    return true;
}
/*!
    \class QCache
    \brief Busca Si El Tamaño Disponible En El Disco Danto Path Y Tamaño Requerido Del Bloque .
*/
int Functions::LogicalFirstFit(int Size, const char *Path, int Begin, int End){
    FILE *f;
    EBR Cur;
    //Logic.part_next=0;
    int LogicIndex=Begin;
    f=fopen(Path,"r+");
    if (!f){
        return-1;
    }
    //Cola para los fit
    //std::queue <EBR> Dita;
    while(LogicIndex!=-1){
        fseek(f,LogicIndex,SEEK_SET);
        fread(&Cur,sizeof(EBR),1,f);
        LogicIndex=Cur.part_next;
        if(Cur.part_status=='t'){
           int Sz=Cur.part_start-Begin;
           if(Sz>0){
               if(Sz>=Size){
                   fclose(f);
                   return Begin;

               }
           }
           Begin=Cur.part_start+Cur.part_size;
        }
    }
    if(End-Begin>=Size){
        fclose(f);
     return Begin;
    }
 fclose(f);
 return -1;
}
/*!
    \class QCache
    \brief Devuelve Un Numero Según La unidad Que Usa.
*/
int Functions::Mult(int Num, char C){
    C=char(tolower(C));
    if(C=='m'){
        return Num*1024*1024;
    }else if(C=='k'){
        return Num*1024;
    }else{
        return Num;
    }
}

/*!
    \class QCache
    \brief Da El Tamaño sin ocupar de un bloque en el disco, si se usa en uno ocupado da 0.
*/
int Functions::BlockSize(int Num,const char *Path){

    FILE *f;
    char r;
    int Contador=0;
    int Siz= FileSize(Path);
    f=fopen(Path,"r");
    if (!f)
        return -1;
    fseek(f,Num,SEEK_SET);
    for (int i=Num;i<Siz; i++)
    {
        fread(&r,sizeof (char),1,f);
        if(r!='0'){
            return Contador;
        }
        else {
            Contador++;
        }
    }
    fclose(f);
    return Contador;
}
/*!
    \class QCache
    \brief Da El Tamaño De Un Archivo.
*/
int Functions::FileSize(const char *Path){
    FILE *f;
    f=fopen(Path,"r");
    fseek(f, 0L, SEEK_END);
    int Size = int(ftell(f));
    fclose(f);
    return Size;
}

void Functions::Out(const char *Path){
    qDebug() << Path;
}

