#include "webview.h"
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QUrl>
#include <QDebug>

Webview::Webview(QWidget *parent):
    QWebEngineView(parent)
  , m_page(0)
{
  m_page = new Webpage(this);
  setPage(m_page);
  m_page->load(QUrl("http://msyfls123.github.io"));
}

Webpage::Webpage(QObject *parent):
    QWebEnginePage(parent)
{
  qDebug() << "Im webpage";
  connect(this, &QWebEnginePage::linkHovered,this,&Webpage::hover);
}

void Webview::setPage(Webpage *_page)
{
    qDebug() << "webpage load";
    QWebEngineView::setPage(_page);
}


void Webpage::hover(const QString &url)
{
    qDebug() << url;
    tempUrl = url;
}

QWebEnginePage *Webpage::createWindow(QWebEnginePage::WebWindowType type=QWebEnginePage::WebBrowserWindow)
{
  qDebug() << "Hello!";
  qDebug() << this->tempUrl;
  this->load(this->tempUrl);
//  this->load(QUrl("http://msyfls123.github.io"));
  if (type == QWebEnginePage::WebBrowserTab) {
      qDebug() << "WebBrowserTab!";
      return this;
  } else if (type == QWebEnginePage::WebBrowserBackgroundTab) {
      qDebug() << "WebBrowserBackgroundTab!";
      return this;
  } else if (type == QWebEnginePage::WebBrowserWindow) {
      qDebug() << "WebBrowserWindow!";
      return this;
  } else {
      qDebug() << "else!";
      return this;
  }
}

