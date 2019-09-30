#ifndef OPERACIONUSUARIO_H
#define OPERACIONUSUARIO_H
#include "functions.h"
#include <QList>

class OperacionUsuario
{
public:
    IUG Permiso;
    //Operaciones Usuarios
    std::string CambiarGrupo(std::string Usr,std::string Gru);
    std::string RemoverUsuario(std::string Usr);
    std::string CrearUsuario(std::string Usr,std::string Pwd,std::string Grp);
    //operaciones Grupo
    std::string RemoverGrupo(std::string Nombre);
    std::string CrearGrupo(std::string Nombre);
    //Informacion
    void CargarDatos(std::string Texto);
    std::string IDMontado;
    USU *UsuarioActual;
    //Mensaje
    bool HayUsuarioEnElSistema();
    //Es Root
    bool UsuarioActualEsRoot();
    //Login
    bool Login(std::string Id, std::string Contra);
    OperacionUsuario();
    void Limpiar();
    int Uid(std::string Busqueda);
private:
    std::string StrGrupo();
    std::string StrUsuario();
    int CantidadComas(std::string Texto);
    void SaltosDeLinea(std::string Texto);
    void Comas(std::string Texto);
    GRU BuscarGrupo(std::string Nombre);
    USU BuscarUsuario(std::string Nombre);
    Functions *Fun;
    QList<USU> *SistemaUsuario;
    QList<GRU> *SistemaGrupo;
};

#endif // OPERACIONUSUARIO_H
