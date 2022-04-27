#include "mainwindow.h"
#include "ui_mainwindow.h"
#define NOM_RX "^([a-z]*|[A-Z]*)+$"
#include <QQuickItem>
#include <QDesktopServices>
QRegExp rxNom(NOM_RX);

using namespace qrcodegen;
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Chatbox
    //end chatbox
    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEdit_Username->setText("");
    ui->lineEdit_Password->setText("");
    ui->lineEdit_Username_mdp_oublie->setText("");
    ui->tableViewUP->setModel(L.Afficher());
    ui->tableViewComptes->setModel(Cmpt.afficher());
    ui->tableViewCommande1->setModel(GC1.afficherCommandes1());
    ui->tableViewCommandes_2->setModel(GC1.afficherCommandes2());
    ui->comboBox_Commandes_id->setModel(GC1.afficherComboBoxCommandes());
    ui->comboBox_codepromoid->setModel(GC1.afficherComboBoxCommandes());
    ui->comboBox_codepromo->setModel(GC1.afficherComboBoxCodePromo());
    ui->comboBox_compte_id->setModel(GC1.afficherComboBoxCompte());
    ui->comboBox_n_compte->setModel(GC1.afficherComboBoxCompte2());
    ui->comboBox_pdf_id->setModel(Cmpt.afficherIdPDFComboBox());
    ui->lineEdit_Numero_Compte->setValidator(new QIntValidator (0, 999, this));
    ui->lineEdit_Suppression_ID->setValidator(new QIntValidator (0, 999, this));
    ui->lineEdit_Nom_Compte->setValidator(new QRegExpValidator(QRegExp("[A-z]*")));
    ui->lineEdit_Classe_Compte->setValidator(new QRegExpValidator(QRegExp("[A-z]*")));
    ui->lineEdit_Recherche->setValidator(new QRegExpValidator(QRegExp("[A-z]*")));
    ui->tableViewHistorique->setModel(H.Afficher());
    //Wahchi
    ui->lineEdit_prenomC->setValidator(new QRegExpValidator(QRegExp("[A-z]*"))) ;
    ui->lineEdit_nomC->setValidator(new QRegExpValidator(QRegExp("[A-z]*"))) ;
    ui->lineEdit_emailC->setValidator(new QRegExpValidator(QRegExp("[a-z]{1,10}@[a-z]{1,10}\\.[a-z]{1,4}"))) ;
    ui->lineEdit_idC->setValidator(new QIntValidator(0,9999,this));
    ui->lineEdit_cinC->setValidator(new QIntValidator(0,19999999,this));
    ui->tableViewC->setModel(Etmp.afficher())  ;
    //end Wahchi
    //Begin Fahed
    ui->tableViewAffichage_F->setModel(FRN.afficher());
    ui->lineEdit_id_F->setValidator(new QIntValidator(0, 999999, this));
    ui->lineEdit_tel_F->setValidator(new QIntValidator(0, 99999999, this));
    ui->comboBoxSup_F->addItems(FRN.lister2());
    ui->lineEdit_email_F->setValidator(new QRegExpValidator(QRegExp("[a-z]{1,10}@[a-z]{1,10}\\.[a-z]{1,4}"))) ;
    ui->view_histo_F->setModel(HF.Afficher());
    //End fahed
    //Begin Majd
    ui->lineEdit_id_maint->setValidator(new QIntValidator(0,9999,this));
    ui->lineEdit_cin_maint->setValidator(new QIntValidator(0,9999,this));
    ui->lineEdit_num_maint->setValidator(new QIntValidator(0,9999,this));
    ui->lineEdit_idtache_maint->setValidator(new QIntValidator(0,9999,this));

    ui->lineEdit_nom_maint->setValidator(new QRegExpValidator ( QRegExp("[A-z]*") ));
    ui->lineEdit_prenom_maint->setValidator(new QRegExpValidator ( QRegExp("[A-z]*") ));
    ui->lineEdit_email_maint->setValidator(new QRegExpValidator ( QRegExp("[A-z]*") ));
    ui->lineEdit_Ps_maint->setValidator(new QRegExpValidator ( QRegExp("[A-z]*") ));

    ui->tableView_maint->setModel(Etmpi.afficher());
    //End Majd
    ui->lineEdit_cinA->setValidator(new QIntValidator(0,99999,this));
    ui->tableViewA->setModel(em.afficher());

    //MAKRAM
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
    ui->quickWidget->show();

    auto obj = ui->quickWidget->rootObject();
    connect(this, SIGNAL(setCenter(QVariant, QVariant)), obj, SLOT(setCenter(QVariant, QVariant)));
    connect(this, SIGNAL(addMarker(QVariant, QVariant)), obj, SLOT(addMarker(QVariant, QVariant)));

    emit setCenter(25.000, 50.000);
    emit addMarker(25.000, 50.000);





    //*******

  ui->tableViewb->setModel(pro.afficher())  ;//afficher
    ui->lineEdit_idb->setValidator(new QIntValidator(0,99999,this));
    QRegExpValidator*valiNom= new QRegExpValidator(rxNom,this);
    ui->lineEdit_nomb->setValidator(valiNom);//nomajoutproduit//

    ui->marqueb->setValidator(valiNom);
    ui->lineEdit_referenceb->setValidator(valiNom);

    ui->type->setValidator(valiNom);
    //END MAKRAM
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButtonSeConnecter_clicked()
{
    QString UserName = ui->lineEdit_Username->text();
    QString Password = ui->lineEdit_Password->text();
    QSqlQuery querry;
    querry.prepare("SELECT TYPE_USER, USERNAME FROM USERS WHERE USERNAME = '"+UserName+"' AND PASSWORD_USER = '"+Password+"'");
    //querry.bindValue(":username", UserName);
    //querry.bindValue(":password", Password);
    if (querry.exec()){
            int counter = 0;
            while (querry.next()){
                counter++;
                role = querry.value(0).toString();
                nickname = querry.value(1).toString();
            }
            ui->lineEditidNickname->setText(nickname);
            //Affichage chat
            QString date;
            QString Conversation = ui->lineEdit_Conversation->text();
            QString nickname, msgForTextEdit, text;
            QSqlQuery querySelect;
            querySelect.prepare("select  nickname, msg, TO_CHAR(date_sent, 'dy HH24:MI') from CHATBOX where conversation like "+Conversation+" order by date_sent;");
            if (querySelect.exec()){
                ui->textEdit->clear();
                while (querySelect.next()){
                    nickname = querySelect.value(0).toString();
                    msgForTextEdit = querySelect.value(1).toString();
                    date = querySelect.value(2).toString();
                    text = date + "    " +  nickname + ": " + msgForTextEdit;
                    ui->textEdit->append(text);
                }
            }else{
                QMessageBox::critical(this, tr("Error::"), querySelect.lastError().text());
            }
            // end affichage chat
            if (counter<1)
                QMessageBox::critical(this, tr("Error::"), "Compte n'existe pas");


            if (counter==1){
                QMessageBox::information(nullptr, QObject::tr("Database Open"),
                                          QObject::tr("Connecté"),
                                          QMessageBox::Ok
                                          );
                if (role=="ADMIN"){
                    ui->stackedWidget->setCurrentIndex(1);
                }else if (role=="FINANCE"){
                    ui->stackedWidget->setCurrentIndex(3);
                }else if (role=="CLIENTS"){
                    ui->stackedWidget->setCurrentIndex(4);
                }else if (role=="FOURNISSEURS"){
                    ui->stackedWidget->setCurrentIndex(5);
                }else if (role=="MAINTENANCE"){
                    ui->stackedWidget->setCurrentIndex(6);
                }else if (role=="EMOPLYEE"){
                    ui->stackedWidget->setCurrentIndex(7);
                }else if (role=="STOCK"){
                    ui->stackedWidget->setCurrentIndex(8);
                }

            }
            if (counter >1)
                QMessageBox::critical(this, tr("Error::"), "Duplicate");

        }else{
            QMessageBox::critical(this, tr("Error::"), querry.lastError().text());
        }
}

void MainWindow::on_pushButton_ENR_clicked()
{

    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_14_clicked()
{
    QString username = ui->lineEdit_Username_UP->text();
    QString mdp = ui->lineEdit_MDP_UP->text();
    QString email = ui->lineEdit_email_UP->text();
    QString role = ui->lineEdit_role_up->text();
    QSqlQuery querry;
    querry.prepare("insert into USERS values (USERS_SEQ.nextval, '"+role+"', '"+username+"', '"+mdp+"', '"+email+"')");
    if (querry.exec()){
        ui->tableViewUP->setModel(L.Afficher());
        QMessageBox::information(nullptr, QObject::tr("Database Open"),
                                  QObject::tr("Compte enregistré"),
                                  QMessageBox::Ok
                                  );
    }else{
        QMessageBox::critical(this, tr("Error::"), querry.lastError().text());
    }
}

void MainWindow::on_pushButton_supp_up_clicked()
{
    QString ID = ui->lineEdit_Username_UP_sup->text();
    QSqlQuery querry;
    querry.prepare("delete from users where id_user = "+ID+" ");
    if (querry.exec()){
        ui->tableViewUP->setModel(L.Afficher());
        QMessageBox::information(nullptr, QObject::tr("Database Open"),
                                  QObject::tr("Compte supprimé"),
                                  QMessageBox::Ok
                                  );
    }else{
        QMessageBox::critical(this, tr("Error::"), querry.lastError().text());
    }
}

void MainWindow::on_pushButtonRetour_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButtonRetourMPrincipale_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEdit_Username->setText("");
    ui->lineEdit_Password->setText("");
    ui->lineEdit_Username_mdp_oublie->setText("");
}

