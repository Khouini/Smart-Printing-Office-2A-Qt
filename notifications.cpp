#include "notifications.h"

notifications::notifications()
{

}
notifications::notifications(int operationInt, QString Nom)
{
    this->operationInt=operationInt;
    this->Nom=Nom;
}
void notifications::notificationsComptes(){
    QString text;
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    switch (operationInt) {
    case 0:  //ajout
        notifyIcon->setIcon(QIcon("D:/Documents/GitHub/Gestion-Fiance-Qt/img/valider.png"));
        notifyIcon->show();
        text = "Nouveau compte " + Nom + " Ajouté";
        notifyIcon->showMessage("Gestion des Comptes", text,QSystemTrayIcon::Information,15000);
    break;
    case 1: //Modification
        notifyIcon->setIcon(QIcon("D:/Documents/GitHub/Gestion-Fiance-Qt/img/modifier.png"));
        notifyIcon->show();
        text = "Compte " + Nom + " modifié";
        notifyIcon->showMessage("Gestion des Plats", text,QSystemTrayIcon::Information,15000);
    break;
    case 2: //Suppression
        notifyIcon->setIcon(QIcon("D:/Documents/GitHub/Gestion-Fiance-Qt/img/supprimer.png"));
        notifyIcon->show();
        text = "Compte " + Nom + " supprimé";
        notifyIcon->showMessage("Gestion des Plats", text,QSystemTrayIcon::Information,15000);
    break;

    }

}
