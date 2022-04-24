#include "login.h"

login::login()
{

}
QSqlQueryModel * login::Afficher()
{
  QSqlQueryModel * model= new QSqlQueryModel();
       model->setQuery("select * from users;");
 return model;
}
