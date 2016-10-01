#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QSpinBox>
#include <QSlider>
#include <QFont>
#include <QSystemTrayIcon>
#include <QMenu>
#include "newspaper.h"
#include "reader.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Newspaper anewspaper("Newspaper A");
    Reader reader;
    QObject::connect(&anewspaper, &Newspaper::newPaper,
                     &reader,    &Reader::receiveNewspaper);
    anewspaper.send();
    MainWindow win;

    QPushButton *button = new QPushButton("Set Value");
    QObject::connect(button, &QPushButton::clicked, &win, &MainWindow::open);
//    QObject::connect(button, &QPushButton::clicked, &QApplication::quit);
    win.addWidget(button);

    QPushButton *button2 = new QPushButton("Choose");
    QObject::connect(button2, &QPushButton::clicked, &win, &MainWindow::choose);
    win.addWidget(button2);

    QSpinBox *spinBox = new QSpinBox(&win);
    QSlider *slider = new QSlider(Qt::Horizontal, &win);
    spinBox->setRange(0, 130);
    slider->setRange(0, 130);

    QObject::connect(slider, &QSlider::valueChanged, spinBox, &QSpinBox::setValue);
    void (QSpinBox:: *spinBoxSignal)(int) = &QSpinBox::valueChanged;
    QObject::connect(spinBox, spinBoxSignal, slider, &QSlider::setValue);
    spinBox->setValue(35);
    win.addWidget(spinBox);
    win.addWidget(slider);

    QSystemTrayIcon *trayIcon = new QSystemTrayIcon();
    trayIcon->setToolTip(QString("I'm tray"));
    trayIcon->setIcon(QIcon(":/images/system-tray"));
    QMenu *tray_menu = new QMenu();
    QAction *action_show = new QAction(tray_menu);
    action_show->setText(QString("显示"));
    action_show->setIcon(QIcon(":/images/system-show"));
    QAction *action_show2 = new QAction(tray_menu);
    action_show2->setText(QString("隐藏"));
    action_show2->setIcon(QIcon(":/images/system-hide"));
    QObject::connect(action_show, &QAction::triggered, &win, &QMainWindow::show);
    QObject::connect(action_show2, &QAction::triggered, &win, &QMainWindow::hide);
    tray_menu->addAction(action_show);
    tray_menu->addAction(action_show2);
    trayIcon->setContextMenu(tray_menu);
    trayIcon->show();

    QFont font("Arial", 10, QFont::Normal, false);
    QApplication::setFont(font);
    win.setWindowFlags(Qt::WindowCloseButtonHint); // 设置禁止最大化
    win.setFixedSize(350,480); // 禁止改变窗口大小。
    win.show();

    return app.exec();
}
