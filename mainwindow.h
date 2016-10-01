#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDialog>
#include <QMainWindow>
#include <QWidget>
#include <QDebug>
#include <QWidget>
#include <QBoxLayout>

class QTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addWidget(QWidget *widget);
    void open();
private slots:
    void openFile();
    void saveFile();
    void hide();
public slots:
    void choose();
private:
    void setUserAge(int age)
    {
        userAge = age;
        qDebug() << userAge;
    };
    QAction *openAction;
    QAction *saveAction;
    QWidget *main;
    QBoxLayout *layout;
    QTextEdit *textEdit;

    int userAge;
    int index;
};


class UserAgeDialog : public QDialog{
    Q_OBJECT
public:
    UserAgeDialog(QWidget *parent):QDialog(parent){}
    void getAge(int age)
    {
        newAge=age;
    }
public slots:
    void accept(){
        emit userAgeChanged(newAge); // newAge is an int
        QDialog::accept();
    }
signals:
    void userAgeChanged(int &age);
private:
    int newAge;
};
#endif // MAINWINDOW_H
