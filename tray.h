#ifndef TRAY_H
#define TRAY_H
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QWidget>
#include <QObject>
#include <QMainWindow>

class MyTray : public QWidget
{
    Q_OBJECT
public:
    MyTray(QWidget *parent);
private:
    QSystemTrayIcon *trayIcon;
    QMenu *tray_menu;
    QAction *action_show;
    QAction *action_hide;
    QWidget *par;
};

#endif // TRAY_H

