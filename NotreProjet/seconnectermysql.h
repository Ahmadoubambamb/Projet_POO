#ifndef SECONNECTERMYSQL_H
#define SECONNECTERMYSQL_H
bool NotreConnection()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setDatabaseName("notrebases");
    db.setPort(3306);
    db.setPassword("mamekhady");
    if(db.open())
       {qDebug() <<"connexion a Mysql avec Succes !!";
        return true;}
    else{qDebug() <<"Echec !!";
     return false;}
}


#endif // SECONNECTERMYSQL_H
