#ifndef TECHNICIENS_H
#define TECHNICIENS_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>


class Techniciens
{
    QString nom, prenom,EMAIL_EMPLOYEE,PASSWORD_EMPLOYEE;
    int id,cin,num,idtache;
public:
    Techniciens(){}
    Techniciens(int,QString,QString,int,int,int,QString,QString);

    int getid(){return id;}
    QString getnom(){return nom;}
    QString getprenom(){return prenom;}
    int getcin(){return cin;}
    int getnum(){return num;}
    int getidtache(){return idtache;}
    QString getEMAIL_EMPLOYEE(){return EMAIL_EMPLOYEE;}
    QString getPASSWORD_EMPLOYEE(){return PASSWORD_EMPLOYEE;}



    void setid(int id ){this->id=id;}
    void setnom(QString n){nom=n;}
    void setprenom(QString p){prenom=p;}
    void setcin(int cin){this->cin=cin;}
    void setnum(int num){this->num=num;}
    void setidtache(int idtache){this->idtache=idtache;}
    void setEMAIL_EMPLOYEE(QString EMAIL_EMPLOYEE){this->EMAIL_EMPLOYEE=EMAIL_EMPLOYEE;}
    void setPASSWORD_EMPLOYEE(QString PASSWORD_EMPLOYEE){this->PASSWORD_EMPLOYEE=PASSWORD_EMPLOYEE;}

    void printPDF();

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * tri_id();
    QSqlQueryModel * tri_nom();

    QSqlQueryModel * recherche(QString);
    void save(int,QString,QString,int,int,int,QString,QString) ;
    QString load() ;

};

#endif // TECHNICIENS_H
