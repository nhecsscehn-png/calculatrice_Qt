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
    QStringList buttonList;
    buttonList << "7" << "8" << "9" << "4" << "5" << "6" << "1" << "2" << "3" << "0";

    QStringList buttonArithmetic;
    buttonArithmetic << "÷" << "×" << "-" << "+";

    QStringList buttonExtras;
    buttonExtras << "C" << "⌫" << "=" << "";

    QLabel *displayLbl = new QLabel();


    // Crée un widget central
    QWidget *centralWidget = new QWidget(this);

    // Crée le layout principal vertical
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Crée les boutons 1-9
    QVBoxLayout *vb0 = new QVBoxLayout();
    QVBoxLayout *vb1 = new QVBoxLayout();
    QVBoxLayout *vb2 = new QVBoxLayout();
    QHBoxLayout *hb0 = nullptr;
    QHBoxLayout *hb1 = new QHBoxLayout();

    for(int m = 0; m < buttonList.size(); m++){
        if(m % 3 == 0){
            hb0 = new QHBoxLayout(); // Pointeur nommé "hb0" qui pointe sur un nouveau conteneur horizontal
            vb0->addLayout(hb0); // Conteneur "vb0" dans lequel l'on empile les conteneurs horizontaux
        }
        QPushButton *numBee = new QPushButton(buttonList.at(m)); // Crée dynamiquement un bouton. QString::number(m) : Convertit le nombre m (0-9) en texte affichable
        connect(numBee, &QPushButton::clicked, [numBee, displayLbl, this](){
            // qDebug() << numBee->text();
            displayLbl->setText(displayLbl->text() + numBee->text());
            this->m_calcContents.push(numBee->text());
        });
        // numBee->setMinimumSize(80, 40);  // Taille des boutons
        hb0->addWidget(numBee); // Placer le bouton dans le conteneur
    }

    // Ajouter des boutons de symboles arithmétique
    for(int k = 0; k < buttonArithmetic.size(); ++k){
        QPushButton *tempButton = new QPushButton(buttonArithmetic.at(k));
        connect(tempButton, &QPushButton::clicked, [displayLbl, this](){
            displayLbl->setText(displayLbl->text() + tempButton->text());
            this->m_calcContents.push(tempButton->text());
        });
        vb1->addWidget(tempButton);
    }

    hb1->addLayout(vb0);
    hb1->addLayout(vb1);

    // Ajouter des boutons en plus
    for(int p = 0; p < buttonExtras.size(); ++p){
        QPushButton *tempButton = new QPushButton(buttonExtras.at(p));

        // Rend meilleur
        if(buttonExtras.at(p).isEmpty() || buttonExtras.at(p).isNull()){
            tempButton->setDisabled(true);
        }
        vb2->addWidget(tempButton);
    }
    hb1->addLayout(vb2);

    // ui->verticalLayout->addLayout(vb0);

    // Ajoute le display ou s'affiche les chiffres (ordre de ligne important pour l'endroit ou il apparaîtra)
    mainLayout->addWidget(displayLbl);

    // Ajoute tous les boutons au layout principal
    mainLayout->addLayout(hb1); // Parcequ'il n y a pas de verticalLayout

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