void MainWindow::on_pushButtonmdpoubliee_clicked()
{
    QString val = ui->lineEdit_Username_mdp_oublie->text();
    QString comboBox = ui->comboBox->currentText();
    QString password, email, username;
    QSqlQuery querry;
    if (comboBox == "Username")
    querry.prepare("select PASSWORD_USER, username, email_user from users where username = '"+val+"' ");
    if (comboBox == "Email")
    querry.prepare("select PASSWORD_USER, username, email_user from users where email_user = '"+val+"' ");
    if (querry.exec()){
        int counter = 0;
        while (querry.next()){
            counter++;
            password  = querry.value(0).toString();
            username = querry.value(1).toString();
            email =  querry.value(2).toString();
        }
        if (counter<1)
            QMessageBox::critical(this, tr("Error::"), "Compte n'existe pas");

        if (counter==1)
        {
            QMessageBox::information(nullptr, QObject::tr("Database Open"),
                                      QObject::tr("Le compte existe"),
                                      QMessageBox::Ok
                                      );
            Mailing* mailing = new Mailing("testkhouini@gmail.com", "Trunks@2001", "smtp.gmail.com", 465);
            QString Subject = "Récupération mot de passe";
            QString Message = "Mr " + username + " Votre mot de passe est " + password ;
            mailing->sendMail("testkhouini@gmail.com", email, Subject ,Message);
            QMessageBox::information(nullptr, QObject::tr("Database Open"),
                                      QObject::tr("Mail enovoyé"),
                                      QMessageBox::Ok
                                      );
        }
        if (counter >1)
            QMessageBox::critical(this, tr("Error::"), "Duplicate");
    }else{
        QMessageBox::critical(this, tr("Error::"), querry.lastError().text());
    }

}
void MainWindow::on_pushButton_Ajouter_clicked()
{
    QString Type;
    int Numero = ui->lineEdit_Numero_Compte->text().toInt();
    QString Nom = ui->lineEdit_Nom_Compte->text();
    QString Classe = ui->lineEdit_Classe_Compte->text();
    float solde= ui->lineEdit_Solde->text().toFloat();
    if (ui->radioButton_Type_Actif->isChecked()){
        Type = "Actif";
    }
    if (ui->radioButton_Type_Passif->isChecked()){
        Type = "Passif";
    }
    Comptes C(Numero, Nom, Classe, Type, solde);
    bool test = C.ajouter();

    if (test){

        ui->tableViewComptes->setModel(Cmpt.afficher());
        ui->comboBox_compte_id->setModel(GC1.afficherComboBoxCompte());
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("Ajout effectué"),
                              QMessageBox::Ok
                              );
        //Notification
        notifications N(0, Nom);
        N.notificationsComptes();
        //Historique
        QString operation = "Ajout";
        Historique h(operation, Numero, Nom);
        h.Ajouter();
        ui->tableViewHistorique->setModel(H.Afficher());
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Ajouter non effectué"),
                              QMessageBox::Cancel
                              );
    }
}

void MainWindow::on_pushButton_Supprimer_clicked()
{
    int id = ui->lineEdit_Suppression_ID->text().toInt();
    QString Nom = ui->lineEdit_Nom_Compte->text();
    bool test = Cmpt.supprimer(id);
    if (test){

        ui->tableViewComptes->setModel(Cmpt.afficher());
        ui->comboBox_compte_id->setModel(GC1.afficherComboBoxCompte());
        ui->tableViewHistorique->setModel(H.Afficher());
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("Suppression effectué"),
                              QMessageBox::Ok
                              );
        //Notification
        notifications N(2, Nom);
        N.notificationsComptes();
        //Historique
        QString operation = "Suppression";
        Historique h(operation, id, Nom);
        h.Ajouter();
        ui->tableViewHistorique->setModel(H.Afficher());
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Suppression non effectué"),
                              QMessageBox::Cancel
                              );
    }
}

void MainWindow::on_pushButton_Modifier_clicked()
{
    QString Type;
    int Numero = ui->lineEdit_Numero_Compte->text().toInt();
    QString Nom = ui->lineEdit_Nom_Compte->text();
    QString Classe = ui->lineEdit_Classe_Compte->text();
    float solde= ui->lineEdit_Solde->text().toFloat();
    if (ui->radioButton_Type_Actif->isChecked()){
        Type = "Actif";
    }
    if (ui->radioButton_Type_Passif->isChecked()){
    Type = "Passif";
    }
    Comptes C(Numero, Nom, Classe, Type, solde);
    bool test = C.modifier();

    if (test){
        ui->tableViewComptes->setModel(Cmpt.afficher());
        ui->comboBox_compte_id->setModel(GC1.afficherComboBoxCompte());
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("Modification effectué"),
                              QMessageBox::Ok
                              );
        //Notification
        notifications N(1, Nom);
        N.notificationsComptes();
        //Historique
        QString operation = "Modification";
        Historique h(operation, Numero, Nom);
        h.Ajouter();
        ui->tableViewHistorique->setModel(H.Afficher());

    }else{
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Modification non effectué"),
                              QMessageBox::Cancel
                              );
    }
}

void MainWindow::on_pushButton_Chercher_clicked()
{
    QString rech_field = ui->lineEdit_Recherche->text();
    ui->tableViewComptes->setModel(Cmpt.recherche(rech_field));
}

void MainWindow::on_pushButton_Trier_clicked()
{
    QString type_of_tri;
    QString tri_par;
    if (ui->radioButton_Tri_Asc->isChecked()){
        type_of_tri = "asc";
    }
    if (ui->radioButton_Tri_Desc->isChecked()){
        type_of_tri = "desc";
    }
    tri_par = ui->comboBox_Tri->currentText();
    ui->tableViewComptes->setModel(Cmpt.trier(type_of_tri, tri_par));

}

void MainWindow::on_pushButton_2_clicked()
{
    ui->tableViewComptes->setModel(Cmpt.afficher());

}

void MainWindow::on_pushButton_Chercher_2_clicked()
{
    QString rech_field = ui->lineEdit_ID_RECH_2->text();
    ui->tableViewComptes->setModel(Cmpt.recherche(rech_field));
}

void MainWindow::on_tableViewComptes_activated(const QModelIndex &index)
{
    QString val = ui->tableViewComptes->model()->data(index).toString();
    QSqlQuery query;
    query.prepare("select * from Comptes where (N_COMPTE) LIKE "+val+" ");
    if (query.exec()){
        while (query.next()){
            ui->lineEdit_Numero_Compte->setText(query.value(0).toString());
            ui->comboBox_pdf_id->setCurrentText(query.value(0).toString());
            ui->lineEdit_Suppression_ID->setText(query.value(0).toString());
            ui->lineEdit_Nom_Compte->setText(query.value(1).toString());
            ui->lineEdit_Classe_Compte->setText(query.value(2).toString());
            ui->lineEdit_Solde->setText(query.value(4).toString());
            if ((query.value(3).toString()) == "Actif"){
                ui->radioButton_Type_Actif->setChecked(1);
            }
            if ((query.value(3).toString()) == "Passif"){
                ui->radioButton_Type_Passif->setChecked(1);
            }
        }
    }else{
        QMessageBox::critical(this, tr("Error::"), query.lastError().text());
    }
}

void MainWindow::on_pushButton_actualier_2_clicked()
{
    ui->tableViewCommande1->setModel(GC1.afficherCommandes1());
    ui->comboBox_Commandes_id->setModel(GC1.afficherComboBoxCommandes());
    ui->comboBox_compte_id->setModel(GC1.afficherComboBoxCompte());
    ui->comboBox_pdf_id->setModel(Cmpt.afficherIdPDFComboBox());
    ui->comboBox_codepromoid->setModel(GC1.afficherComboBoxCommandes());
    ui->comboBox_codepromo->setModel(GC1.afficherComboBoxCodePromo());
}

void MainWindow::on_pushButton_valider_etablissement_clicked()
{
    int id_compte = ui->comboBox_compte_id->currentText().toUInt();
    int id_commande = ui->comboBox_Commandes_id->currentText().toInt();
    GestionCommandes GC(id_compte, id_commande);
    bool test = GC.EtablirCompte();

    if (test){
        ui->tableViewCommande1->setModel(GC1.afficherCommandes1());
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("etablir effectué"),
                              QMessageBox::Ok
                              );
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("etablir non effectué"),
                              QMessageBox::Cancel
                              );
    }
}

void MainWindow::on_pushButton_afficher_PJ_clicked()
{
    QString val = ui->lineEdit_id_commande->text();
    QSqlQuery query;
    query.prepare("select PJ from Commandes where (id_commande) LIKE "+val+" ");
    QString fichier_PJ;
    QString X;
    if (query.exec()){
        while (query.next()){
            fichier_PJ = query.value(0).toString();
            X = "D:\\Documents\\GitHub\\Gestion-Fiance-Qt\\PJ\\"+fichier_PJ ;
            QFile file (X);
            if(!file.open(QIODevice::ReadOnly)){
                QMessageBox::information(0, "info", file.errorString());
            }else{
                QTextStream in(&file);
                QMessageBox::about(this, tr("Piéce Justificative"), in.readAll());
            }
        }
    }else{
        QMessageBox::critical(this, tr("Error::"), query.lastError().text());
    }
}

void MainWindow::on_tableViewCommande1_activated(const QModelIndex &index)
{
    QString val = ui->tableViewCommande1->model()->data(index).toString();
    QSqlQuery query;
    query.prepare("select id_commande from commandes where (id_commande) LIKE "+val+" ");
    if (query.exec()){
        while (query.next()){
            ui->lineEdit_id_commande->setText(query.value(0).toString());
            ui->lineEdit_id_commande_email->setText(query.value(0).toString());
            ui->comboBox_Commandes_id->setCurrentText(query.value(0).toString());
        }
    }else{
        QMessageBox::critical(this, tr("Error::"), query.lastError().text());
    }
}

void MainWindow::on_pushButton_Trier_2_clicked()
{
    QString type_of_tri;
    QString tri_par;
    if (ui->radioButton_Tri_Asc_2->isChecked()){
        type_of_tri = "asc";
    }
    if (ui->radioButton_Tri_Desc_2->isChecked()){
        type_of_tri = "desc";
    }
    tri_par = ui->comboBox_Tri_2->currentText();
    ui->tableViewCommande1->setModel(GC1.trierCommandes1(type_of_tri, tri_par));
}

