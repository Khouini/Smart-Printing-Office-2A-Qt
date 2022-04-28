#include "produit.h"
#include<QSqlQueryModel>
#include <QRegExpValidator>
#include <QDesktopServices>
#include <QPdfWriter>
#include <QPainter>
#include <QMessageBox>
#include <QTextStream>
#include<QFile>
#include<QDebug>
#include<QString>
#include <QDateTime>
#define NOM_RX "^([a-z]+[,.]?[ ]?|[a-z]+['-]?)+$"

produit::produit(int id_produit,QString nom_produit,QString reference_produit,QString type,QString marque ,QString qte )
{


    this ->id_produit=id_produit;
    this->nom_produit=nom_produit;
    this->reference_produit=reference_produit;
     this ->type=type;
     this ->marque=marque;
     this ->qte=qte;





}
bool produit::ajouter()
{QSqlQuery query;
    QString res = QString::number(id_produit);

    //prepare() prend la requete en parametre pour la preparer a léxéxution
    query.prepare("insert into produit(id_produit,nom_produit,reference_produit,type,marque,qte)""values(:id_produit, :nom_produit, :reference,:type,:marque,:qte)");
//Creation des variables liees

    query.bindValue(":id_produit",res);
    query.bindValue(":nom_produit",nom_produit);
    query.bindValue(":reference",reference_produit);
    query.bindValue(":type",type);
    query.bindValue(":marque",marque);
    query.bindValue(":qte",qte);
    return query.exec();//exec() envoie la requéte pour léxecuter
}

bool produit::alert()
{QSqlQuery query;
    QString res = QString::number(id_produit);
    //prepare() prend la requete en parametre pour la preparer a léxéxution
    query.prepare("select * from produit  where id_produit < 5");


    return query.exec();//exec() envoie la requéte pour léxecuter
}

void produit::printPDF_produit()
{

    QPdfWriter pdf("C:/Users/dell/Desktop/stock/produit.pdf");
    QPainter painter(&pdf);
    QFont font=painter.font();
    QMessageBox msgBox;

       font.setPointSize(font.pointSize() * 2);
       painter.setFont(font);
       painter.setPen(Qt::black);
       painter.drawText(300,800,"id: ");
       painter.drawText(300,1600 , "nom_produit: ");
       painter.drawText(300,2400, "reference: ");
       painter.drawText(300, 3200, "type: ");
       painter.drawText(300, 4000, "marque: ");
        painter.drawText(300, 4800, "qte: ");
       painter.setPen(Qt::blue);
        QString res = QString::number(id_produit);
       painter.drawText(2000, 800, res);
       painter.drawText(2000, 1600, this->nom_produit);
       painter.drawText(2000, 2400, this->reference_produit);
       painter.drawText(2000, 3200, this->type);
       painter.drawText(2000,4000,this->marque);
        painter.drawText(2000,4800,this->qte);
       painter.end();
       msgBox.setIcon(QMessageBox::Information);
       msgBox.setText("A pdf has been created.");
       msgBox.exec();


}

QSqlQueryModel * produit::afficher()
{

    QSqlQueryModel * model=new QSqlQueryModel() ;
    model->setQuery("select * from produit ") ;
    return model ;

}
bool produit::supprimer(int id_produit)
{
    QSqlQuery query ;
    QString res = QString::number(id_produit) ;
    query.prepare("Delete from produit where id_produit= :id_produit") ;
    query.bindValue(":id_produit",res) ;
    return query.exec() ;

}
bool produit::modifier(int id_produit)
{
QSqlQuery query;
QString res= QString::number(id_produit);
query.prepare("Update produit set id_produit = :id_produit , nom_produit = :nom_produit , reference_produit = :reference_produit , type = :type , marque = :marque  where id_produit = :id_produit ");
query.bindValue(":id_produit",res);
query.bindValue(":nom_produit",nom_produit);
query.bindValue(":reference_produit",reference_produit);
query.bindValue(":type",type);
query.bindValue(":marque",marque);
return    query.exec();
}

QSqlQueryModel * produit :: trie_produitN()
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("select * from produit order by nom_produit DESC" );
    return model ;


}

QSqlQueryModel * produit:: trie_produitQ()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from produit order by id_produit" );
    return model ;

}

QSqlQueryModel * produit::recherche(QString rech)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from produit where id_produit LIKE '%"+rech+"%'");
    return  model ;

 }
void produit::save(int id_produit,QString nom_produit ,QString reference_produit, QString type,QString marque,QString qte)
{    QFile file ("D:/Documents/GitHub/IntegrationQt/Historique/historiqueProduits.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);


             out <<"id: " << id_produit << endl;
             out <<"nom_produit: " << nom_produit << endl;
             out <<"reference_produit: " << reference_produit << endl;
             out <<"type: " << type << endl;
             out <<"marque: " << marque << endl;
              out <<"qte: " << qte << endl;
             QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz");
                     out <<"date: " << sDate << endl;
                     out <<"************************ " <<endl;


}
QString produit::load()
{   QString tmp="";
    QFile file("D:/Documents/GitHub/IntegrationQt/Historique/historiqueProduits.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      tmp="";

    QTextStream in(&file);

   while (!in.atEnd()) {

         QString myString = in.readLine();
         tmp+=myString+"\n";

   }
   return tmp;
}



