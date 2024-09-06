#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QPixmap>
#include <QLabel>
#include <QMenu>
#include <QAction>
#include "seconnectermysql.h"
#include <QDebug>
#include <QVBoxLayout>
//#include "comparehach.h"
//#include <QCharts>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , tableHache(new NotreTableHache(100))// on construis une table de 100 buckets
{
    ui->setupUi(this);

    // Connexion à la base de données
    if (!NotreConnection())
        exit(-1);

    ui->tableWidget->setColumnCount(7);
    QStringList headers;
    headers << "Clé Voiture" << "Marque" << "Gamme" << "Modèle" << "Année" << "Photo" << "Présentation";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setColumnWidth(5, 250);

    // on creer ici un menu button
       QMenu *menuBase = new QMenu(this);
       QAction *B1 = new QAction("charger", this);
       QAction *B2 = new QAction("afficher", this);
       QAction *Ataille = new QAction("Taille",this);
       QAction *sauve = new QAction("Sauvegarder",this);
       menuBase->addAction(B1);
       menuBase->addAction(B2);
       menuBase->addAction(Ataille);
       menuBase->addAction(sauve);
       ui->Base->setMenu(menuBase);

       // bouton voiture
       QMenu *menuVoiture = new QMenu(this);
       QAction *v1 = new QAction("Rechercher", this);
       QAction *v2 = new QAction("Inserer", this);
       QAction *v3 = new QAction("Supprimer",this);
       menuVoiture->addAction(v1);
       menuVoiture->addAction(v2);
       menuVoiture->addAction(v3);
       ui->Voiture->setMenu(menuVoiture);

       QMenu *menuHache = new QMenu(this);
       QAction *F1 = new QAction("f1", this);
       QAction *F2 = new QAction("f2", this);
       QAction *F3 = new QAction("f3",this);
       QAction *F4 = new QAction("SansHach",this);
       menuHache->addAction(F1);
       menuHache->addAction(F2);
       menuHache->addAction(F3);
       menuHache->addAction(F4);
       ui->FonctionHachage->setMenu(menuHache);
       // Connecter les boutons aux slots
       connect(B1, &QAction::triggered, this, &MainWindow::chargement);
       connect(B2, &QAction::triggered, this, &MainWindow::affichage);
       connect(Ataille,&QAction::triggered,this,&MainWindow::tailleT);
       connect(sauve, &QAction::triggered, this, &MainWindow::sauvegarder);
       connect(ui->reset, &QPushButton::clicked, this, &MainWindow::cleanner);
        connect(ui->Recherher, &QPushButton::pressed, this, &MainWindow::valideVoiture);
       connect(ui->supprimer,&QPushButton::clicked,this, &MainWindow::supprime);

      // connect(ui->compareButton, &QPushButton::clicked, this, &MainWindow::compareHashFunctions);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete tableHache;
}

void MainWindow::chargement()
{
    tableHache->charger();
    QMessageBox::information(this, "Succès", "Données chargées avec succès.");
}

void MainWindow::sauvegarder()
{
    tableHache->sauvegarder();
    QMessageBox::information(this, "Succès", "Données sauvegardées avec succès.");
}

void MainWindow::affichage()
{
    afficherVoitures();
}

void MainWindow::tailleT()
{
    QMessageBox::information(this, "Taille de la table", QString::number(tableHache->size()));
}

void MainWindow::cleanner()
{
    ui->tableWidget->clearContents();
}

//void MainWindow::h1(){

//}

void MainWindow::afficherVoitures()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    for (int i = 0; i < tableHache->taillemax(); ++i) {
        bucket *current = tableHache->Tab(i);
        while (current != nullptr) {
            VOITURE *voiture = current->voiture;
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(voiture->cle_voiture));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(voiture->marque));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(voiture->gamme));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(voiture->modele));
            ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(voiture->annee)));

            QLabel *imageLabel = new QLabel;
            QString imagePath = voiture->photo;
            imagePath = imagePath.remove("file:///");
            QPixmap pixmap(imagePath);
            qDebug() << "Image path: " << imagePath;
            if (!pixmap.isNull()) {
                imageLabel->setPixmap(pixmap.scaled(250, 250, Qt::KeepAspectRatio));
            } else {
                imageLabel->setText("Image non disponible");
                qDebug() << "Erreur de chargement de l'image: " << imagePath;
            }
            ui->tableWidget->setCellWidget(row, 5, imageLabel);
              ui->tableWidget->setRowHeight(row, 200);
            ui->tableWidget->setItem(row, 6, new QTableWidgetItem(voiture->presentation));
            current = current->suivant;
        }
    }
}




void MainWindow::valideVoiture()
{
    QString marque = ui->searchMarque->text();
      QString cle = ui->searchCle->text();
      VOITURE* voiture = tableHache->get_voiture(marque, cle);
      if (voiture) {
         QMessageBox::information(this, "Voiture trouvée", "Clé: " + voiture->cle_voiture + "\nMarque: " + voiture->marque + "\nGamme: " + voiture->gamme + "\nModèle: " + voiture->modele + "\nAnnée: " + QString::number(voiture->annee) + "\nPhoto: " + voiture->photo + "\nPrésentation: " + voiture->presentation);
        afficherImageVoiture(voiture->photo);

      } else {
          QMessageBox::warning(this, "Erreur", "Voiture non trouvée.");
}
}

void MainWindow::supprime(){
    QString cle = ui->clef->text();
      QString marque = ui->valeurs->text();
    tableHache->suppression(marque,cle);
     QMessageBox::information(this, "Succès", "Données supprimer avec succès.");
}

void MainWindow::afficherImageVoiture(QString imagePath)
{
    imagePath = imagePath.remove("file:///");
    QPixmap pixmap(imagePath);
    if (!pixmap.isNull()) {
        QLabel *imageLabel = new QLabel;
        imageLabel->setPixmap(pixmap.scaled(250, 250, Qt::KeepAspectRatio));
        imageLabel->show();
        QMessageBox msgBox;
        msgBox.layout()->addWidget(imageLabel);
        msgBox.exec();
    } else {
        QMessageBox::warning(this, "Erreur", "Image non disponible.");
        qDebug() << "Erreur de chargement de l'image: " << imagePath;
    }
}

