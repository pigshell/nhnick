#include "webview.h"

#include <QWebFrame>
#include <QWebPage>
#include <QPainter>

WebView::WebView(QWidget* parent)
    : QWidget(parent), renderHints(QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform)
{
    page = 0;
    wpage = 0;
    setAttribute(Qt::WA_InputMethodEnabled);
    setAttribute(Qt::WA_AcceptTouchEvents);
    setAcceptDrops(true);
    setMouseTracking(true);
    setFocusPolicy(Qt::WheelFocus);
}

WebView::~WebView()
{
}

void WebView::paintEvent(QPaintEvent *ev)
{
    if (page) {
        QWebFrame* frame = page->mainFrame();
        QPainter p(this);
        p.setRenderHints(renderHints);
        frame->render(&p, ev->region());
    }
}

void WebView::render(const int x, const int y, const int width, const int height)
{
    if (page) {
        update(x, y, width, height);
    }
}

void WebView::scroll(int x, int y, const QRect& scrollViewRect)
{
    qDebug() << __PRETTY_FUNCTION__;
}

void WebView::mouseMoveEvent(QMouseEvent* ev)
{
    if (page) {
        const bool accepted = ev->isAccepted();
        wpage->event(ev);
        ev->setAccepted(accepted);
    }
}

void WebView::mousePressEvent(QMouseEvent* ev)
{
    if (page) {
        const bool accepted = ev->isAccepted();
        wpage->event(ev);
        ev->setAccepted(accepted);
    }
}

void WebView::mouseDoubleClickEvent(QMouseEvent* ev)
{
    if (page) {
        const bool accepted = ev->isAccepted();
        wpage->event(ev);
        ev->setAccepted(accepted);
    }
}

void WebView::mouseReleaseEvent(QMouseEvent* ev)
{
    if (page) {
        const bool accepted = ev->isAccepted();
        wpage->event(ev);
        ev->setAccepted(accepted);
    }
}

void WebView::wheelEvent(QWheelEvent* ev)
{
    if (page) {
        const bool accepted = ev->isAccepted();
        wpage->event(ev);
        ev->setAccepted(accepted);
    }
}
