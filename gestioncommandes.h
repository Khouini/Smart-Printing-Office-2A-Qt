#ifndef GESTIONCOMMANDES_H
#define GESTIONCOMMANDES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class GestionCommandes
{
    int id_commande, id_compte;
public:
    GestionCommandes();
    GestionCommandes(int, int);
    bool EtablirCompte();
    QSqlQueryModel * afficherCommandes1();
    QSqlQueryModel * afficherCommandes2();
    QSqlQueryModel * trierCommandes1(QString, QString);
    QSqlQueryModel * trierCommandes2(QString, QString);
    QSqlQueryModel * recherche1(QString);
    QSqlQueryModel * recherche2(QString);
    QSqlQueryModel * afficherComboBoxCommandes();
    QSqlQueryModel * afficherComboBoxCompte();
    QSqlQueryModel * afficherComboBoxCompte2();
    QSqlQueryModel * afficherComboBoxCodePromo();

};

#endif // GESTIONCOMMANDES_H
