#ifndef _WEBVIEW_H
#define _WEBVIEW_H

#include <QtWidgets>
#include <QtWebKitWidgets/QWebPage>
#include "webpage.h"

class WebView: public QWidget {
    Q_OBJECT

public:
    WebView(QWidget* parent = 0);
    ~WebView();
    WebPage* page();
    void setPage(WebPage* wp, QWebPage* qwp, bool readonly = false);
    void handleUrlEntered(const QString& url);

protected:
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void wheelEvent(QWheelEvent*);

signals:
    void urlChanged(const QUrl& url);

public slots:
    void stop();
    void back();
    void forward();
    void reload();

    void handleUrlChanged(const QUrl& url);

    void handleRepaintRequested(const int x, const int y, const int width, const int height);
    void handleScrollRequested(int x, int y, const QRect& scrollViewRect);

private:
    QPainter::RenderHints renderHints;
    WebPage* m_webpage;
    QWebPage* m_qwebpage;
    bool readonly;
};

#endif
