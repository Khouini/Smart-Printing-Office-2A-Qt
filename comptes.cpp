#include "comptes.h"
#include <QPdfWriter>
#include <QPainter>
#include <QMessageBox>

Comptes::Comptes()
{

}
Comptes::Comptes(int Numero, QString Nom, QString Classe, QString Type,  float Solde){
    this->Numero=Numero;
    this->Nom=Nom;
    this->Classe=Classe;
    this->Type=Type;
    this->Solde=Solde;
}
bool Comptes::ajouter(){
    QSqlQuery query;
    query.prepare("insert into Comptes values (:Numero, :Nom, :Classe, :Type, :Solde, NULL)");
    query.bindValue(":Numero", Numero);
    query.bindValue(":Nom", Nom);
    query.bindValue(":Classe", Classe);
    query.bindValue(":Solde", Solde);
    query.bindValue(":Type", Type);
    return query.exec();
}
QSqlQueryModel * Comptes::afficher(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from Comptes");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Numéro"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("Classe"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("Solde"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("ID User"));

    return model;
}
bool Comptes::supprimer(int num){
    QSqlQuery query;
    QString res = QString::number(num);
    query.prepare("delete from Comptes where N_COMPTE = :num;");
    query.bindValue(":num", res);
    return query.exec();
}
bool Comptes::modifier(){
    QSqlQuery query;
    query.prepare("UPDATE Comptes set NOM_COMPTE = :Nom, CLASSE_COMPTE = :Classe, TYPE_COMPTE = :Type, SOLDE_COMPTE = :Solde  WHERE N_COMPTE = :Numero");
    query.bindValue(":Numero", Numero);
    query.bindValue(":Nom", Nom);
    query.bindValue(":Classe", Classe);
    query.bindValue(":Solde", Solde);
    query.bindValue(":Type", Type);
    return query.exec();
}

QSqlQueryModel * Comptes::trier(QString type_tri, QString tri_par){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from Comptes order by "+tri_par+" "+type_tri+" ");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Numéro"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("Classe"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("Solde"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("ID User"));
    return model;
}
QSqlQueryModel * Comptes::recherche(QString rech){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from Comptes where  (N_COMPTE) LIKE '%"+rech+"%' OR (NOM_COMPTE) LIKE '%"+rech+"%' OR (CLASSE_COMPTE) LIKE '%"+rech+"%' OR (TYPE_COMPTE) LIKE '%"+rech+"%' OR (SOLDE_COMPTE) LIKE '%"+rech+"%' ");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Numéro"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("Classe"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("Solde"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("ID User"));
    return model;
}
QSqlQueryModel * Comptes::rechercheID(QString rech){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from Comptes where (N_COMPTE) LIKE "+rech+" ");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Numéro"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("Classe"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("Solde"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("ID User"));
    return model;
}
void Comptes::printPDF_comptes()
{
    QPdfWriter pdf("D:/Documents/GitHub/IntegrationQt/PDF/comptes.pdf");
    QPainter painter(&pdf);
    QFont font=painter.font();
    QMessageBox msgBox;
    QString id = QString::number(Numero) ;
    QString solde = QString::number(Solde) ;
    font.setPointSize(font.pointSize() * 2);
           painter.setFont(font);
           painter.setPen(Qt::black);
           painter.drawText(300,800 , "Numero: ");
           painter.drawText(300,1600, "Nom: ");
           painter.drawText(300, 2400, "Classe: ");
           painter.drawText(300, 3200, "Type: ");
           painter.drawText(300,4000,"Solde: ");
           painter.setPen(Qt::blue);
           painter.drawText(2100, 800, id);
           painter.drawText(2100,1600 , this->Nom);
           painter.drawText(2100, 2400, this->Classe);
           painter.drawText(2100, 3200, this->Type);
           painter.drawText(2100, 4000, solde);
           painter.end();
           msgBox.setIcon(QMessageBox::Information);
           msgBox.setText("A pdf has been created.");
           msgBox.exec();
}
QSqlQueryModel * Comptes::afficherIdPDFComboBox(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT n_compte FROM comptes;");
    return model;
}
