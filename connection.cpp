#include "connection.h"

Connection::Connection(){
}

bool Connection::createconnection(){
    db = QSqlDatabase::addDatabase("QODBC");
    bool test = false;
    db.setDatabaseName("SourceProjet");
    db.setUserName("Yacine");
    db.setPassword("trunks");
    if (db.open()) test=true;
    return test;
}
void Connection::closeConnection(){
    db.close();
}
