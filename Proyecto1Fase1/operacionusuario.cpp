#include "operacionusuario.h"
std::string OperacionUsuario::CambiarGrupo(std::string Usr, std::string Gru){
    std::string Retorno="";
    int Longitud=SistemaUsuario->length();
    USU Usuario;
    for (int i=0;i<Longitud;i++) {
        Usuario=SistemaUsuario->at(i);
        if(Fun->IFEspecial(Usuario.Usuario,Usr)){
            if(Usuario.Uid!=0){
                USU Cambio;
                Cambio.Tipo=Usuario.Tipo;
                GRU Gr=BuscarGrupo(Gru);
                if(Gr.Gid==-1){
                    std::cout<<"No Se Encontro Grupo "+Gru<<std::endl;
                    break;
                }
                Cambio.Grupo=&Gr;
                Cambio.Uid=Usuario.Uid;
                Cambio.Usuario=Usuario.Usuario;
                Cambio.Contrasenia=Usuario.Contrasenia;
                SistemaUsuario->replace(i,Cambio);
                break;
            }
        }
    }
    Retorno=Retorno+StrGrupo()+StrUsuario();

    return Retorno;
}
std::string OperacionUsuario::RemoverUsuario(std::string Usr){
    std::string Retorno="";
    int Longitud=SistemaUsuario->length();
    USU Usuario;
    for (int i=0;i<Longitud;i++) {
        Usuario=SistemaUsuario->at(i);
        if(Fun->IFEspecial(Usuario.Usuario,Usr)){
            if(Usuario.Uid!=0){
                USU Cambio;
                Cambio.Tipo=Usuario.Tipo;
                Cambio.Grupo=Usuario.Grupo;
                Cambio.Uid=0;
                Cambio.Usuario=Usuario.Usuario;
                Cambio.Contrasenia=Usuario.Contrasenia;
                SistemaUsuario->replace(i,Cambio);
                break;
            }
        }
    }
    Retorno=Retorno+StrGrupo()+StrUsuario();

    return Retorno;
}
std::string OperacionUsuario::CrearUsuario(std::string Usr,std::string Pwd,std::string Grp){
    USU Busqueda=BuscarUsuario(Usr);
    GRU GrupoCreado=BuscarGrupo(Grp);
    if(GrupoCreado.Gid==-1){
        std::cout<<"No Existe Un Grupo Con El Nombre: "<<Grp<<std::endl;
        return "";
    }
    std::string Retorno="";
    if(Busqueda.Uid!=-1){
        std::cout<<"Ya Existe Un Usuario Con El Nombre: "<<Usr<<std::endl;
    }else{
        USU UsuarioNuevo;
        UsuarioNuevo.Uid=SistemaUsuario->length()+1;
        UsuarioNuevo.Tipo="U";
        UsuarioNuevo.Grupo=&GrupoCreado;
        UsuarioNuevo.Usuario=Usr;
        UsuarioNuevo.Contrasenia=Pwd;
        SistemaUsuario->push_front(UsuarioNuevo);
        Retorno=Retorno+std::to_string(UsuarioNuevo.Uid)+","+UsuarioNuevo.Tipo+","+UsuarioNuevo.Grupo->Grupo+","+UsuarioNuevo.Usuario+","+UsuarioNuevo.Contrasenia+"\n";
    }
    return Retorno;
}

