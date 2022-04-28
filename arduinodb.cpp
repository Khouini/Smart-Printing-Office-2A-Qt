#include "arduinodb.h"

arduinoDB::arduinoDB()
{

}

arduinoDB::arduinoDB(QString poids)
{
    this->poids=poids;
}
void arduinoDB::ajouter(){
    QSqlQuery query;
        query.prepare("insert into ARDUINO values (ARDUINO_SEQ.nextval, sysdate, :poids);");
        query.bindValue(":poids", poids);
        query.exec();
}
QSqlQueryModel * arduinoDB::afficher(){
    QSqlQueryModel * model= new QSqlQueryModel();
         model->setQuery("select ID, DATEG, POIDS FROM arduino order by id desc;");
         return model;

}
