#ifndef HISTO_H
#define HISTO_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class histo
{
private:
    QString operation;
    int id_f;

public:
    histo();
    histo(QString, int);
    void Ajouter();
    QSqlQueryModel * Afficher( );

};
#endif // HISTO_H
