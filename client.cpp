#include "client.h"
#include <QPdfWriter>
#include "mainwindow.h"
#include <QPainter>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
// #include

client::client()
{

}
client::client(QString nom ,QString prenom ,QString email,QString sexe,QString type_client,int idclient,int cinn)
{
   this->nom=nom;
   this->prenom=prenom;
   this->email=email;
   this->sexe=sexe;
   this->type_client=type_client;
   this->idclient=idclient;
   this->cinn=cinn;

}
bool client::ajouterclient()
{
    client c ;
    QSqlQuery query ;
    QString res1 = QString::number(idclient) ;
    QString res2 = QString::number(cinn) ;

    //insertion
    query.prepare("insert into CLIENTS values (:idclient, :nom , :prenom, :email, :cinn,:sexe , :type_client, NULL )");
    //creations des variables liee
    query.bindValue(":idclient",res1) ;
    query.bindValue(":nom",nom) ;
    query.bindValue(":prenom",prenom) ;
    query.bindValue(":email",email) ;
    query.bindValue(":cinn",res2) ;
    query.bindValue(":type_client",type_client) ;
    query.bindValue(":sexe",sexe) ;



    //exec
    return query.exec() ;


    }
QSqlQueryModel * client::tri(QString type , QString attribut)
{
   QSqlQueryModel * model=new QSqlQueryModel() ;
   model->setQuery("select * from CLIENTS order by "+attribut+" "+type+" ") ;
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id_Client")) ;
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom")) ;
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom")) ;
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("Email")) ;
   model->setHeaderData(4,Qt::Horizontal,QObject::tr("Cin")) ;
   model->setHeaderData(5,Qt::Horizontal,QObject::tr("Sexe")) ;
   model->setHeaderData(6,Qt::Horizontal,QObject::tr("Type")) ;
   return model ;

}
QSqlQueryModel *client::rechercher(QString id )
{

     QSqlQueryModel *model=new QSqlQueryModel();
     model->setQuery("select * from CLIENTS where (ID_CLIENT LIKE '"+id+"')  ") ;
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id_Client")) ;
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom")) ;
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom")) ;
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("Email")) ;
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("Cin")) ;
     model->setHeaderData(5,Qt::Horizontal,QObject::tr("Sexe")) ;
     model->setHeaderData(6,Qt::Horizontal,QObject::tr("Type")) ;

      return model;
}



QSqlQueryModel * client::afficher()
{
   QSqlQueryModel * model=new QSqlQueryModel() ;
   model->setQuery("select * from CLIENTS ") ;
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id_Client")) ;
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom")) ;
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom")) ;
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("Email")) ;
   model->setHeaderData(4,Qt::Horizontal,QObject::tr("Cin")) ;
   model->setHeaderData(5,Qt::Horizontal,QObject::tr("Sexe")) ;
   model->setHeaderData(6,Qt::Horizontal,QObject::tr("Type")) ;
   return model ;

}

bool client::supprimer(int idclient)
{
    QSqlQuery query ;
    QString res = QString::number(idclient) ;
    query.prepare("Delete from CLIENTS where ID_CLIENT=:idclient") ;
    query.bindValue(":idclient",res) ;
    return  query.exec() ;


}
bool client::modifierclient(){
    QSqlQuery query ;
    QString res1 = QString::number(idclient) ;
    QString res2 = QString::number(cinn) ;
    //insertion
    query.prepare("update CLIENTS set nom_client = :nom, prenom_client = :prenom, email_client = :email, cin_client = :cinn, sexe_client = :sexe , type_client =  :type_client where id_client = :idclient;");
    //creations des variables liee
    query.bindValue(":idclient",res1) ;
    query.bindValue(":nom",nom) ;
    query.bindValue(":prenom",prenom) ;
    query.bindValue(":email",email) ;
    query.bindValue(":cinn",res2) ;
    query.bindValue(":type_client",type_client) ;
    query.bindValue(":sexe",sexe) ;


    //exec
    return query.exec() ;
}
void client::printPDF_client()
{
    QPdfWriter pdf("D:/Documents/GitHub/IntegrationQt/PDF/clients.pdf");
    QPainter painter(&pdf);
    QFont font=painter.font();
    QMessageBox msgBox;
    QString res1 = QString::number(idclient) ;
    QString res2 = QString::number(cinn) ;
    font.setPointSize(font.pointSize() * 2);
           painter.setFont(font);
           painter.setPen(Qt::red);
           painter.drawText(2500,400 , "Fiche client: ");
           painter.setPen(Qt::black);
           painter.drawText(300,800 , "id_client: ");
           painter.drawText(300,1600, "cin_client: ");
           painter.drawText(300, 2400, "nom_client: ");
           painter.drawText(300, 3200, "prenom_client: ");
           painter.drawText(300,4000,"email_client: ");
           painter.drawText(300,4800,"sexe_client: ");
           painter.drawText(300,5600,"type_client: ");
           painter.setPen(Qt::blue);
           painter.drawText(2100, 800, res1);
           painter.drawText(2100,1600,res2);
           painter.drawText(2100, 2400, this->nom);
           painter.drawText(2100, 3200 , this->prenom);
           painter.drawText(2100, 4000, this->email);
           painter.drawText(2100, 4800, this->sexe);
           painter.drawText(2100, 5600, this->type_client);

           painter.end();
           msgBox.setIcon(QMessageBox::Information);
           msgBox.setText("A pdf has been created.");
           msgBox.exec();
}
void client::save(QString id,QString cinn , QString nom ,QString prenom , QString email ,QString sexe ,QString type_client , QString operation )
{    QFile file ("D:/Documents/GitHub/IntegrationQt/Historique/hitoriqueClients.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
      QTextStream out(&file);
       out  << endl;
       out <<"Operation effectuée: " << operation << endl;
       out <<"ID: " << id << endl;
       out <<"CIN: " << cinn << endl;
       out <<"Nom: " << nom << endl;
       out <<"Prenom: " << prenom << endl;
       out <<"Email: " << email << endl;
       out <<"sexe: " << sexe << endl;
       out <<"type_client: " << type_client << endl;
       QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz");
       out <<"date: " << sDate << endl;
       out <<"************************ " <<endl;


}
QString client::load()
{  QString tmp="";
    QFile file("D:/Documents/GitHub/IntegrationQt/Historique/hitoriqueClients.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      tmp="";

    QTextStream in(&file);

   while (!in.atEnd()) {

         QString myString = in.readLine();
         tmp+=myString+"\n";

   }
   return tmp;
}