void MainWindow::on_pushButton_Chercher_3_clicked()
{
    QString rech_field = ui->lineEdit_Recherche_2->text();
    ui->tableViewCommande1->setModel(GC1.recherche1(rech_field));
}

void MainWindow::on_pushButton_Trier_3_clicked()
{
    QString type_of_tri;
    QString tri_par;
    if (ui->radioButton_Tri_Asc_3->isChecked()){
        type_of_tri = "asc";
    }
    if (ui->radioButton_Tri_Desc_3->isChecked()){
        type_of_tri = "desc";
    }
    tri_par = ui->comboBox_Tri_3->currentText();
    ui->tableViewCommandes_2->setModel(GC1.trierCommandes2(type_of_tri, tri_par));
}

void MainWindow::on_pushButton_Chercher_4_clicked()
{
    QString rech_field = ui->lineEdit_Recherche_3->text();
    ui->tableViewCommandes_2->setModel(GC1.recherche2(rech_field));
}

void MainWindow::on_pushButton_actualier_3_clicked()
{
    ui->tableViewCommandes_2->setModel(GC1.afficherCommandes2());
    ui->comboBox_n_compte->setModel(GC1.afficherComboBoxCompte2());
}

void MainWindow::on_pushButton_valider_compta_clicked()
{
    QString montant = ui->lineEdit_montant->text();
    QString nCompte = ui->comboBox_n_compte->currentText();
    QString compta_type;
    if (ui->radioButton_crediter->isChecked()){
        compta_type = "+";
    }
    if (ui->radioButton_debiter->isChecked()){
        compta_type = "-";
    }
    QSqlQuery query;
    query.prepare("update comptes set solde_compte = solde_compte "+compta_type+" "+montant+" where n_compte like "+nCompte+" ");
    if (query.exec()){
            ui->tableViewCommandes_2->setModel(GC1.afficherCommandes2());
            QMessageBox::information(nullptr, QObject::tr("Database is open"),
                                  QObject::tr("Manipulation effectué"),
                                  QMessageBox::Ok
                                  );
        }else{
        QMessageBox::critical(this, tr("Error::"), query.lastError().text());
    }
}

void MainWindow::on_tableViewCommandes_2_activated(const QModelIndex &index)
{
    QString val = ui->tableViewCommandes_2->model()->data(index).toString();
    QSqlQuery query;
    query.prepare("select n_compte from commandes where (n_compte) LIKE "+val+" ");
    if (query.exec()){
        while (query.next()){
            ui->comboBox_n_compte->setCurrentText(query.value(0).toString());
        }
    }else{
        QMessageBox::critical(this, tr("Error::"), query.lastError().text());
    }
}

void MainWindow::on_pushButtonActualiserHistorique_clicked()
{
    ui->tableViewHistorique->setModel(H.Afficher());
}

void MainWindow::on_pushButton_clicked()
{
    QString Nom, Classe, Type;
    int Numero, solde;
    QString val = ui->comboBox_pdf_id->currentText();
    QSqlQuery query;
    query.prepare("select * from comptes where (n_compte) LIKE "+val+" ");
    if (query.exec()){

        while (query.next()){
            Numero = query.value(0).toInt();
            Nom = query.value(1).toString();
            Classe = query.value(2).toString();
            Type = query.value(3).toString();
            solde = query.value(4).toInt();
        }
    }else{
        QMessageBox::critical(this, tr("Error::"), query.lastError().text());
    }
    Comptes C(Numero, Nom, Classe, Type, solde);

    C.printPDF_comptes() ;

}

void MainWindow::on_pushButton_afficher_pdf_clicked()
{
    QString link="file:///D:/Documents/GitHub/IntegrationQt/PDF/comptes.pdf";
            QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_pushButton_envoyer_clicked()
{
    QString nickname = ui->lineEditidNickname->text();
    QString Conversation = ui->lineEdit_Conversation->text();
    QString message_sent = ui->lineEdit_massage->text();
    QSqlQuery query;
    query.prepare("insert into CHATBOX values ('"+nickname+"', "+Conversation+", CHATBOX_SEQ.nextval, '"+message_sent+"', sysdate); ");
    if (query.exec()){
            QString Conversation = ui->lineEdit_Conversation->text();
            QString nickname, msgForTextEdit, text;
            QSqlQuery querySelect;
            QString date;
            querySelect.prepare("select  nickname, msg, TO_CHAR(date_sent, 'dy HH24:MI') from CHATBOX where conversation like "+Conversation+" order by date_sent;");
            if (querySelect.exec()){
                ui->textEdit->clear();
                while (querySelect.next()){
                    nickname = querySelect.value(0).toString();
                    msgForTextEdit = querySelect.value(1).toString();
                    date = querySelect.value(2).toString();
                    text = date + "    " +  nickname + ": " + msgForTextEdit;
                    ui->textEdit->append(text);
                }
            }else{
                QMessageBox::critical(this, tr("Error::"), querySelect.lastError().text());
            }
        }else{
        QMessageBox::critical(this, tr("Error::"), query.lastError().text());
    }

}

void MainWindow::on_pushButton_actualiser_chat_clicked()
{
    QString date;
    QString Conversation = ui->lineEdit_Conversation->text();
    QString nickname, msgForTextEdit, text;
    QSqlQuery querySelect;
    querySelect.prepare("select  nickname, msg, TO_CHAR(date_sent, 'dy HH24:MI') from CHATBOX where conversation like "+Conversation+" order by date_sent;");
    if (querySelect.exec()){
        ui->textEdit->clear();
        while (querySelect.next()){
            nickname = querySelect.value(0).toString();
            msgForTextEdit = querySelect.value(1).toString();
            date = querySelect.value(2).toString();
            text = date + "    " +  nickname + ": " + msgForTextEdit;
            ui->textEdit->append(text);
        }
    }else{
        QMessageBox::critical(this, tr("Error::"), querySelect.lastError().text());
    }
}

void MainWindow::on_pushButton_send_mail_clicked()
{
    QMessageBox::information(nullptr, QObject::tr("STMP is open"),
                          QObject::tr("Message envoyé"),
                          QMessageBox::Ok
                          );
    Mailing* mailing = new Mailing("testkhouini@gmail.com", "Trunks@2001", "smtp.gmail.com", 465);
    QString adresse = ui->lineEdit_adresse_dest->text();
    QString Subject = ui->lineEdit_subject->text();
    QString Message = ui->textEdit_message_email->toPlainText();
    mailing->sendMail("testkhouini@gmail.com", adresse, Subject ,Message);
}

void MainWindow::on_pushButton_mail_pj_clicked()
{
    QString txt;
    QString val = ui->lineEdit_id_commande_email->text();
    QSqlQuery query;
    query.prepare("select PJ from Commandes where (id_commande) LIKE "+val+" ");
    QString fichier_PJ;
    QString X;
    if (query.exec()){
        while (query.next()){
            fichier_PJ = query.value(0).toString();
            X = "D:\\Documents\\GitHub\\Gestion-Fiance-Qt\\PJ\\"+fichier_PJ ;
            QFile file (X);
            if(!file.open(QIODevice::ReadOnly)){
                QMessageBox::information(0, "info", file.errorString());
            }else{
                QTextStream in(&file);
                txt = in.readAll();

            }
        }
    }else{
        QMessageBox::critical(this, tr("Error::"), query.lastError().text());
    }
    Mailing* mailing = new Mailing("testkhouini@gmail.com", "Trunks@2001", "smtp.gmail.com", 465);
    QString adresse = ui->lineEditMailClient->text();
    mailing->sendMail("testkhouini@gmail.com", adresse, "PJ" , txt);
    QMessageBox::information(nullptr, QObject::tr("STMP is open"),
                          QObject::tr("mail envoyé"),
                          QMessageBox::Ok
                          );
}


void MainWindow::on_pushButton_GF_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_RPGF_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEdit_Username->setText("");
    ui->lineEdit_Password->setText("");
    ui->lineEdit_Username_mdp_oublie->setText("");
}

void MainWindow::on_pushButton_RMPF_clicked()
{
    if (role == "ADMIN"){
        ui->stackedWidget->setCurrentIndex(1);
    }else{
        QMessageBox::critical(this, tr("Error::"), "Vous n'etes pas un admin pour visionner cette page");
    }
}
//Begin Wahchi
void MainWindow::on_pushButton_ajouterC_clicked()
{
    // recuperation des info saisies
    int id_client=ui->lineEdit_idC->text().toInt();
    int cinn=ui->lineEdit_cinC->text().toInt();
    QString nom=ui->lineEdit_nomC->text();
    QString prenom=ui->lineEdit_prenomC->text();
    QString email=ui->lineEdit_emailC->text();
    QString sexe;
    QString type_client;
    QString operation=" ajout";
    if (ui->radioButtonHommeC->isChecked()){
        sexe = "Homme";
    }
    if (ui->radioButton_FemmeC->isChecked()){
        sexe = "Femme";
    }
    if (ui->radioButton_VIPC->isChecked()){
        type_client = "VIP";
    }
    if (ui->radioButton_FidelC->isChecked()){
        type_client = "Fidele";
    }
    if (ui->radioButton_passageeC->isChecked()){
        type_client = "Passager";
    }
    QString res1 = QString::number(id_client) ;
    QString res2 = QString::number(cinn) ;
    // objet client
    client C(nom,prenom,email,sexe,type_client,id_client,cinn);
    C.save(res1, res2, nom, prenom, email, sexe, type_client,operation);
    bool test= C.ajouterclient();
    // bool test2=C.controle_saisie_client(C) ;
    if(test)   // si requete executée
    {
        ui->tableViewC->setModel(Etmp.afficher());
        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("ajout effectué\n"
                                             "Click cancel to exit."),
                                QMessageBox::Cancel);
         }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("ajout NON effectué\n"
                                             "Click cancel to exit."),
                                QMessageBox::Cancel);

}
}

