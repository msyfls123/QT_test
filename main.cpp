#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QSpinBox>
#include <QSlider>
#include <QFont>
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
    QWidget window;

    QPushButton *button = new QPushButton("Quit");
    QObject::connect(button, &QPushButton::clicked, &QApplication::quit);

    QPushButton *button2 = new QPushButton("Quit");
//    QObject::connect(button2, &QPushButton::clicked, &QApplication::quit);

    QSpinBox *spinBox = new QSpinBox(&window);
    QSlider *slider = new QSlider(Qt::Horizontal, &window);
    spinBox->setRange(0, 130);
    slider->setRange(0, 130);

    QObject::connect(slider, &QSlider::valueChanged, spinBox, &QSpinBox::setValue);
    void (QSpinBox:: *spinBoxSignal)(int) = &QSpinBox::valueChanged;
    QObject::connect(spinBox, spinBoxSignal, slider, &QSlider::setValue);
    spinBox->setValue(35);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(button);
    layout->addWidget(button2);
    layout->addWidget(spinBox);
    layout->addWidget(slider);
    window.setLayout(layout);
    QFont font("Arial", 10, QFont::Normal, false);
    QApplication::setFont(font);
    win.setWindowFlags(Qt::WindowCloseButtonHint); // 设置禁止最大化
    win.setFixedSize(350,240); // 禁止改变窗口大小。
    win.setCentralWidget(&window);
    win.show();

    return app.exec();
}
