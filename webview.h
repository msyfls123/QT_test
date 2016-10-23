#ifndef WEBVIEW_H
#define WEBVIEW_H
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QObject>

class Webpage : public QWebEnginePage
{
    Q_OBJECT
public:
    Webpage(QObject *parent = Q_NULLPTR);
private slots:
    void hover(const QString &url);
protected:
    QWebEnginePage *createWindow(QWebEnginePage::WebWindowType type) Q_DECL_OVERRIDE;
private:
    friend class Webview;
    QUrl tempUrl;
};

class Webview : public QWebEngineView
{
    Q_OBJECT

public:
    Webview(QWidget *parent = Q_NULLPTR);
    Webpage *webPage() const { return m_page; }
    void setPage(Webpage *page);
protected:

private:
    Webpage *m_page;
};



#endif // WEBVIEW_H
