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
#include "tray.h"

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


    MyTray *mytray = new MyTray(&win);
    win.addWidget(mytray);

    EventLabel *label = new EventLabel;
    label->resize(300, 200);
    label->setMouseTracking(true);
    win.addWidget(label);

    QFont font("Arial", 10, QFont::Normal, false);
    QApplication::setFont(font);
//    win.setWindowFlags(); // 设置禁止最大化
    win.setFixedSize(350,480); // 禁止改变窗口大小。
    win.show();

    return app.exec();
}