//
std::string OperacionUsuario::RemoverGrupo(std::string Nombre){
    std::string Retorno="";
    int Longitud=SistemaGrupo->length();
    GRU Gru;
    for (int i=0;i<Longitud;i++) {
        Gru=SistemaGrupo->at(i);
        if(Fun->IFEspecial(Gru.Grupo,Nombre)){
            if(Gru.Gid!=0){
                GRU Cambio;
                Cambio.Tipo=Gru.Tipo;
                Cambio.Grupo=Gru.Grupo;
                Cambio.Gid=0;
                SistemaGrupo->replace(i,Cambio);
                break;
            }
        }
    }
    Retorno=Retorno+StrGrupo()+StrUsuario();

    return Retorno;
}
std::string OperacionUsuario::StrGrupo(){
    std::string Retorno="";
    int Longitud=SistemaGrupo->length();
    GRU Gru;
    for (int i=0;i<Longitud;i++) {
        Gru=SistemaGrupo->at(i);
        Retorno=Retorno+std::to_string(Gru.Gid)+","+Gru.Tipo+","+Gru.Grupo+"\n";
    }
    return Retorno;
}
std::string OperacionUsuario::StrUsuario(){
    std::string Retorno="";
    int Longitud=SistemaUsuario->length();
    USU Usuario;
    for (int i=0;i<Longitud;i++) {
        Usuario=SistemaUsuario->at(i);
        Retorno=Retorno+std::to_string(Usuario.Uid)+","+Usuario.Tipo+","+Usuario.Usuario+","+Usuario.Grupo->Grupo+","+Usuario.Contrasenia+"\n";
    }
    return Retorno;
}
std::string OperacionUsuario::CrearGrupo(std::string Nombre){
    GRU Busqueda=BuscarGrupo(Nombre);
    std::string Retorno="";
    if(Busqueda.Gid!=-1){
        std::cout<<"Ya Existe Un Grupo Con El Nombre: "<<Nombre<<std::endl;
    }else{
        GRU GrupoNuevo;
        GrupoNuevo.Gid=SistemaGrupo->length()+1;
        GrupoNuevo.Tipo="G";
        GrupoNuevo.Grupo="Nombre";
        SistemaGrupo->push_front(GrupoNuevo);
        Retorno=Retorno+std::to_string(GrupoNuevo.Gid)+","+GrupoNuevo.Tipo+","+GrupoNuevo.Grupo+"\n";
    }
    return Retorno;
}
//
void OperacionUsuario::Limpiar(){
    Permiso.Gid=-5;
    Permiso.Uid=-5;
    this->IDMontado="";
    this->SistemaGrupo= new QList<GRU>;
    this->SistemaUsuario= new QList<USU>;
    UsuarioActual=nullptr;
}
bool OperacionUsuario::Login(std::string Id, std::string Contra){
    USU Usu= BuscarUsuario(Id);
    if(Usu.Uid==-1){
        std::cout<<"No Se Encontro El Usuario"<<std::endl;
        return false;
    }
    if(Fun->IFEspecial(Contra,Usu.Contrasenia)){
        UsuarioActual=&Usu;
        Permiso.Gid=Usu.Grupo->Gid;
        Permiso.Uid=Usu.Uid;
        return true;
     }
    std::cout<<"Contrasenia Incorrecta"<<std::endl;
    return false;
}
OperacionUsuario::OperacionUsuario()
{
    this->IDMontado="";
    this->Fun= new Functions();
    this->SistemaGrupo= new QList<GRU>;
    this->SistemaUsuario= new QList<USU>;
    UsuarioActual=nullptr;
}
void OperacionUsuario::CargarDatos(std::string Texto){

    SaltosDeLinea(Texto);
}
void OperacionUsuario::SaltosDeLinea(std::string Texto){
    std::string s = Texto;
    std::string delimiter = "\n";
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        Comas(token);
        s.erase(0, pos + delimiter.length());
    }
}
void OperacionUsuario::Comas(std::string Texto){



    int Cantidad=CantidadComas(Texto);
    std::string s = Texto;
    std::string delimiter = ",";
    size_t pos = 0;
    std::string token;
    int Veces=0;
    if(Cantidad==2){
        GRU GrupoNuevo;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            switch (Veces) {
            case 0:{
                GrupoNuevo.Gid=std::atoi (token.c_str());
                break;
            }
            case 1:{
                GrupoNuevo.Tipo=token;
                break;
            }
            }
            Veces++;
            s.erase(0, pos + delimiter.length());
        }
        GrupoNuevo.Grupo=s;

        SistemaGrupo->push_front(GrupoNuevo);
    }

    if(Cantidad==4){
        USU UsuarioNuevo;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            switch (Veces) {
            case 0:{
                UsuarioNuevo.Uid=std::atoi (token.c_str());
                break;
            }
            case 1:{
                UsuarioNuevo.Tipo=token;
                break;
            }
            case 2:{
                GRU Gru=BuscarGrupo(token);
                if(Gru.Gid==-1){
                    std::cout<<"No Se Encontro El Grupo '"<<token<<"' Para El Usuario '"<<UsuarioNuevo.Uid<<"'"<<std::endl;
                }
                UsuarioNuevo.Grupo=&Gru;
                break;
            }
            case 3:{
                UsuarioNuevo.Usuario=token;
                break;
            }
            }
            Veces++;
            s.erase(0, pos + delimiter.length());
        }
        UsuarioNuevo.Contrasenia=s;
        SistemaUsuario->push_front(UsuarioNuevo);
    }

}
int OperacionUsuario::CantidadComas(std::string Texto){
    int Contador=0;
    int Longitud=Texto.length();
    for(int i=0;i<Longitud;i++){
        if(','==Texto.at(i)){
            Contador++;
        }
    }
    return Contador;
}
bool OperacionUsuario::HayUsuarioEnElSistema(){


    if(UsuarioActual!=nullptr)
        return true;
    else{

        return false;
        }
}
bool OperacionUsuario::UsuarioActualEsRoot(){
    if(UsuarioActual->Grupo->Gid==1)
        return true;
    else
        return false;
}
int OperacionUsuario::Uid(std::string Busqueda){
    USU Info=BuscarUsuario(Busqueda);
    return Info.Uid;
}
GRU OperacionUsuario::BuscarGrupo(std::string Nombre){
    int Longitud=SistemaGrupo->length();
    GRU Gru;
    for (int i=0;i<Longitud;i++) {
        Gru=SistemaGrupo->at(i);
        if(Fun->IFEspecial(Gru.Grupo,Nombre)){
            if(Gru.Gid!=0)
                return Gru;
        }
    }
    Gru.Gid=-1;
    return Gru;
}
USU OperacionUsuario::BuscarUsuario(std::string Nombre){
    int Longitud=SistemaUsuario->length();
    USU Usu;

    for (int i=0;i<Longitud;i++) {
        Usu=SistemaUsuario->at(i);        
        if(Fun->IFEspecial(Usu.Usuario,Nombre)){
            if(Usu.Uid!=0)
                return Usu;
        }
    }
    Usu.Uid=-1;
    return Usu;

}
