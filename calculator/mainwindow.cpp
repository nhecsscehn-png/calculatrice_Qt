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

    QLabel *displayLbl = new QLabel();

    // Crée un widget central
    QWidget *centralWidget = new QWidget(this);

    // Crée le layout principal vertical
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Crée les boutons 1-9
    QVBoxLayout *vb0 = new QVBoxLayout();
    QHBoxLayout *hb0 = nullptr;

    for(int m = 0; m < 10; m++){
        if(m % 3 == 0){
            hb0 = new QHBoxLayout(); // Pointeur nommé "hb0" qui pointe sur un nouveau conteneur horizontal
            vb0->addLayout(hb0); // Conteneur "vb0" dans lequel l'on empile les conteneurs horizontaux
        }
        QPushButton *numBee = new QPushButton(QString::number(m)); // Crée dynamiquement un bouton. QString::number(m) : Convertit le nombre m (0-9) en texte affichable
        connect(numBee, &QPushButton::clicked, [numBee, displayLbl](){
            qDebug() << numBee->text();
            displayLbl->setText(displayLbl->text() + numBee->text());
        });
        // numBee->setMinimumSize(80, 40);  // Taille des boutons
        hb0->addWidget(numBee); // Placer le bouton dans le conteneur
    }
    // ui->verticalLayout->addLayout(vb0);

    // Ajoute le display ou s'affiche les chiffres (ordre de ligne important pour l'endroit ou il apparaîtra)
    mainLayout->addWidget(displayLbl);

    // Ajoute tous les boutons au layout principal
    mainLayout->addLayout(vb0); // Parcequ'il n y a pas de verticalLayout

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
