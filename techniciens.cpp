#include "techniciens.h"
#include <QMessageBox>
#include <QPainter>
#include <QPdfWriter>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>


Techniciens::Techniciens(int id,QString nom,QString prenom,int cin,int num,int idtache , QString EMAIL_EMPLOYEE , QString PASSWORD_EMPLOYEE)
  {

    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->cin=cin;
    this->num=num;
    this->idtache=idtache;
    this->EMAIL_EMPLOYEE=EMAIL_EMPLOYEE;
    this->PASSWORD_EMPLOYEE=PASSWORD_EMPLOYEE;

}

bool Techniciens::ajouter()

{
    QSqlQuery query;
    QString res = QString::number(id);

    query.prepare("insert into EMPLOYEES values (:id,:nom,:prenom,:cin,:EMAIL_EMPLOYEE,:PASSWORD_EMPLOYEE,NULL,NULL,NULL,NULL,:idtache,NULL,NULL,:num)");

    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":cin",cin);
    query.bindValue(":num",num);
    query.bindValue(":idtache",idtache);
    query.bindValue(":EMAIL_EMPLOYEE",EMAIL_EMPLOYEE);
    query.bindValue(":PASSWORD_EMPLOYEE",PASSWORD_EMPLOYEE);

    return query.exec();
}

QSqlQueryModel * Techniciens::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select ID_EMPLOYEE,NOM_EMPLOYEE,PRENOM_EMPLOYEE,CIN_EMPLOYEE,TEL_EMPLOYEE,ID_TACHE,EMAIL_EMPLOYEE,PASSWORD_EMPLOYEE from EMPLOYEES");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("cin"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("num"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("idtache"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("email"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("password"));


    return  model;

}

bool Techniciens::supprimer(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);

    query.prepare("Delete from EMPLOYEES where ID_EMPLOYEE= :id");
    query.bindValue(":id",res);
    return  query.exec();
}
bool Techniciens::modifier()

{
    QSqlQuery query;
    QString res = QString::number(id);

    query.prepare("update EMPLOYEES set NOM_EMPLOYEE = :nom, PRENOM_EMPLOYEE = :prenom, CIN_EMPLOYEE = :cin,TEL_EMPLOYEE = :num, ID_TACHE = :idtache, EMAIL_EMPLOYEE = :EMAIL_EMPLOYEE , PASSWORD_EMPLOYEE = :PASSWORD_EMPLOYEE where ID_EMPLOYEE = :id ");

    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":cin",cin);
    query.bindValue(":num",num);
    query.bindValue(":idtache",idtache);
    query.bindValue(":EMAIL_EMPLOYEE",EMAIL_EMPLOYEE);
    query.bindValue(":PASSWORD_EMPLOYEE",PASSWORD_EMPLOYEE);

    return query.exec();
}



QSqlQueryModel * Techniciens:: tri_id()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select ID_EMPLOYEE,NOM_EMPLOYEE,PRENOM_EMPLOYEE,CIN_EMPLOYEE,TEL_EMPLOYEE,ID_TACHE,EMAIL_EMPLOYEE,PASSWORD_EMPLOYEE from EMPLOYEES order by ID_EMPLOYEE" );
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID")) ;
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom")) ;
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom")) ;
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("cin")) ;
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("num")) ;
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("idtache")) ;
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("email")) ;
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("mdp")) ;

    return model ;

}

QSqlQueryModel * Techniciens:: tri_nom()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select ID_EMPLOYEE,NOM_EMPLOYEE,PRENOM_EMPLOYEE,CIN_EMPLOYEE,TEL_EMPLOYEE,ID_TACHE,EMAIL_EMPLOYEE,PASSWORD_EMPLOYEE from EMPLOYEES order by NOM_EMPLOYEE" );
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID")) ;
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom")) ;
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom")) ;
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("cin")) ;
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("num")) ;
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("idtache")) ;
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("email")) ;
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("mdp")) ;

    return model ;

}


QSqlQueryModel * Techniciens::recherche(QString rech)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from EMPLOYEES where ID_EMPLOYEE LIKE '%"+rech+"%'");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("num"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("idtache"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("email")) ;
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("mdp")) ;
    return  model ;

 }




void Techniciens::printPDF()
{

    QPdfWriter pdf("C:/Users/Majd Tabessi/Desktop/ESPRIT2-2/projet c++/interfacefin MRIGEL/generer.pdf");
    QPainter painter(&pdf);
    QFont font=painter.font();
    QMessageBox msgBox;
    QString resID=QString::number(id);
    QString resCIN=QString::number(cin);
    QString resNUM=QString::number(num);
    QString resIDT=QString::number(idtache);

    font.setPointSize(font.pointSize() * 2);
       painter.setFont(font);
       painter.setPen(Qt::black);
       painter.drawText(300,1500 , "id: ");
       painter.drawText(300,2000, "nom: ");
       painter.drawText(300, 2500, "prenom: ");
       painter.drawText(300, 3000, "cin: ");
       painter.drawText(300,3500, "num: ");
       painter.drawText(300,4000, "id tache: ");
       painter.drawText(300,4500, "mot de passe: ");
       painter.drawText(300,5000, "email: ");


       painter.setPen(Qt::blue);
       painter.drawText(2000, 1500, resID);
       painter.drawText(2000, 2000, this->nom);
       painter.drawText(2000, 2500, this->prenom);
       painter.drawText(2000, 3000, resCIN);
       painter.drawText(2000,3500, resNUM);
       painter.drawText(2000,4000, resIDT);
       painter.drawText(2000, 4500, this->PASSWORD_EMPLOYEE);
       painter.drawText(2000, 5000, this->EMAIL_EMPLOYEE);



       painter.end();
       msgBox.setIcon(QMessageBox::Information);
       msgBox.setText("A pdf has been created.");
       msgBox.exec();


}


void Techniciens::save(int id,QString nom,QString prenom,int cin,int num,int idtache , QString EMAIL_EMPLOYEE , QString PASSWORD_EMPLOYEE)
{    QFile file ("C:/Users/Majd Tabessi/Desktop/ESPRIT2-2/projet c++/interfacefin MRIGEL/histo.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);


             out <<"id: " << id << endl;
             out <<"nom: " << nom << endl;
             out <<"prenom: " << prenom << endl;
              out <<"cin: " << cin << endl;
              out <<"num: " << num << endl;
              out <<"idtache: " << idtache << endl;
               out <<"email: " << EMAIL_EMPLOYEE << endl;
               out <<"password: " << PASSWORD_EMPLOYEE << endl;
                QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz");
                         out <<"date: " << sDate << endl;
                         out <<"************************ " <<endl;


    }


QString Techniciens::load()
{   QString tmp="";
    QFile file("C:/Users/Majd Tabessi/Desktop/ESPRIT2-2/projet c++/interfacefin MRIGEL/histo.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      tmp="";

    QTextStream in(&file);

   while (!in.atEnd()) {

         QString myString = in.readLine();
         tmp+=myString+"\n";

   }
   return tmp;
}

