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
    WebPage* page;
    QWebPage* wpage;

protected:
    void paintEvent(QPaintEvent *ev);
    void mouseMoveEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void wheelEvent(QWheelEvent*);

public slots:
    void render(const int x, const int y, const int width, const int height);
    void scroll(int x, int y, const QRect& scrollViewRect);

private:
    QPainter::RenderHints renderHints;
};

#endif
