#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addition(void);
    void substraction(void);
    void multiply(void);
    void divide(void);
    void equals(void);

private:
    Ui::MainWindow *ui;
    QStack<QString> m_calcContents;
};
#endif // MAINWINDOW_H
