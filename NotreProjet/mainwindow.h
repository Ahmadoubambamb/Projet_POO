#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QPushButton>
#include <QTabWidget>
#include <QLineEdit>
#include <QMenuBar>
#include <stack>
#include <QMenu>
#include <QHBoxLayout>
#include "NHachage.h"
//#include "sanshachage.h"
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
    void chargement();
    void sauvegarder();
    void affichage();
    void tailleT();
    void cleanner();
  //  void compareHashFunctions();
   // void on_btnSearch_clicked();
//    void h1();
//    void h2();
//    void h3();
    //int menuAch(int);
    void valideVoiture();
    void supprime();
private:
    Ui::MainWindow *ui;
    NotreTableHache *tableHache;
    //  SansHachage *tableHache;
    void afficherVoitures();
    void afficherImageVoiture(QString imagePath);
};


#endif // MAINWINDOW_H
