#include "histo.h"


#include <QSqlQuery>
#include <QtDebug>
#include<QSqlQueryModel>
#include <QString>

#include <QObject>
#include<QDate>

histo::histo()
{

}
histo::histo(QString b, int c)
 {
    operation=b;
    id_f=c;
 }

void histo::Ajouter()
{
    QSqlQuery query;


    query.prepare("insert into HISTORIQUE(ID_HISTO,DATE_HISTO,TYPE_OPERATION, id_four) values(HISTORIQUE_SEQ.nextval, sysdate, :operation, :id_fournisseur)");// ya3tik numero eli be3de
   query.bindValue(":operation",operation);
   query.bindValue(":id_fournisseur",id_f);

 query.exec();
}
QSqlQueryModel * histo::Afficher( )
{
  QSqlQueryModel * model= new QSqlQueryModel();

       model->setQuery("select DATE_HISTO, TYPE_OPERATION, ID_FOUR from HISTORIQUE ;");
       model->setHeaderData(0, Qt::Horizontal,QObject:: tr("date et heure"));
       model->setHeaderData(1, Qt::Horizontal,QObject:: tr("Operation"));
       model->setHeaderData(1, Qt::Horizontal,QObject:: tr("ID fournisseur"));



 return model;
}
