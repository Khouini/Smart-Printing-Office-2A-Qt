#ifndef FOURNISSEURS_H
#define FOURNISSEURS_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Fournisseurs
{
    int ID;
    int Num;
    QString Email;
    QString Produit;
    QString Date_Arrivee;
    QString Nom;
public:
    Fournisseurs();
    Fournisseurs(int, int, QString, QString, QString, QString);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * trier();
    QSqlQueryModel * trierNom();
    QSqlQueryModel * chercher(QString);


    QStringList lister2();
    void printPDF_employe() ;
};

#endif // FOURNISSEURS_H
