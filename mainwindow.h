#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include "connection.h"
#include "QSqlQuery"
#include <QSqlError>
#include "login.h"
#include "mailing.h"
#include "comptes.h"
#include "gestioncommandes.h"
#include "historique.h"
#include "mailing.h"
#include "notifications.h"
#include <QIntValidator>
#include <QDebug>
#include <QTextStream>
#include <QUrl>
#include <QDesktopServices>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pushButtonSeConnecter_clicked();

    void on_pushButton_ENR_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_supp_up_clicked();

    void on_pushButtonRetour_clicked();

    void on_pushButtonRetourMPrincipale_clicked();

    void on_pushButtonmdpoubliee_clicked();

    void on_pushButton_Ajouter_clicked();

    void on_pushButton_Supprimer_clicked();

    void on_pushButton_Modifier_clicked();

    void on_pushButton_Chercher_clicked();

    void on_pushButton_Trier_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_Chercher_2_clicked();

    void on_tableViewComptes_activated(const QModelIndex &index);

    void on_pushButton_actualier_2_clicked();

    void on_pushButton_valider_etablissement_clicked();

    void on_pushButton_afficher_PJ_clicked();


    void on_tableViewCommande1_activated(const QModelIndex &index);

    void on_pushButton_Trier_2_clicked();

    void on_pushButton_Chercher_3_clicked();

    void on_pushButton_Trier_3_clicked();

    void on_pushButton_Chercher_4_clicked();

    void on_pushButton_actualier_3_clicked();

    void on_pushButton_valider_compta_clicked();

    void on_tableViewCommandes_2_activated(const QModelIndex &index);

    void on_pushButtonActualiserHistorique_clicked();

    void on_pushButton_clicked();

    void on_pushButton_afficher_pdf_clicked();

    void on_pushButton_envoyer_clicked();

    void on_pushButton_actualiser_chat_clicked();

    void on_pushButton_send_mail_clicked();

    void on_pushButton_mail_pj_clicked();

    void on_pushButton_GF_clicked();

    void on_pushButton_RPGF_clicked();

    void on_pushButton_RMPF_clicked();

private:
    Ui::MainWindow *ui;
    login L;
    Comptes Cmpt;
    GestionCommandes GC1;
    Historique H;
    QString role;

};
#endif // MAINWINDOW_H
