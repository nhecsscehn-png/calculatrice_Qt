#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Rendre les boutons à nouveau formidables
    QVBoxLayout *vb0 = new QVBoxLayout();
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
