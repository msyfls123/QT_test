#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QSpinBox>
#include <QSlider>
#include <QFont>
#include <QSystemTrayIcon>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QUrl>
#include <QMenu>
#include "newspaper.h"
#include "reader.h"
#include "mainwindow.h"
#include "tray.h"
#include "webview.h"

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
    button->setStyleSheet("QPushButton{width:150px;height:30px;border-radius:10px;border: 2px groove gray;}QPushButton:hover{background-color:black;color:white;}");
    QObject::connect(button, &QPushButton::clicked, &win, &MainWindow::open);
    win.addWidget(button);

    QPushButton *button2 = new QPushButton("Choose");
    button2->setStyleSheet("QPushButton{width:150px;height:30px;border-radius:10px;border: 2px groove gray;}");
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

//    QWebEngineView *view = new QWebEngineView(&win);
//    view->load(QUrl("http://msyfls123.github.io/myWiki/"));
//    win.addWidget(view);
    Webview *view = new Webview(Q_NULLPTR);
    view->load(QUrl("http://masy.site"));
    win.addWidget(view);

    MyTray *mytray = new MyTray(&win);
    win.addWidget(mytray);

    EventLabel *label = new EventLabel;
    label->resize(300, 200);
    label->setMouseTracking(true);
    win.addWidget(label);

    QFont font("Arial", 10, QFont::Normal, false);
    QApplication::setFont(font);
//    win.setWindowFlags(); // 设置禁止最大化
    win.setFixedSize(720,630); // 禁止改变窗口大小。
    win.show();

    return app.exec();
}
