#ifndef ARDUINODB_H
#define ARDUINODB_H

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
class arduinoDB
{
public:
    arduinoDB();
    arduinoDB(QString);
    void ajouter();
    QSqlQueryModel * afficher();
private:
    QString poids;
};

#endif // ARDUINODB_H