void MainWindow::on_pushButton_supprimerC_clicked()
{
    int id =ui->lineEdit_supprimer_C->text().toInt() ;
    bool test= Etmp.supprimer(id);
    int id_client=ui->lineEdit_idC->text().toInt();
    int cinn=ui->lineEdit_cinC->text().toInt();
    QString nom=ui->lineEdit_nomC->text();
    QString prenom=ui->lineEdit_prenomC->text();
    QString email=ui->lineEdit_emailC->text();
    QString sexe;
    QString type_client;
    QString operation=" Delete";
    QString res1 = QString::number(id_client) ;
    QString res2 = QString::number(cinn) ;
    client C(nom,prenom,email,sexe,type_client,id_client,cinn);
    C.save(res1, res2, nom, prenom, email, sexe, type_client,operation);

    if(test)   // si requete executée
    {
        ui->tableViewC->setModel(Etmp.afficher());
        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("suppression effectué\n"
                                             "Click cancel to exit."),
                                QMessageBox::Cancel);
         }
    else  {

        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("suppression NON effectué\n"
                                             "Click cancel to exit."),
                                QMessageBox::Cancel);

          }

}

void MainWindow::on_pushButton_modifierC_clicked()
{
    // recuperation des info saisies
    int id_client=ui->lineEdit_idC->text().toInt();
    int cinn=ui->lineEdit_cinC->text().toInt();
    QString nom=ui->lineEdit_nomC->text();
    QString prenom=ui->lineEdit_prenomC->text();
    QString email=ui->lineEdit_emailC->text();
    QString sexe;
    QString type_client;
    QString operation=" modification";
    if (ui->radioButtonHommeC->isChecked()){
        sexe = "Homme";
    }
    if (ui->radioButton_FemmeC->isChecked()){
        sexe = "Femme";
    }
    if (ui->radioButton_VIPC->isChecked()){
        type_client = "VIP";
    }
    if (ui->radioButton_FidelC->isChecked()){
        type_client = "Fidele";
    }
    if (ui->radioButton_passageeC->isChecked()){
        type_client = "Passager";
    }
    QString res1 = QString::number(id_client) ;
    QString res2 = QString::number(cinn) ;
    // objet client
    client C(nom,prenom,email,sexe,type_client,id_client,cinn);
    bool test= C.modifierclient();
    C.save(res1, res2, nom, prenom, email, sexe, type_client , operation);
    if(test)   // si requete executée
    {
        ui->tableViewC->setModel(Etmp.afficher());
        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("modification effectué\n"
                                             "Click cancel to exit."),
                                QMessageBox::Cancel);
         }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("modification NON effectué\n"
                                             "Click cancel to exit."),
                                QMessageBox::Cancel);

}
}

void MainWindow::on_pushButton_chercherC_clicked() //recherche
{
QString rech = ui->lineEdit_RC->text() ;
ui->tableViewC->setModel(Etmp.rechercher(rech)) ;
}

void MainWindow::on_pushButton_triC_clicked()  //tri
{
    QString type ;
    QString attribut ;
    if (ui->radioButton_6AC->isChecked())
    {  type="asc" ; }
    if (ui->radioButton_6DC->isChecked())
    {  type="desc" ; }

    attribut = ui->comboBoxC->currentText();
    ui->tableViewC->setModel(Etmp.tri(type,attribut))  ;



}


/* void MainWindow::on_tableViewC_2_activated(const QModelIndex &index) //table commande
{

} */

void MainWindow::on_tableViewC_activated(const QModelIndex &index) // selection par id
{
    QString id=ui->tableViewC->model()->data(index).toString() ;


    QSqlQuery query  ;

    query.prepare("select * from CLIENTS where (ID_CLIENT LIKE '"+id+"')") ;
    if (query.exec())
    {
        while (query.next()) {

            ui->lineEdit_idC->setText(query.value(0).toString()) ;
            ui->lineEdit_nomC->setText(query.value(1).toString()) ;
            ui->lineEdit_prenomC->setText(query.value(2).toString()) ;
            ui->lineEdit_emailC->setText(query.value(3).toString()) ;
            ui->lineEdit_cinC->setText(query.value(4).toString()) ;
            if ((query.value(5).toString() == "Homme"))
            { ui->radioButtonHommeC->setChecked(1) ;  }
            if ((query.value(5).toString() == "Femme"))
            { ui->radioButton_FemmeC->setChecked(1) ;  }
            if ((query.value(6).toString() == "VIP"))
            { ui->radioButton_VIPC->setChecked(1) ;  }
            if ((query.value(6).toString() == "Fidele"))
            { ui->radioButton_FidelC->setChecked(1) ;  }
            if ((query.value(6).toString() == "Passager"))
            { ui->radioButton_passageeC->setChecked(1) ;  }

        }
    }
        else {
             QMessageBox::critical(this,tr("error::"),query.lastError().text()) ;
               }

}

void MainWindow::on_pushButtonPDFC_clicked()  //button export pdf
{
   int cinn=ui->lineEdit_cinC->text().toInt();
   int id_client=ui->lineEdit_idC->text().toInt();
   QString email=ui->lineEdit_emailC->text();
   QString nom=ui->lineEdit_nomC->text();
   QString prenom=ui->lineEdit_prenomC->text();
   QString sexe;
   QString type_client;
   if (ui->radioButtonHommeC->isChecked()){
       sexe = "Homme";
   }
   if (ui->radioButton_FemmeC->isChecked()){
       sexe = "Femme";
   }
   if (ui->radioButton_VIPC->isChecked()){
       type_client = "VIP";
   }
   if (ui->radioButton_FidelC->isChecked()){
       type_client = "Fidele";
   }
   if (ui->radioButton_passageeC->isChecked()){
       type_client = "Passager";
   }
   client Etmp(nom,prenom,email,sexe,type_client,id_client,cinn);
   Etmp.printPDF_client() ;

}

void MainWindow::on_pushButton_theme1C_clicked()
{

    QFile styleSheetFile("D:/Documents/GitHub/IntegrationQt/stylesheet/Darkeum.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String (styleSheetFile.readAll());
    MainWindow::setStyleSheet(styleSheet);
}

void MainWindow::on_pushButton_theme2C_clicked()
{
    QFile styleSheetFile("D:/Documents/GitHub/IntegrationQt/stylesheet/Toolery.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String (styleSheetFile.readAll());
    MainWindow::setStyleSheet(styleSheet);
}

void MainWindow::on_pushButton_historiqueC_clicked()
{
    QString link="file:///D:/Documents/GitHub/IntegrationQt/Historique/hitoriqueClients.txt";
        QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_pushButton_ouvrirPDFC_clicked()
{
    QString link="file:///D:/Documents/GitHub/IntegrationQt/PDF/clients.pdf";
        QDesktopServices::openUrl(QUrl(link));
}

//End Wahchi

void MainWindow::on_pushButton_GC_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_pushButton_RPGF_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
        ui->lineEdit_Username->setText("");
        ui->lineEdit_Password->setText("");
        ui->lineEdit_Username_mdp_oublie->setText("");
}

void MainWindow::on_pushButton_RMPF_2_clicked()
{
    if (role == "ADMIN"){
            ui->stackedWidget->setCurrentIndex(1);
        }else{
            QMessageBox::critical(this, tr("Error::"), "Vous n'etes pas un admin pour visionner cette page");
        }
}
void MainWindow::on_pushButton_Ajouter_F_clicked()
{

    int id = ui->lineEdit_id_F->text().toInt();
    int num = ui->lineEdit_tel_F->text().toInt();
    QString email = ui->lineEdit_email_F->text();
    QString produit = ui->lineEdit_produit_F->text();
    QString date_arrivee = ui->lineEdit_email_2_F->text();
    QString nom = ui->lineEdit_nom_F->text();
    Fournisseurs F(id, num, email, produit, date_arrivee, nom);
    bool test = F.ajouter();

    if (test){


        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("Ajout effectué"),
                              QMessageBox::Ok
                              );
        QString operation="ajout";

              histo h(operation, id);
               h.Ajouter();
               ui->view_histo_F->setModel(HF.Afficher()); // refrechi el tableau
      ui->tableViewAffichage_F->setModel(FRN.afficher());
      ui->lineEdit_id_F->clear();
      ui->lineEdit_nom_F->clear();
      ui->lineEdit_tel_F->clear();
      ui->lineEdit_email_F->clear();
      ui->lineEdit_email_2_F->clear();
      ui->lineEdit_produit_F->clear();
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Ajouter non effectué"),
                              QMessageBox::Cancel
                              );
        ui->lineEdit_id_F->clear();
        ui->lineEdit_nom_F->clear();
        ui->lineEdit_tel_F->clear();
        ui->lineEdit_email_F->clear();
        ui->lineEdit_email_2_F->clear();
        ui->lineEdit_produit_F->clear();
    }
}

void MainWindow::on_pushButton_Supprimer_F_clicked()
{
    int id =ui->comboBoxSup_F->currentText().toInt();
   // int id = ui->lineEdit_id_suppression->text().toInt();
    bool test = FRN.supprimer(id);
    ui->view_histo_F->setModel(HF.Afficher());

    if (test){
        QString operation="suppression";
        histo h(operation, id);
                h.Ajouter();
                 ui->comboBoxSup_F->addItems(FRN.lister2());

        ui->tableViewAffichage_F->setModel(FRN.afficher());
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("Suppression effectué"),
                              QMessageBox::Ok
                              );
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Suppression non effectué"),
                              QMessageBox::Cancel
                              );
    }

}

void MainWindow::on_pushButton_Modifier_F_clicked()
{
    int id = ui->lineEdit_id_F->text().toInt();
    int num = ui->lineEdit_tel_F->text().toInt();
    QString email = ui->lineEdit_email_F->text();
    QString produit = ui->lineEdit_produit_F->text();
    QString date_arrivee = ui->lineEdit_email_2_F->text();
    QString nom = ui->lineEdit_nom_F->text();
    Fournisseurs F(id, num, email, produit, date_arrivee, nom);
    bool test = F.modifier();

    if (test){
        QString operation="modification";
        histo h(operation, id);
                h.Ajouter();
                 ui->view_histo_F->setModel(HF.Afficher());
        ui->tableViewAffichage_F->setModel(FRN.afficher());
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("Modification effectué"),
                              QMessageBox::Ok
                              );
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Modification non effectué"),
                              QMessageBox::Cancel
                              );
    }
}

