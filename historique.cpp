#include "historique.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QSqlQueryModel>
#include <QString>
#include <QObject>
#include<QDate>
Historique::Historique()
{

}
Historique::Historique(QString operation, int id, QString nom){
    this->operation=operation;
    this->id=id;
    this->nom=nom;
}

void Historique::Ajouter()
{
    QSqlQuery query;
    query.prepare("insert into HISTORIQUE_COMPTE values (HISTORIQUE_COMPTE_SEQ.nextval, sysdate, :operation, :n_compte, :nom_compte);");
    query.bindValue(":operation",operation);
    query.bindValue(":n_compte",id);
    query.bindValue(":nom_compte",nom);
    query.exec();
}
QSqlQueryModel * Historique::Afficher()
{
  QSqlQueryModel * model= new QSqlQueryModel();
       model->setQuery("select DATE_HIS, TYPE_OPERATION, N_COMPTE, NOM_COMPTE FROM HISTORIQUE_COMPTE;");
       model->setHeaderData(0, Qt::Horizontal,QObject:: tr("Date"));
       model->setHeaderData(1, Qt::Horizontal,QObject:: tr("Type d'opération"));
       model->setHeaderData(2, Qt::Horizontal,QObject:: tr("Numéro Compte"));
       model->setHeaderData(3, Qt::Horizontal,QObject:: tr("Nom Compte"));
 return model;
}
