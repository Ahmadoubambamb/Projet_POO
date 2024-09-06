#ifndef SECONNECTERSQLITE3_H
#define SECONNECTERSQLITE3_H

#include "qsqldatabase.h"
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

void InsertionDeDonnees();
bool NotreConnection() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("nosvoiture.db");

    if (!db.open()) {
        QMessageBox::critical(nullptr, QObject::tr("Impossible d'ouvrir le SGBDR"),
                              QObject::tr("Connection impossible !!"),
                              QMessageBox::Cancel);
        qDebug() <<"Data base echec";
        return false;

    }
    qDebug() << "connecter avec sucess!!";
    return true;
}

void InsertionDeDonnees(const QString& marque, const QString& gamme, const QString& modele, int annee, const QString& photoUrl, const QString& presentation) {
    QSqlQuery query;
    query.prepare("INSERT INTO Voitures (marque, gamme, modele, annee,image_vh, presentation) VALUES (?, ?, ?, ?, ?, ?)");
    query.addBindValue(marque);
    query.addBindValue(gamme);
    query.addBindValue(modele);
    query.addBindValue(annee);
    query.addBindValue(photoUrl);
    query.addBindValue(presentation);
    if (!query.exec()) {
        QMessageBox::critical(nullptr, QObject::tr("Impossible d'ouvrir le SGBDR"),
                              QObject::tr(" Ou Chargement impossible !!"),
                              QMessageBox::Cancel);
        qDebug() <<"Echec de la charge";
    }
    else
        qDebug() << "Charegement effectuer avec succes!!";
}
#endif // SECONNECTERSQLITE3_H



//void Cconnecter()
//{QSqlDatabase db=QSqlDatabase::addDatabase("QPSQL");
//    db.setHostName("localhost");
//    db.setUserName("postgres");
//    db.setPort(5432);
//    db.setPassword("mamekhady");
//    db.setDatabaseName("biblio.db");
//    bool ouvert=db.open();
//    if(ouvert==true)
//        qDebug() << "Base de donnees connecter avec succes!!";
//    else
//    {    qDebug() << "Echec de la connexion a la base de donnees";
//        exit(-1);
//    }
//}