void MainWindow::on_pushButton_F_clicked()
{
    ui->tableViewAffichage_F->setModel(FRN.trier());
}

void MainWindow::on_pushButton_Actualiser_F_clicked()
{
    ui->tableViewAffichage_F->setModel(FRN.afficher());
}

void MainWindow::on_pushButton_2_F_clicked()
{
    ui->tableViewAffichage_F->setModel(FRN.trierNom());
}


void MainWindow::on_pushButton_3_F_clicked()
{
        int id_fournisseur=ui->lineEdit_id_F->text().toInt();
        int tel=ui->lineEdit_tel_F->text().toInt();
        QString nom=ui->lineEdit_nom_F->text();
        QString email=ui->lineEdit_email_F->text();
        QString produit=ui->lineEdit_produit_F->text();
        QString date=ui->lineEdit_email_2_F->text();
       Fournisseurs F(id_fournisseur,tel,nom,email,produit,date);

       F.printPDF_employe();
}

void MainWindow::on_pushButton_4_F_clicked()
{
    //ui->stackedWidget_2->setCurrentIndex(1);
            QSqlQueryModel * model= new QSqlQueryModel();
            model->setQuery("select * from fournisseurs where id_fournisseur < 19999 ");
            float taille=model->rowCount();
            model->setQuery("select * from fournisseurs where id_fournisseur  between 19999 and 29999 ");
            float taillee=model->rowCount();
            model->setQuery("select * from fournisseurs where id_fournisseur >29999 ");
            float tailleee=model->rowCount();
            float total=taille+taillee+tailleee;
            QString a=QString("fournisseurs fidele . "+QString::number((taille*100)/total,'f',2)+"%" );
            QString b=QString("fournisseur non fidele .  "+QString::number((taillee*100)/total,'f',2)+"%" );
            QString c=QString("fournisseur retsekour ."+QString::number((tailleee*100)/total,'f',2)+"%" );
            QPieSeries *series = new QPieSeries();
            series->append(a,taille);
            series->append(b,taillee);
            series->append(c,tailleee);
            if (taille!=0)
            {QPieSlice *slice = series->slices().at(0);
                slice->setLabelVisible();
                slice->setPen(QPen());}
            if ( taillee!=0)
            {
                // Add label, explode and define brush for 2nd slice
                QPieSlice *slice1 = series->slices().at(1);
                //slice1->setExploded();
                slice1->setLabelVisible();
            }
            if(tailleee!=0)
            {
                // Add labels to rest of slices
                QPieSlice *slice2 = series->slices().at(2);
                //slice1->setExploded();
                slice2->setLabelVisible();
            }
            // Create the chart widget
            QChart *chart = new QChart();
            // Add data to chart with title and hide legend
            chart->addSeries(series);
            chart->setTitle("distribution fournisseurs :Nombre Des fournisseurs "+ QString::number(total));
            chart->legend()->hide();
            // Used to display the chart
            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->resize(1000,500);
            chartView->show();
}
void MainWindow::on_pushButton_chercher_F_clicked()
{
    QString rech_field = ui->lineEdit_nom_recherche_F->text();
    ui->tableViewAffichage_F->setModel(FRN.chercher(rech_field));

}
void MainWindow::on_pushButton_6_F_clicked()
{
    QString strStream;

                     QTextStream out(&strStream);

                     const int rowCount = ui->tableViewAffichage_F->model()->rowCount();
                     const int columnCount = ui->tableViewAffichage_F->model()->columnCount();
                     QString TT = QDateTime::currentDateTime().toString();
                     out <<"<html>\n"
                           "<head>\n"
                            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                         << "<title>ERP - COMmANDE LIST<title>\n "
                         << "</head>\n"
                         "<body bgcolor=#ffffff link=#5000A0>\n"
                            "<h1 style=\"text-align: center;\"><strong> "+TT+"</strong></h1>"
                            +"<img src=C:\\Users\\maato\\Desktop\\Nouveau%20dossier\\fahed.pdf />"
                            "<h1 style=\"text-align: center;\"><strong> *****LISTE DES  licence commerciale ***** </strong></h1>"


                         "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                           "</br> </br>";
                     // headers
                     out << "<thead><tr bgcolor=#d6e5ff>";
                     for (int column = 0; column < columnCount; column++)
                         if (!ui->tableViewAffichage_F->isColumnHidden(column))
                             out << QString("<th>%1</th>").arg(ui->tableViewAffichage_F->model()->headerData(column, Qt::Horizontal).toString());
                     out << "</tr></thead>\n";

                     // data table
                     for (int row = 0; row < rowCount; row++) {
                         out << "<tr>";
                         for (int column = 0; column < columnCount; column++) {
                             if (!ui->tableViewAffichage_F->isColumnHidden(column)) {
                                 QString data =ui->tableViewAffichage_F->model()->data(ui->tableViewAffichage_F->model()->index(row, column)).toString().simplified();
                                 out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                             }
                         }
                         out << "</tr>\n";
                     }
                     out <<  "</table>\n"
                         "</body>\n"
                         "</html>\n";

                     QTextDocument *document = new QTextDocument();
                     document->setHtml(strStream);

                     QPrinter printer;

                     QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
                     if (dialog->exec() == QDialog::Accepted) {
                         document->print(&printer);
                     }

                     delete document;
}
void MainWindow::on_pb_image_F_clicked()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString fileName =QFileDialog::getOpenFileName(this, tr("Open Images"), "C:/Users/maato/Desktop/Projet CRUD/ProjectFournisseurs", tr("Image Files (*.png *.jpg *.bmp)"));
//to select and show the picture
    if (!fileName.isEmpty())
    {
        QImage image(fileName);
            ui->label_pic_F->setPixmap(QPixmap::fromImage(image));
    }
}


void MainWindow::on_pushButton_RPGF_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
        ui->lineEdit_Username->setText("");
        ui->lineEdit_Password->setText("");
        ui->lineEdit_Username_mdp_oublie->setText("");
}

void MainWindow::on_pushButton_RMPF_3_clicked()
{
    if (role == "ADMIN"){
            ui->stackedWidget->setCurrentIndex(1);
        }else{
            QMessageBox::critical(this, tr("Error::"), "Vous n'etes pas un admin pour visionner cette page");
        }
}

void MainWindow::on_pushButton_GF_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}
//Begin Majd
void MainWindow::on_pushButton_ajouter_maint_clicked()
{
    int id=ui->lineEdit_id_maint->text().toInt();
    QString nom=ui->lineEdit_nom_maint->text();
    QString prenom=ui->lineEdit_prenom_maint->text();
    int cin=ui->lineEdit_cin_maint->text().toInt();
    int num=ui->lineEdit_num_maint->text().toInt();
    int idtache=ui->lineEdit_idtache_maint->text().toInt();
    QString EMAIL_EMPLOYEE=ui->lineEdit_email_maint->text();
    QString PASSWORD_EMPLOYEE=ui->lineEdit_Ps_maint->text();


    Techniciens T(id,nom,prenom,cin,num,idtache,EMAIL_EMPLOYEE,PASSWORD_EMPLOYEE);
    T.save(id,nom,prenom,cin,num,idtache,EMAIL_EMPLOYEE,PASSWORD_EMPLOYEE);
    bool test=T.ajouter();

    if(test)
    {
        ui->tableView_maint->setModel(Etmpi.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                              QObject::tr("Ajout non effectué.\n"
                                          "Click cancel to exit."), QMessageBox::Cancel);



}


//suppression

void MainWindow::on_pushButton_supp_maint_clicked()
{
    int id =ui->lineEdit_supp_maint->text().toInt();
    bool test=Etmpi.supprimer(id);

    if(test)
    {
        ui->tableView_maint->setModel(Etmpi.afficher());

        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Suppression effectuée\n"
                                             "Click cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                     QObject::tr("Suppression non effectuée.\n"
                                 "Click cancel to exit."), QMessageBox::Cancel);
    }

}




//modifier

void MainWindow::on_pushButton_Modifier_maint_clicked()
{
    int id=ui->lineEdit_id_maint->text().toInt();
    QString nom=ui->lineEdit_nom_maint->text();
    QString prenom=ui->lineEdit_prenom_maint->text();
    int cin=ui->lineEdit_cin_maint->text().toInt();
    int num=ui->lineEdit_num_maint->text().toInt();
    int idtache=ui->lineEdit_idtache_maint->text().toInt();
    QString EMAIL_EMPLOYEE=ui->lineEdit_email_maint->text();
    QString PASSWORD_EMPLOYEE=ui->lineEdit_Ps_maint->text();

    Techniciens T(id,nom,prenom,cin,num,idtache,EMAIL_EMPLOYEE,PASSWORD_EMPLOYEE);

    bool test=T.modifier();

    if(test)
    {
        ui->tableView_maint->setModel(Etmpi.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("modification effectué\n"
                                             "Click cancel to exit."), QMessageBox::Cancel);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                              QObject::tr("modification non effectué.\n"
                                          "Click cancel to exit."), QMessageBox::Cancel);
    }


}






//TRI ID
void MainWindow::on_radioButton_idTri_maint_clicked()
{
    ui->tableView_maint->setModel(Etmpi.tri_id());

}
//TRI NOM

void MainWindow::on_radioButton_nomTri_maint_clicked()
{
    ui->tableView_maint->setModel(Etmpi.tri_nom());

}

//recherche


void MainWindow::on_pushButton_rech_maint_clicked()
{

    QString rech= ui->lineEdit_rech_maint->text();
    ui->tableView_maint->setModel(Etmpi.recherche(rech));

}




//generer pdf


