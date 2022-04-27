#ifndef PRODUIT_H
#define PRODUIT_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>


class produit
{
    QString nom_produit,reference_produit,type,marque,qte ;
    int id_produit;
public:
    //constructeurs
    produit(){}
  produit(int,QString,QString,QString,QString,QString);
//getters
QString getnom_produit(){return nom_produit ;}
QString getreference_produit(){return reference_produit ;}
int getid_produit(){return  id_produit;}
QString gettype(){return type ;}
QString getmarque(){return marque ;}
QString getqte(){return qte ;}
//setters
void setnom_produit(QString n){nom_produit=n;}
void setreference_produit(QString n){nom_produit=n;}
void setid_produit(int id_produit) {this->id_produit=id_produit;}
void settype(QString n){type=n;}
void setmarque(QString n){marque=n;}
void setqte(QString n){qte=n;}
//fonctionnalités de base relatives
bool ajouter();
bool alert();
QSqlQueryModel * afficher();
bool supprimer(int);
bool modifier(int);
//bool rechercher_id(int);
QSqlQueryModel * trie_produitN();
QSqlQueryModel * trie_produitQ();
QSqlQueryModel * recherche(QString);
void printPDF_produit() ;
void save(int, QString ,QString, QString,QString,QString ) ;
QString load() ;


};

#endif // PRODUIT_H
