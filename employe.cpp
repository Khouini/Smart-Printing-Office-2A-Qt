#include "employe.h"
#include <QPdfWriter>
#include "mainwindow.h"
#include <QMessageBox>
#include <QPainter>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QDateTime>
employe::employe(int cin,QString nom,QString prenom,QString email,QString type,QString adresse)
{
      this->cin=cin;
      this->prenom=prenom;
      this->nom=nom;
      this->email=email;
    this->type=type;
    this->adresse=adresse;
}
bool employe::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(cin);
    query.prepare("insert into EMPLOYE (CIN, NOM, PRENOM, EMAIL, TYPE, ADRESSE)" "values(:cin, :nom, :prenom, :email, :type, :adresse)");
    query.bindValue(":cin",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":email",email);
    query.bindValue(":type",type);
    query.bindValue(":adresse",adresse);
    return query.exec();
}
QSqlQueryModel * employe::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from employe");


    return model;
}
bool employe::supprimer(int cin)
{
    QSqlQuery query;
    QString res = QString::number(cin);
    query.prepare("Delete from EMPLOYE where CIN= :cin");
    query.bindValue(":cin",res);

    return query.exec();
}
bool employe::modifier()
{
    QSqlQuery query;
    QString res = QString::number(cin);
    query.prepare("update  EMPLOYE set CIN = :cin, NOM = :nom, PRENOM = :prenom, EMAIL = :email, TYPE = :type, ADRESSE = :adresse where CIN =:cin");
    query.bindValue(":cin",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":email",email);
    query.bindValue(":type",type);
    query.bindValue(":adresse",adresse);
    return query.exec();
}
QSqlQueryModel * employe::trier(QString type_tri, QString tri_par)
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from employe order by "+tri_par+" "+type_tri+"");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("email"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("type"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("adresse"));

    return model;
}

QSqlQueryModel * employe::rechercher(QString cin )
{

     QSqlQueryModel *model=new QSqlQueryModel();
     model->setQuery("select * from employe where (CIN LIKE '"+cin+"')  ") ;
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("email"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("type"));
     model->setHeaderData(5,Qt::Horizontal,QObject::tr("adresse"));

      return model;
}

void employe::printPDF_employe()
{
    QPdfWriter pdf("C:/Users/souay/OneDrive/Documents/untitled/test.pdf");
    QPainter painter(&pdf);
    QFont font=painter.font();
    QMessageBox msgBox;
       font.setPointSize(font.pointSize() * 2);
       painter.setFont(font);
       painter.setPen(Qt::black);
       painter.drawText(300,800 , "nom: ");
       painter.drawText(300,1600, "prenom: ");
       painter.drawText(300, 2400, "email: ");
       painter.drawText(300, 3200, "type: ");
       painter.drawText(300,4000,"adresse: ");
       painter.setPen(Qt::blue);
       painter.drawText(2000, 800, this->nom);
       painter.drawText(2000, 1600, this->prenom);
       painter.drawText(1500, 2400, this->email);
       painter.drawText(2000, 3200, this->type);
       painter.drawText(2000,4000,this->adresse);
       painter.end();
       msgBox.setIcon(QMessageBox::Information);
       msgBox.setText("A pdf has been created.");
       msgBox.exec();
}


void employe::save(int cin ,QString nom,QString prenom , QString email ,QString adresse ,QString type )
{    QFile file ("C:/Users/souay/OneDrive/Documents/untitled/histo.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
      QTextStream out(&file);
       out  << endl;
       out <<"CIN: " << cin << endl;
       out <<"Nom: " << nom << endl;
       out <<"Prenom: " << prenom << endl;
       out <<"Email: " << email << endl;
       out <<"adresse: " << adresse << endl;
       out <<"type: " << type << endl;
       QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz");
       out <<"date: " << sDate << endl;
       out <<"********************** " <<endl;
}
QString employe::load()
{  QString tmp="";
    QFile file("C:/Users/souay/OneDrive/Documents/untitled/histo.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      tmp="";

    QTextStream in(&file);

   while (!in.atEnd()) {

         QString myString = in.readLine();
         tmp+=myString+"\n";

   }
   return tmp;
}
