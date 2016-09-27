#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QDebug>
#include <QSpinbox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QGridLayout>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle(tr("Main Window"));

    openAction = new QAction(QIcon(":/images/doc-open"), tr("&Open..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction, &QAction::triggered, this, &MainWindow::open);

    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction(openAction);

    QToolBar *toolBar = addToolBar(tr("&File"));
    toolBar->addAction(openAction);

    QToolBar *toolBar2 = addToolBar(tr("Tool Bar 2"));
    toolBar2->addAction(openAction);

    statusBar() ;
}

MainWindow::~MainWindow()
{
}
UserAgeDialog::UserAgeDialog(QWidget *parent):QDialog(parent){}
void MainWindow::open()
{
    UserAgeDialog *dialog = new UserAgeDialog(this);

    QSpinBox *spinBox = new QSpinBox();
    void (QSpinBox:: *spinBoxSignal)(int) = &QSpinBox::valueChanged;
    QObject::connect(spinBox, spinBoxSignal, dialog, &UserAgeDialog::getAge);
    QObject::connect(dialog, &UserAgeDialog::userAgeChanged, this, &MainWindow::setUserAge);

    QDialogButtonBox *button = new QDialogButtonBox(dialog);
    button->addButton( "OK", QDialogButtonBox::YesRole);
    button->addButton( "NO", QDialogButtonBox::NoRole);
    connect(button, SIGNAL(accepted()), dialog, SLOT(accept()));
    connect(button, SIGNAL(rejected()), dialog, SLOT(reject()));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(spinBox);
    layout->addWidget(button);
    dialog->setLayout(layout);
    dialog->setWindowTitle(tr("Hello, dialog!"));
    dialog->show();
}
