#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>      // Pour créer des boutons
#include <QHBoxLayout>      // Layout horizontal (boutons côte à côte)
#include <QVBoxLayout>      // Layout vertical (empiler des éléments)
#include <QLabel>           // Pour l'affichage du résultat (écran de la calculatrice)
#include <QMessageBox>      // Pour afficher des messages d'erreur (ex: division par zéro)

// Constructeur de la fenêtre principale
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)           // Appel du constructeur de la classe mère QMainWindow
    , ui(new Ui::MainWindow)        // Création de l'interface générée par Qt Designer (même si on l'utilise peu ici)
{
    ui->setupUi(this);              // Initialise tout ce qui vient du fichier .ui (si l'on en as un)

    // === Listes des textes des boutons ===
    QStringList buttonList = {"7","8","9","4","5","6","1","2","3","0"};   // Les 10 chiffres
    QStringList buttonArithmetic = {"÷", "×", "-", "+"};                  // Les 4 opérateurs

    // === Création de l'écran d'affichage ===
    QLabel *displayLbl = new QLabel("0");                    // Crée le label qui affiche le résultat
    displayLbl->setAlignment(Qt::AlignRight);                // Aligne le texte à droite (comme une vraie calculatrice)
    displayLbl->setStyleSheet("QLabel { background-color: #222; color: white; font-size: 24px; padding: 10px; min-height: 50px; }");
    // Style visuel : fond sombre, texte blanc, grande police

    // === Création du widget central et du layout principal ===
    QWidget *centralWidget = new QWidget(this);          // Widget obligatoire pour QMainWindow
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);  // Layout vertical principal (écran + boutons)

    // === Layouts pour organiser les boutons ===
    QVBoxLayout *vb0 = new QVBoxLayout();   // Contient tous les boutons numériques (organisés en lignes)
    QVBoxLayout *vb1 = new QVBoxLayout();   // Contient les opérateurs arithmétiques (colonne de droite)
    QVBoxLayout *vb2 = new QVBoxLayout();   // Contient C, ⌫, = (dernière colonne)
    QHBoxLayout *hb1 = new QHBoxLayout();   // Layout horizontal qui va contenir vb0 + vb1 + vb2

    // ====================== BOUTONS NUMÉRIQUES (0-9) ======================
    QHBoxLayout *hb0 = nullptr;             // Pointeur temporaire pour créer les lignes de 3 boutons

    for (int m = 0; m < buttonList.size(); ++m) {          // Boucle sur les 10 chiffres
        if (m % 3 == 0) {                                  // Toutes les 3 boutons → nouvelle ligne
            hb0 = new QHBoxLayout();                       // Crée un nouveau layout horizontal
            vb0->addLayout(hb0);                           // Ajoute cette ligne dans le layout vertical des nombres
        }

        QPushButton *numBee = new QPushButton(buttonList.at(m));  // Crée un bouton avec le chiffre
        numBee->setMinimumSize(60, 60);                           // Taille minimale pour un bel affichage

        // Connexion du clic sur le bouton chiffre
        connect(numBee, &QPushButton::clicked, [this, numBee, displayLbl]() {
            QString current = displayLbl->text();                 // Récupère le texte actuel de l'écran

            // Si l'écran affiche "0" et qu'on clique sur un autre chiffre → on remplace le 0
            if (current == "0" && numBee->text() != "0")
                displayLbl->setText(numBee->text());
            else
                displayLbl->setText(current + numBee->text());    // Sinon on ajoute le chiffre à la suite

            this->m_calcContents.push(numBee->text());            // On stocke le chiffre dans la pile
        });

        hb0->addWidget(numBee);                                   // Ajoute le bouton dans la ligne horizontale
    }

    // ====================== BOUTONS OPÉRATEURS (+ - × ÷) ======================
    for (const QString &op : buttonArithmetic) {              // Pour chaque opérateur
        QPushButton *opButton = new QPushButton(op);          // Crée le bouton opérateur
        opButton->setMinimumSize(60, 60);                     // Taille minimale

        // Connexion du clic sur un opérateur
        connect(opButton, &QPushButton::clicked, [this, opButton, displayLbl]() {
            if (m_calcContents.isEmpty()) return;             // On ne peut pas commencer par un opérateur

            QString opText = opButton->text();

            // Si le dernier élément est déjà un opérateur → on le remplace
            if (!m_calcContents.isEmpty() && !m_calcContents.top().back().isNumber()) {
                m_calcContents.pop();                         // Supprime l'ancien opérateur
                QString txt = displayLbl->text();
                txt.chop(1);                                  // Supprime le dernier caractère de l'affichage
                displayLbl->setText(txt);
            }

            m_calcContents.push(opText);                      // Ajoute le nouvel opérateur dans la pile
            displayLbl->setText(displayLbl->text() + opText); // Ajoute l'opérateur à l'écran
        });

        vb1->addWidget(opButton);                             // Ajoute le bouton dans la colonne des opérateurs
    }

    hb1->addLayout(vb0);    // Ajoute la grille des nombres
    hb1->addLayout(vb1);    // Ajoute la colonne des opérateurs

    // ====================== BOUTONS C, ⌫ et = ======================
    // Bouton "C" : tout effacer
    QPushButton *clearButton = new QPushButton("C");
    clearButton->setMinimumSize(60, 60);
    connect(clearButton, &QPushButton::clicked, [this, displayLbl]() {
        displayLbl->setText("0");          // Remet l'écran à 0
        m_calcContents.clear();            // Vide complètement la pile
    });
    vb2->addWidget(clearButton);

    // Bouton "⌫" : effacer le dernier caractère
    QPushButton *backspaceButton = new QPushButton("⌫");
    backspaceButton->setMinimumSize(60, 60);
    connect(backspaceButton, &QPushButton::clicked, [this, displayLbl]() {
        QString txt = displayLbl->text();
        if (txt.size() > 1) {
            txt.chop(1);                   // Supprime le dernier caractère
            displayLbl->setText(txt);
            if (!m_calcContents.isEmpty())
                m_calcContents.pop();      // Supprime aussi de la pile
        } else {
            displayLbl->setText("0");      // Si un seul caractère → remet à 0
            m_calcContents.clear();
        }
    });
    vb2->addWidget(backspaceButton);

    // ====================== BOUTON = (calcul) ======================
    QPushButton *equalButton = new QPushButton("=");
    equalButton->setMinimumSize(60, 60);

    // Connexion du clic sur le bouton égal (partie la plus importante)
    connect(equalButton, &QPushButton::clicked, [this, displayLbl]() {
        if (m_calcContents.isEmpty()) return;     // Rien à calculer

        QStringList tokens;       // Liste qui va contenir : nombre, opérateur, nombre, opérateur...
        QString number;           // Tampon pour construire les nombres multi-chiffres

        // Étape 1 : transformer la pile en liste de tokens bien séparés
        for (const QString &token : m_calcContents) {
            if (token.back().isNumber() || token == ".") {   // Si c'est un chiffre ou un point
                number += token;                             // On ajoute au nombre en cours
            } else {                                         // Sinon c'est un opérateur
                if (!number.isEmpty()) {
                    tokens << number;        // On ajoute le nombre complet à la liste
                    number.clear();          // On vide le tampon
                }
                tokens << token;             // On ajoute l'opérateur
            }
        }
        if (!number.isEmpty())
            tokens << number;                // Ajoute le dernier nombre s'il reste

        // Étape 2 : calcul de gauche à droite
        double result = 0.0;                 // Résultat final
        QString op = "+";                    // Opérateur en cours (on commence par +)

        for (const QString &t : tokens) {
            if (t == "+" || t == "-" || t == "×" || t == "÷") {
                op = t;                      // On change d'opérateur
            }
            else {                           // C'est un nombre
                bool ok;
                double val = t.toDouble(&ok);   // Conversion en nombre (double)
                if (!ok) continue;

                // On applique l'opération en cours
                if (op == "+")      result += val;
                else if (op == "-") result -= val;
                else if (op == "×") result *= val;
                else if (op == "÷") {
                    if (val == 0.0) {                     // Protection contre division par zéro
                        QMessageBox::warning(this, "Erreur", "Division par zéro !");
                        return;
                    }
                    result /= val;
                }
            }
        }

        // Affichage du résultat
        displayLbl->setText(QString::number(result));

        // On vide la pile et on y met le résultat pour pouvoir continuer à calculer
        m_calcContents.clear();
        m_calcContents.push(QString::number(result));
    });

    vb2->addWidget(equalButton);

    // Bouton vide (juste pour l'alignement esthétique)
    QPushButton *emptyButton = new QPushButton("");
    emptyButton->setDisabled(true);
    emptyButton->setMinimumSize(60, 60);
    vb2->addWidget(emptyButton);

    hb1->addLayout(vb2);        // Ajoute la colonne C / ⌫ / =

    // ====================== Assemblage final ======================
    mainLayout->addWidget(displayLbl);   // Ajoute l'écran en haut
    mainLayout->addLayout(hb1);          // Ajoute tous les boutons en dessous

    setCentralWidget(centralWidget);     // Définit le widget central de la fenêtre
}

// Destructeur
MainWindow::~MainWindow()
{
    delete ui;      // Libère la mémoire de l'interface
}

// Méthodes déclarées dans le .h mais pas encore utilisées
void MainWindow::addition() {}
void MainWindow::substraction() {}
void MainWindow::multiply() {}
void MainWindow::divide() {}
void MainWindow::equals() {}
