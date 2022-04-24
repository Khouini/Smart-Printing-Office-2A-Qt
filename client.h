#ifndef CLIENT_H
#define CLIENT_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

// test
class client
{
    QString   nom , prenom , email , sexe , type_client  ;
    int idclient , cinn ;
public:

    //constructeurs
    client();
    client(QString,QString,QString,QString,QString,int,int) ;
    //get
    int getidclient(){return idclient;}
    int getcinn(){return cinn;}
    QString getnom(){return nom;}
    QString getprenom(){return prenom;}
    QString getemail(){return email;}
    QString getsexe(){return sexe;}
    QString gettype_client(){return type_client;}
     //set
    void setidclient(int idclient){this->idclient=idclient;}
    void setcinn(int cinn){this->cinn=cinn;}
    void setnom(QString nom){this->nom=nom;}
    void setprenom(QString prenom){this->prenom=prenom;}
    void setemail(QString email){this->email=email;}
    void setsexe(QString sexe){this->sexe=sexe;}
    void settype_client(QString type_client){this->type_client=type_client;}
    //fonction
    bool ajouterclient() ;
    QSqlQueryModel * afficher() ;
    QSqlQueryModel * tri(QString,QString) ;
    QSqlQueryModel * rechercher(QString) ;
    bool supprimer(int) ;
    bool modifierclient() ;
    bool controle_saisie_client(client) ;
    bool controle_saisie_nom() ;
    bool controle_saisie_email() ;
    void printPDF_client() ;
    void save(QString ,QString , QString,QString,QString,QString,QString,QString) ;
    QString load() ;



};

#endif // CLIENT_H