void MainWindow::on_pushButton_pdf_maint_clicked()
{
    int id=ui->lineEdit_id_maint->text().toInt();
    QString nom=ui->lineEdit_nom_maint->text();
    QString prenom=ui->lineEdit_prenom_maint->text();
    int cin=ui->lineEdit_cin_maint->text().toInt();
    int num=ui->lineEdit_num_maint->text().toInt();
    int idtache=ui->lineEdit_idtache_maint->text().toInt();
    QString PASSWORD_EMPLOYEE=ui->lineEdit_Ps_maint->text();
    QString EMAIL_EMPLOYEE=ui->lineEdit_email_maint->text();



    Techniciens T(id,nom,prenom,cin,num,idtache,PASSWORD_EMPLOYEE,EMAIL_EMPLOYEE);
    T.printPDF();
}





//qr code


void MainWindow::on_qrCode_clicked()
{
    int tabeq=ui->tableView_maint->currentIndex().row();
                   QVariant idd=ui->tableView_maint->model()->data(ui->tableView_maint->model()->index(tabeq,0));
                   QString id=idd.toString();
                  // QString code=idd.toSTring();
                   QSqlQuery qry;
                   qry.prepare("select * from EMPLOYEES where id_employee=:id");
                   qry.bindValue(":id",id);
                   qry.exec();

                   int num,cin,idtache;
                    QString idA, nom,prenom,password,email;//attributs


                  while(qry.next()){

                      idA=qry.value(0).toString();
                       nom=qry.value(1).toString();
                        prenom=qry.value(2).toString();
                       cin=qry.value(3).toInt();
                       num=qry.value(13).toInt();
                       idtache=qry.value(10).toInt();
                       password=qry.value(5).toString();
                       email=qry.value(4).toString();

                   }
                   id=QString(id);
                          id="ID_EMPLOYEE:\t" +idA+ "NOM_EMPLOYEE\t:" +nom+ "PRENOM_EMPLOYEE:\t" +prenom+ "CIN_EMPLOYEE:\t" +cin+ "TEL_EMPLOYEE:\t" +num+ "ID_TACHE:\t" +idtache+ "EMAIL_EMPLOYEE:\t" +email+ "PASSWORD_EMPLOYEE:\t" +password ;
                   QrCode qr = QrCode::encodeText(id.toUtf8().constData(), QrCode::Ecc::HIGH);

                   // Read the black & white pixels
                   QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
                   for (int y = 0; y < qr.getSize(); y++) {
                       for (int x = 0; x < qr.getSize(); x++) {
                           int color = qr.getModule(x, y);  // 0 for white, 1 for black

                           // You need to modify this part
                           if(color==0)
                               im.setPixel(x, y,qRgb(254, 254, 254));
                           else
                               im.setPixel(x, y,qRgb(0, 0, 0));
                       }
                   }
                   im=im.scaled(200,200);
                  ui->qr_code->setPixmap(QPixmap::fromImage(im));
}



//historique

void MainWindow::on_pushButton_historique_maint_clicked()
{
    QString link="file:///D:/Documents/GitHub/IntegrationQt/Historique/historiqueTechneciens.txt";
        QDesktopServices::openUrl(QUrl(link));

}




void MainWindow::on_QUITTER_maint_clicked()
{
    close();
}
//End Majd

void MainWindow::on_pushButton_GM_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_pushButton_RPGF_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
        ui->lineEdit_Username->setText("");
        ui->lineEdit_Password->setText("");
        ui->lineEdit_Username_mdp_oublie->setText("");
}

void MainWindow::on_pushButton_RMPF_4_clicked()
{
    if (role == "ADMIN"){
            ui->stackedWidget->setCurrentIndex(1);
        }else{
            QMessageBox::critical(this, tr("Error::"), "Vous n'etes pas un admin pour visionner cette page");
        }
}

void MainWindow::on_pushButton_APDFF_clicked()
{
    QString link="file:///D:/Documents/GitHub/IntegrationQt/PDF/fournisseurs.pdf";
        QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_pushButton_RetourPC22_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEdit_Username->setText("");
    ui->lineEdit_Password->setText("");
    ui->lineEdit_Username_mdp_oublie->setText("");
}

