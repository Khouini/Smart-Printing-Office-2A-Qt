#ifndef EMPLOYE_H
#define EMPLOYE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class employe
{
private:
    QString nom, prenom, adresse, email, type;
    int cin;
public:
    employe(){}
    employe(int,QString,QString,QString,QString,QString);

    QString getnom(){return nom;}
    QString getprenom(){return prenom;}
        QString getemail(){return email;}
        QString gettype(){return type;}
        QString getadresse(){return adresse;}
    int getcin(){return cin;}
    void settnom(QString n){nom=n;}
    void setprenom(QString p){prenom=p;}
    void settype(QString t){type=t;}
    void setemail(QString e){email=e;}
    void setadresse(QString a){adresse=a;}
    void setcin(int c){cin=c;}
    void save(int,QString,QString,QString,QString,QString);

    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * trier(QString,QString);
    QSqlQueryModel * rechercher(QString);
    void printPDF_employe();
    bool supprimer(int);
    bool modifier();
    QString load();
    void save(QString,QString);
};

#endif // EMPLOYE_H
