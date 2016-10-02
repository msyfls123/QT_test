#include <QSystemTrayIcon>
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QWidget>
#include <QObject>
#include "tray.h"

MyTray::MyTray(QWidget *parent):
    par(parent)
{
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setToolTip(QString("I'm tray"));
    trayIcon->setIcon(QIcon(":/images/system-tray"));
    tray_menu = new QMenu();
    action_show = new QAction(tray_menu);
    action_show->setText(QString("显示"));
    action_show->setIcon(QIcon(":/images/system-show"));
    action_hide = new QAction(tray_menu);
    action_hide->setText(QString("隐藏"));
    action_hide->setIcon(QIcon(":/images/system-hide"));
    QObject::connect(action_show, &QAction::triggered, par, &QMainWindow::show);
    QObject::connect(action_hide, &QAction::triggered, par, &QMainWindow::hide);
    tray_menu->addAction(action_show);
    tray_menu->addAction(action_hide);
    trayIcon->setContextMenu(tray_menu);
    trayIcon->show();
}