void MainWindow::on_pushButton_PDFMAINT_clicked()
{
    QString link="file:///D:/Documents/GitHub/IntegrationQt/PDF/maintenance.pdf";
        QDesktopServices::openUrl(QUrl(link));
}
void MainWindow::on_pushButton_modifierA_clicked()
{
    int cin=ui->lineEdit_cinA->text().toInt();
    QString nom=ui->lineEdit_nomA->text();
    QString prenom=ui->lineEdit_prenomA->text();
    QString adresse=ui->lineEdit_adresseA->text();
    QString email=ui->lineEdit_emailA->text();
    QString type;
    if(ui->radioButtonA->isChecked()){
        type = "standard";
    }
    if(ui->radioButton_2A->isChecked()){
        type = "technicien";
    }

    employe e(cin,nom,prenom,adresse,type,email);
    e.save(cin,nom,prenom,adresse,type,email);
    bool test;
    test=e.modifier();

    if(test)
    {
         ui->tableViewA->setModel(em.afficher());//ref
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("modification effectue\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("modification non effectue\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
void MainWindow::on_pushButton_ajouterA_clicked()
{
    int cin=ui->lineEdit_cinA->text().toInt();
    QString nom=ui->lineEdit_nomA->text();
    QString prenom=ui->lineEdit_prenomA->text();
    QString adresse=ui->lineEdit_adresseA->text();
    QString email=ui->lineEdit_emailA->text();
    QString type;
    if(ui->radioButtonA->isChecked()){
        type = "standard";
    }
    if(ui->radioButton_2A->isChecked()){
        type = "technicien";
    }
    employe e(cin,nom,prenom,adresse,type,email);
    e.save(cin,nom,prenom,adresse,type,email);
    bool test;
    test=e.ajouter();
    if(test)
    {
         ui->tableViewA->setModel(em.afficher());//ref
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectue\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectue\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_supprimerA_clicked()
{
    int cin=ui->lineEdit_cinsA->text().toInt();

    bool test;
    test=em.supprimer(cin);

    if(test)
    {
         ui->tableViewA->setModel(em.afficher());//ref
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Supression effectue\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Supression non effectue\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_2A_clicked()
{
    QString type_of_tri;
    QString tri_par;
    if(ui->radioButton_5A->isChecked()){
        type_of_tri = "asc";
    }
    if(ui->radioButton_6A->isChecked()){
        type_of_tri = "desc";
    }
    tri_par = ui->comboBoxA->currentText();
    ui->tableViewA->setModel(em.trier(type_of_tri, tri_par));
}

void MainWindow::on_pushButton_4A_clicked()
{
    QString rech = ui->lineEdit_2A->text() ;
    ui->tableViewA->setModel(em.rechercher(rech)) ;
}

void MainWindow::on_pushButtonA_clicked()
{
    if ("CLIENT20"  == ui->lineEdit_cin_3A->text()){
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("remise de 20% effectue\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);    }
    else if ("EMPLOYE50"  == ui->lineEdit_cin_3A->text()){
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("remise de 50% effectue\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else if ("ADMIN100"  == ui->lineEdit_cin_3A->text()){
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("remise de 100% effectue\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("remise non effectue\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

}



void MainWindow::on_pushButton_6A_clicked()
{
    int cin=ui->lineEdit_cinA->text().toInt();
    QString nom=ui->lineEdit_nomA->text();
    QString prenom=ui->lineEdit_prenomA->text();
    QString adresse=ui->lineEdit_adresseA->text();
    QString email=ui->lineEdit_emailA->text();
    QString type;
    if(ui->radioButtonA->isChecked()){
        type = "standard";
    }
    if(ui->radioButton_2A->isChecked()){
        type = "technicien";
    }
    employe e(cin,nom,prenom,adresse,type,email);
        e.printPDF_employe();
}

void MainWindow::on_pushButton_7A_clicked()
{
    QString link="file:///C:/Users/souay/OneDrive/Documents/untitled/test.pdf";
            QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_pushButton_5A_clicked()
{
    QString link="file:///C:/Users/souay/OneDrive/Documents/untitled/histo.txt";
            QDesktopServices::openUrl(QUrl(link));
}


void MainWindow::on_pushButton_RPGF_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
       ui->lineEdit_Username->setText("");
       ui->lineEdit_Password->setText("");
       ui->lineEdit_Username_mdp_oublie->setText("");

}

void MainWindow::on_pushButton_RMPF_5_clicked()
{

       if (role == "ADMIN"){
               ui->stackedWidget->setCurrentIndex(1);
           }else{
               QMessageBox::critical(this, tr("Error::"), "Vous n'etes pas un admin pour visionner cette page");
           }
}

void MainWindow::on_pushButton_GE_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}
// Debut Makram
void MainWindow::on_pushButton_10b_clicked()
{


    int id_produit=ui->lineEdit_idb->text().toInt();
    QString nom_produit=ui->lineEdit_nomb->text();
    QString reference_produit =ui ->lineEdit_referenceb->text();
     QString type =ui ->type->text();
      QString marqueb =ui ->marqueb->text();
       QString qteb =ui ->qteb->text();
produit p(id_produit,nom_produit,reference_produit,type,marqueb,qteb);
// fel fonction ajoutt
p.save(id_produit,nom_produit,reference_produit,type,marqueb,qteb);
bool test= p.ajouter();


if (test)
{
 //   QMessageBox msg;
 //   msg.setWindowTitle("Error");
 //   msg.setIcon(QMessageBox::Critical);
 //   msg.setText("Error: Something went wrong!");
 //   msg.exec();
    ui->tableViewb->setModel(pro.afficher());

QMessageBox::information(nullptr,QObject::tr("ok"),
                         QObject::tr("ajouter effectué\n"
                                     "Click cancel to exit."),
                        QMessageBox::Cancel);

}
else
    QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                             QObject::tr("ajouter NON effectué\n"
                                         "Click cancel to exit."),
                            QMessageBox::Cancel);




}

void MainWindow::on_stock_clicked()
{

        produit p;
     QString qnt=ui->qteb->text();
   //int qnt;
    bool test;
    QSqlQuery qry;

    qry.prepare("select qteb from produit  where  qteb = "+qnt+" ");
    if (qry.exec()){
        while (qry.next()){
            qnt = (qry.value(0).toInt());
            if (qnt > 10){
                test = true;
            }else{
                test = false;
            }
        }
    }
        QMessageBox msgbox;
        if (test){
                ui->tableViewb->setModel(pro.afficher());
                QMessageBox::information(nullptr, QObject::tr("***alert stock***"),
                                      QObject::tr("Ce Produit est encore en stock"),
                                      QMessageBox::Ok
                                      );
            }else{
                QMessageBox::critical(nullptr, QObject::tr("***alert stock***"),
                                      QObject::tr("Ce Produit nest plus en stock (stock<10)"),
                                      QMessageBox::Cancel
                                      );
            }
    }









/*

    //QString test2="55";
     //int id_produit=ui->lineEdit_idb->text().toInt();
    produit p;
      bool test= p.alert();
    if (test)
    {
        QMessageBox msg;
      // msg.setWindowTitle("Error");
       // msg.setIcon(QMessageBox::Critical);
       // msg.setText("Error: Something went wrong!");
       //msg.exec();
        ui->tableViewb->setModel(pro.afficher());
    QMessageBox::information(nullptr,QObject::tr("ok"),
                             QObject::tr("stock effectué\n"
                                         "Click cancel to exit."),
                            QMessageBox::Cancel);



}
    else
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("stock NON effectué\n"
                                             "Click cancel to exit."),
                                QMessageBox::Cancel);
                                */







void MainWindow::on_pushButton_supprimerb_clicked()
{
    int id =ui->lineEdit_supprimer_3b->text().toInt() ;
    bool test= pro.supprimer(id);
    if(test)   // si requete executée
    {
        ui->tableViewb->setModel(pro.afficher());

        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("suppression effectué\n"
                                             "Click cancel to exit."),
                                QMessageBox::Cancel);
         }
    else  {

        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("suppression NON effectué\n"
                                             "Click cancel to exit."),
                                QMessageBox::Cancel);

          }
}



void MainWindow::on_pushButton_11b_clicked()
{
    {

        //

        int id_produit=ui->lineEdit_idb->text().toInt();
        QString nom_produit=ui->lineEdit_nomb->text();
        QString reference_produit =ui ->lineEdit_referenceb->text();
         QString type =ui ->type->text();
          QString marqueb =ui ->marqueb->text();
          QString qteb =ui ->qteb->text();
          produit p(id_produit,nom_produit,reference_produit,type,marqueb,qteb);



      bool test=p.modifier(id_produit);
      if(test)
    {
         ui->tableViewb->setModel(pro.afficher());
      //refresh
    QMessageBox::information(nullptr, QObject::tr("modifier une agence"),
                      QObject::tr("Agence modifié.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

    }
      else
          QMessageBox::critical(nullptr, QObject::tr("modifier une agence"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

    }

}

void MainWindow::on_radioButton_TRInProdb_clicked()
{

         ui->tableViewb->setModel((pro.trie_produitN()));

}

void MainWindow::on_radioButton_TRIqProdb_clicked()
{
  ui->tableViewb->setModel(pro.trie_produitQ());
}




void MainWindow::on_pushButton_3b_clicked()
{
    QString rech= ui->lineEdit_7b->text();
    ui->tableViewb->setModel(pro.recherche(rech));

}


void MainWindow::on_pushButton_4_clicked()
{


        int id_produit=ui->lineEdit_idb->text().toInt();
        QString nom_produit=ui->lineEdit_nomb->text();
        QString reference_produit =ui ->lineEdit_referenceb->text();
         QString type =ui ->type->text();
          QString marqueb =ui ->marqueb->text();
           QString qteb =ui ->qteb->text();
       produit p(id_produit,nom_produit,reference_produit,type,marqueb,qteb);
    p.printPDF_produit();
}



void MainWindow::on_tableViewb_activated(const QModelIndex &index)
{



        QSqlQuery query  ;
       QString id_produit=ui->tableViewb->model()->data(index).toString() ;
        query.prepare("select * from produit where (id_produit LIKE '"+id_produit+"')") ;
        if (query.exec())
        {
            while (query.next()) {

                ui->lineEdit_idb->setText(query.value(0).toString()) ;
                ui->lineEdit_nomb->setText(query.value(1).toString()) ;
                ui->lineEdit_referenceb->setText(query.value(2).toString()) ;
                ui->type->setText(query.value(3).toString()) ;
                ui->marqueb->setText(query.value(4).toString()) ;
                ui->qteb->setText(query.value(5).toString()) ;
            }
        }
            else {
                 QMessageBox::critical(this,tr("error::"),query.lastError().text()) ;
                   }

}

void MainWindow::on_cam_clicked()
{

}

void MainWindow::on_pushButton_5_clicked()
{

        QString link="file:///C:/Users/dell/Desktop/stock/produit.pdf";
        QDesktopServices::openUrl(QUrl(link));

}

void MainWindow::on_pushButtonb_clicked()
{
    QString link="file:///C:/Users/dell/Desktop/stock/histo.txt";
    QDesktopServices::openUrl(QUrl(link));
}

// End Makram

void MainWindow::on_pushButton_GS_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);

}

void MainWindow::on_pushButton_RPGF_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEdit_Username->setText("");
    ui->lineEdit_Password->setText("");
    ui->lineEdit_Username_mdp_oublie->setText("");
}

void MainWindow::on_pushButton_RMPF_6_clicked()
{
    if (role == "ADMIN"){
           ui->stackedWidget->setCurrentIndex(1);
       }else{
           QMessageBox::critical(this, tr("Error::"), "Vous n'etes pas un admin pour visionner cette page");
       }

}

void MainWindow::on_pushButton_cht_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}

void MainWindow::on_pushButton_cht_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}

void MainWindow::on_pushButton_cht_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}

void MainWindow::on_pushButton_cht_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}

void MainWindow::on_pushButton_cht_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}

void MainWindow::on_pushButton_cht_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}

void MainWindow::on_pushButton_Retourrrr_clicked()
{
    if (role=="ADMIN"){
        ui->stackedWidget->setCurrentIndex(1);
    }else if (role=="FINANCE"){
        ui->stackedWidget->setCurrentIndex(3);
    }else if (role=="CLIENTS"){
        ui->stackedWidget->setCurrentIndex(4);
    }else if (role=="FOURNISSEURS"){
        ui->stackedWidget->setCurrentIndex(5);
    }else if (role=="MAINTENANCE"){
        ui->stackedWidget->setCurrentIndex(6);
    }else if (role=="EMOPLYEE"){
        ui->stackedWidget->setCurrentIndex(7);
    }else if (role=="STOCK"){
        ui->stackedWidget->setCurrentIndex(8);
    }
}

void MainWindow::on_pushButton_chatboxxxZE_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}

void MainWindow::on_pushButton_QRCODEC_clicked()
{
    int tabeq=ui->tableViewC->currentIndex().row();
    QVariant idd=ui->tableViewC->model()->data(ui->tableViewC->model()->index(tabeq,0));
    QString id=idd.toString();
   // QString code=idd.toSTring();
    QSqlQuery qry;
    qry.prepare("select * from CLIENTS where ID_CLIENT=:id");
    qry.bindValue(":id",id);
    qry.exec();
     QString nom,prenom,email,idC;//attributs
     QString cin ;
   while(qry.next()){
       idC=qry.value(0).toString();
       nom=qry.value(1).toString();
       prenom=qry.value(2).toString();
       cin=qry.value(4).toString();
       email=qry.value(3).toString();
    }
    id=QString(id);
  id= "ID_CLIENT: " +id+ " NOM_CLIENT :" +nom+ " PRENOM_CLIENT: " +prenom+ " CIN_CLIENT: " +cin+ " EMAIL_CLIENT: " +email  ;
    QrCode qr = QrCode::encodeText(id.toUtf8().constData(), QrCode::Ecc::HIGH);

    // Read the black & white pixels
    QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
    for (int y = 0; y < qr.getSize(); y++) {
        for (int x = 0; x < qr.getSize(); x++) {
            int color = qr.getModule(x, y);  // 0 for white, 1 for black

            // You need to modify this part
            if(color==0)
                im.setPixel(x, y,qRgb(254, 254, 254));
            else
                im.setPixel(x, y,qRgb(0, 0, 0));
        }
    }
    im=im.scaled(200,200);

      ui->qr_code_C->setPixmap(QPixmap::fromImage(im));
}

void MainWindow::on_tableViewAffichage_F_activated(const QModelIndex &index)
{
    QString id=ui->tableViewAffichage_F->model()->data(index).toString() ;


            QSqlQuery query  ;

            query.prepare("select * from FOURNISSEURS where (ID_FOURNISSEUR LIKE '"+id+"')") ;
            if (query.exec())
            {
                while (query.next()) {
                    ui->lineEdit_id_F->setText(query.value(0).toString()) ;
                    ui->lineEdit_tel_F->setText(query.value(1).toString()) ;
                    ui->lineEdit_produit_F->setText(query.value(2).toString()) ;
                    ui->lineEdit_email_2_F->setText(query.value(3).toString()) ;
                    ui->lineEdit_email_F->setText(query.value(4).toString()) ;
                    ui->lineEdit_nom_F->setText(query.value(5).toString()) ;

                }
            }
                else {
                     QMessageBox::critical(this,tr("error::"),query.lastError().text()) ;
                       }
}

void MainWindow::on_tableView_maint_activated(const QModelIndex &index)
{
    QString id=ui->tableView_maint->model()->data(index).toString() ;
            QSqlQuery query  ;
            query.prepare("select * from EMPLOYEES where (ID_EMPLOYEE LIKE '"+id+"')") ;
            if (query.exec())
            {
                while (query.next()) {

                    ui->lineEdit_id_maint->setText(query.value(0).toString()) ;
                    ui->lineEdit_nom_maint->setText(query.value(1).toString()) ;
                    ui->lineEdit_prenom_maint->setText(query.value(2).toString()) ;
                    ui->lineEdit_cin_maint->setText(query.value(3).toString()) ;
                    ui->lineEdit_email_maint->setText(query.value(4).toString()) ;
                    ui->lineEdit_Ps_maint->setText(query.value(5).toString()) ;
                    ui->lineEdit_num_maint->setText(query.value(13).toString()) ;
                    ui->lineEdit_idtache_maint->setText(query.value(10).toString()) ;

                }
            }
                else {
                     QMessageBox::critical(this,tr("error::"),query.lastError().text()) ;
                       }
}

void MainWindow::on_tableViewA_activated(const QModelIndex &index)
{
    QString cin=ui->tableViewA->model()->data(index).toString() ;
        QSqlQuery query  ;
        query.prepare("select * from EMPLOYE where (CIN LIKE '"+cin+"')") ;
        if (query.exec())
        {
            while (query.next()) {

                ui->lineEdit_cinA->setText(query.value(0).toString()) ;
                ui->lineEdit_nomA->setText(query.value(1).toString()) ;
                ui->lineEdit_adresseA->setText(query.value(2).toString()) ;
                ui->lineEdit_emailA->setText(query.value(3).toString()) ;
                if ((query.value(4).toString() == "standard"))
                { ui->radioButtonA->setChecked(1) ;  }
                if ((query.value(4).toString() == "technicien"))
                { ui->radioButton_2A->setChecked(1) ;  }
                ui->lineEdit_prenomA->setText(query.value(5).toString()) ;
            }
        }
            else {
                 QMessageBox::critical(this,tr("error::"),query.lastError().text()) ;
                   }
}

void MainWindow::on_pushButton_statWahchi_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();

                                 model->setQuery("select * from CLIENTS where TYPE_CLIENT like 'VIP'  ");

                                 float VIP=model->rowCount();

                                 model->setQuery("select * from CLIENTS where TYPE_CLIENT like 'Fidele' ");

                                 float Fidele=model->rowCount();

                                 model->setQuery("select * from CLIENTS where TYPE_CLIENT like 'Passager' ");

                                 float Passager=model->rowCount();

                                 float total=VIP+Fidele+Passager;



                                 QString a=QString("VIP  "+QString::number((VIP*100)/total,'f',2)+"%" );

                                 QString b=QString("Fidele  "+QString::number((Fidele*100)/total,'f',2)+"%" );

                                 QString c=QString("Passager  "+QString::number((Passager*100)/total,'f',2)+"%" );



                                 QPieSeries *series = new QPieSeries();

                                 series->append(a,VIP);

                                 series->append(b,Fidele);

                                 series->append(c,Passager);





                         if (VIP!=0)

                         {QPieSlice *slice = series->slices().at(0); //pourcentage de chaque slice

                          slice->setLabelVisible();

                          slice->setPen(QPen());}

                         if ( Fidele!=0)

                         {

                                  // Add label, explode and define brush for 2nd slice

                                  QPieSlice *slice1 = series->slices().at(1);

                                  //slice1->setExploded();

                                  slice1->setLabelVisible();

                         }

                         if ( Passager!=0)

                         {

                                  // Add label, explode and define brush for 2nd slice

                                  QPieSlice *slice2 = series->slices().at(2);

                                  //slice2->setExploded();

                                  slice2->setLabelVisible();

                         }





                                 // Create the chart widget

                                 QChart *chart = new QChart();

                                 // Add data to chart with title and hide legend

                                 chart->addSeries(series);

                                 chart->setTitle("Pourcentage Par TYPE_CLIENT :Nombre clients "+ QString::number(total));

                                 chart->legend()->hide();

                                 // Used to display the chart

                                 QChartView *chartView = new QChartView(chart);

                                 chartView->setRenderHint(QPainter::Antialiasing);

                                 chartView->resize(1000,500);

                                 chartView->show();
}

void MainWindow::on_pushButton_qr_finance_clicked()
{
    int tabeq=ui->tableViewComptes->currentIndex().row();
    QVariant idd=ui->tableViewComptes->model()->data(ui->tableViewComptes->model()->index(tabeq,0));
    QString id=idd.toString();
    // QString code=idd.toSTring();
    QSqlQuery qry;
    qry.prepare("select * from comptes where n_compte=:id");
    qry.bindValue(":id",id);
    qry.exec();
     QString num, nom, classe, type, solde;//attributs
    while(qry.next()){
       num=qry.value(0).toString();
       nom=qry.value(1).toString();
       classe=qry.value(2).toString();
        type=qry.value(3).toString();
       solde=qry.value(4).toString();
    }
    id=QString(id);
  id= "ID_Compte: " +id+ " | Nom compte :" +nom+ " | Classe compte: " +classe+ " | Type compte: " +type+ " | Solde: " +solde  ;
    QrCode qr = QrCode::encodeText(id.toUtf8().constData(), QrCode::Ecc::HIGH);

    // Read the black & white pixels
    QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
    for (int y = 0; y < qr.getSize(); y++) {
        for (int x = 0; x < qr.getSize(); x++) {
            int color = qr.getModule(x, y);  // 0 for white, 1 for black

            // You need to modify this part
            if(color==0)
                im.setPixel(x, y,qRgb(254, 254, 254));
            else
                im.setPixel(x, y,qRgb(0, 0, 0));
        }
    }
    im=im.scaled(200,200);

      ui->qr_code_finance->setPixmap(QPixmap::fromImage(im));
}

void MainWindow::on_pushButton_qr_four_clicked()
{
    int tabeq=ui->tableViewAffichage_F->currentIndex().row();
    QVariant idd=ui->tableViewAffichage_F->model()->data(ui->tableViewAffichage_F->model()->index(tabeq,0));
    QString id=idd.toString();
    // QString code=idd.toSTring();
    QSqlQuery qry;
    qry.prepare("select * from fournisseurs where id_fournisseur=:id");
    qry.bindValue(":id",id);
    qry.exec();
     QString num, num_tel, produit, email, nom , date;//attributs
    while(qry.next()){
       id=qry.value(0).toString();
       num_tel=qry.value(1).toString();
       produit=qry.value(2).toString();
        date=qry.value(3).toString();
       email=qry.value(4).toString();
        nom=qry.value(5).toString();
    }
    id=QString(id);
  id= "ID_Compte: " +id+ " | num_tel :" +num_tel+ " | Nom produit : " +produit+ " | Date arrivage: " +date+ " | Email_fournisseur: " +email+ " | Nom_fournisseur: " +nom ;
    QrCode qr = QrCode::encodeText(id.toUtf8().constData(), QrCode::Ecc::HIGH);

    // Read the black & white pixels
    QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
    for (int y = 0; y < qr.getSize(); y++) {
        for (int x = 0; x < qr.getSize(); x++) {
            int color = qr.getModule(x, y);  // 0 for white, 1 for black

            // You need to modify this part
            if(color==0)
                im.setPixel(x, y,qRgb(254, 254, 254));
            else
                im.setPixel(x, y,qRgb(0, 0, 0));
        }
    }
    im=im.scaled(200,200);


      ui->qr_code_four->setPixmap(QPixmap::fromImage(im));
}

void MainWindow::on_pushButton_employe_clicked()
{
    int tabeq=ui->tableViewA->currentIndex().row();
        QVariant idd=ui->tableViewA->model()->data(ui->tableViewA->model()->index(tabeq,0));
        QString id=idd.toString();
       // QString code=idd.toSTring();
        QSqlQuery qry;
        qry.prepare("select * from EMPLOYE where CIN= :CIN");
        qry.bindValue(":CIN",id);
        qry.exec();
         QString nom,adresse,prenom,email,cin, type;//attributs
       while(qry.next()){
           cin=qry.value(0).toString();
           nom=qry.value(1).toString();
           prenom=qry.value(2).toString();
           email=qry.value(3).toString();
           type=qry.value(4).toString();
           adresse=qry.value(5).toString();
        }
        id=QString(id);
      id="cin_EMPLOYEE: " +cin+ " | NOM_EMPLOYEE :" +nom+ " | adresse_EMPLOYEE: " +adresse+ " | email_EMPLOYEE:\t" +email+ " | TYPE_EMPLOYEE" +type+ " | prenom_EMPLOYEE: " +prenom  ;
        QrCode qr = QrCode::encodeText(id.toUtf8().constData(), QrCode::Ecc::HIGH);

        // Read the black & white pixels
        QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
        for (int y = 0; y < qr.getSize(); y++) {
            for (int x = 0; x < qr.getSize(); x++) {
                int color = qr.getModule(x, y);  // 0 for white, 1 for black

                // You need to modify this part
                if(color==0)
                    im.setPixel(x, y,qRgb(254, 254, 254));
                else
                    im.setPixel(x, y,qRgb(0, 0, 0));
            }
        }
        im=im.scaled(200,200);

          ui->qr_code_employe->setPixmap(QPixmap::fromImage(im));
}

void MainWindow::on_pushButton_codepromo_clicked()
{
    QString id = ui->comboBox_codepromoid->currentText();
    QString code = ui->comboBox_codepromo->currentText();

    QString price_discount;
    QSqlQuery querySelect;
    querySelect.prepare("select price_discount from codepromo where code like '"+code+"'");
    if (querySelect.exec()){
        ui->textEdit->clear();
        while (querySelect.next()){
            price_discount = querySelect.value(0).toString();
        }
    }else{
        QMessageBox::critical(this, tr("Error::"), querySelect.lastError().text());
    }
    QSqlQuery query;
    query.prepare("update commandes set total = (total - (total * "+price_discount+" / 100)) where id_commande like "+id+" ");
    if (query.exec()){
            ui->tableViewCommandes_2->setModel(GC1.afficherCommandes2());
            QMessageBox::information(nullptr, QObject::tr("Database is open"),
                                  QObject::tr("Manipulation effectué"),
                                  QMessageBox::Ok
                                  );
            ui->tableViewCommande1->setModel(GC1.afficherCommandes1());
        }else{
        QMessageBox::critical(this, tr("Error::"), query.lastError().text());
    }
}
