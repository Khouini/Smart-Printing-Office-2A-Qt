#include "gestioncommandes.h"

GestionCommandes::GestionCommandes(){

}
GestionCommandes::GestionCommandes(int id_compte, int id_commande){
    this->id_compte=id_compte;
    this->id_commande=id_commande;
}
QSqlQueryModel * GestionCommandes::afficherCommandes1(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT commandes.id_commande, commandes.PJ, commandes.TOTAL , comptes.N_compte, comptes.nom_compte, comptes.type_compte, comptes.solde_compte FROM commandes JOIN comptes ON commandes.n_compte = comptes.n_compte;");
    return model;
}
QSqlQueryModel * GestionCommandes::afficherCommandes2(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT commandes.id_commande, comptes.N_compte, comptes.nom_compte, comptes.type_compte, comptes.solde_compte FROM commandes JOIN comptes ON commandes.n_compte = comptes.n_compte;");
    return model;
}
QSqlQueryModel * GestionCommandes::afficherComboBoxCommandes(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT id_commande FROM commandes;");
    return model;
}
QSqlQueryModel * GestionCommandes::afficherComboBoxCompte(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT n_compte FROM comptes;");
    return model;
}
QSqlQueryModel * GestionCommandes::afficherComboBoxCompte2(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select n_compte from commandes;");
    return model;
}
bool GestionCommandes::EtablirCompte(){
    QSqlQuery query;
    query.prepare("UPDATE Commandes set N_Compte = :idCompte  WHERE id_commande = :idCommande;");
    query.bindValue(":idCompte", id_compte);
    query.bindValue(":idCommande", id_commande);
    return query.exec();
}
QSqlQueryModel * GestionCommandes::trierCommandes1(QString type_tri, QString tri_par){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT commandes.id_commande, commandes.PJ, comptes.N_compte, comptes.nom_compte, comptes.type_compte, comptes.solde_compte FROM commandes JOIN comptes ON commandes.n_compte = comptes.n_compte order by "+tri_par+" "+type_tri+" ");
    return model;
}
QSqlQueryModel * GestionCommandes::recherche1(QString rech){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT commandes.id_commande, commandes.PJ, comptes.N_compte, comptes.nom_compte, comptes.type_compte, comptes.solde_compte FROM commandes JOIN comptes ON commandes.n_compte = comptes.n_compte where (commandes.ID_COMMANDE) LIKE '%"+rech+"%' OR (comptes.N_COMPTE) LIKE '%"+rech+"%' OR (comptes.NOM_COMPTE) LIKE '%"+rech+"%' OR (comptes.CLASSE_COMPTE) LIKE '%"+rech+"%' OR (comptes.TYPE_COMPTE) LIKE '%"+rech+"%' OR (comptes.SOLDE_COMPTE) LIKE '%"+rech+"%' ");
    return model;
}
QSqlQueryModel * GestionCommandes::trierCommandes2(QString type_tri, QString tri_par){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT commandes.id_commande,comptes.N_compte, comptes.nom_compte, comptes.type_compte, comptes.solde_compte FROM commandes JOIN comptes ON commandes.n_compte = comptes.n_compte order by "+tri_par+" "+type_tri+" ");
    return model;
}
QSqlQueryModel * GestionCommandes::recherche2(QString rech){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT commandes.id_commande,comptes.N_compte, comptes.nom_compte, comptes.type_compte, comptes.solde_compte FROM commandes JOIN comptes ON commandes.n_compte = comptes.n_compte where (commandes.ID_COMMANDE) LIKE '%"+rech+"%' OR (comptes.NOM_COMPTE) LIKE '%"+rech+"%' OR (comptes.CLASSE_COMPTE) LIKE '%"+rech+"%' OR (comptes.TYPE_COMPTE) LIKE '%"+rech+"%' OR (comptes.SOLDE_COMPTE) LIKE '%"+rech+"%' ");
    return model;
}
QSqlQueryModel * GestionCommandes::afficherComboBoxCodePromo(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select code from codepromo;");
    return model;
}
