#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Rendre les boutons à nouveau formidables

    // Crée un widget central
    QWidget *centralWidget = new QWidget(this);

    // Crée le layout principal vertical
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Crée les boutons 1-9
    QVBoxLayout *vb0 = new QVBoxLayout();
    QHBoxLayout *hb0 = nullptr;

    for(int m = 0; m < 9; m++){
        if(m % 3 == 0){
            hb0 = new QHBoxLayout();
            vb0->addLayout(hb0);
        }
        QPushButton *numBee = new QPushButton(QString::number(m)); // Crée dynamiquement un bouton de calculatrice dont le texte affiché correspond à un chiffre. C'est typique pour éviter de créer 10 boutons manuellement (0 à 9).
        // numBee->setMinimumSize(80, 40);  // Taille des boutons
        hb0->addWidget(numBee);
    }
    // ui->verticalLayout->addLayout(vb0);

    // Ajoute tous les boutons au layout principal
    mainLayout->addLayout(vb0);

    // Définit le widget central
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addition()
{

}

void MainWindow::substraction()
{

}

void MainWindow::multiply()
{

}

void MainWindow::divide()
{

}

void MainWindow::equals()
{

}

// Additionner
// Soustraire
// Multiplier
// Diviser
// Égal
// Bouton 0-9// Additionner
// Soustraire
// Multiplier
// Diviser
// Égal
// Bouton 0-9
