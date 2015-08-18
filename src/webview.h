#ifndef WEBVIEW_H
#define WEBVIEW_H

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

protected:
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void wheelEvent(QWheelEvent*);

public slots:
    void stop();
    void back();
    void forward();
    void reload();

    void handleRepaintRequested(const int x, const int y, const int width, const int height);
    void handleScrollRequested(int x, int y, const QRect& scrollViewRect);

private:
    QPainter::RenderHints renderHints;
    WebPage* m_webpage;
    QWebPage* m_qwebpage;
    bool readonly;
};

#endif
