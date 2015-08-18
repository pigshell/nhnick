#include "webview.h"

#include <QWebFrame>
#include <QWebPage>
#include <QPainter>

WebView::WebView(QWidget* parent)
    : QWidget(parent), renderHints(QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform), m_webpage(0), m_qwebpage(0), readonly(false)
{
    setAttribute(Qt::WA_InputMethodEnabled);
    setAcceptDrops(true);
    setMouseTracking(true);
    setFocusPolicy(Qt::WheelFocus);
}

WebView::~WebView()
{
}

WebPage* WebView::page()
{
    return m_webpage;
}

void WebView::setPage(WebPage* wp, QWebPage* qwp, bool ro)
{
    m_webpage = wp;
    m_qwebpage = qwp;
    readonly = ro;
}

void WebView::paintEvent(QPaintEvent *ev)
{
    if (m_webpage) {
        QWebFrame* frame = m_webpage->mainFrame();
        QPainter p(this);
        p.setRenderHints(renderHints);
        frame->render(&p, ev->region());
    }
}

void WebView::handleRepaintRequested(const int x, const int y, const int width, const int height)
{
    if (m_webpage) {
        update(x, y, width, height);
    }
}

void WebView::handleScrollRequested(int x, int y, const QRect& scrollViewRect)
{
    update();
}

void WebView::mouseMoveEvent(QMouseEvent* ev)
{
    if (m_webpage) {
        const bool accepted = ev->isAccepted();
        m_qwebpage->event(ev);
        ev->setAccepted(accepted);
    }
}

void WebView::mousePressEvent(QMouseEvent* ev)
{
    if (m_webpage) {
        const bool accepted = ev->isAccepted();
        m_qwebpage->event(ev);
        ev->setAccepted(accepted);
    }
}

void WebView::mouseDoubleClickEvent(QMouseEvent* ev)
{
    if (m_webpage) {
        const bool accepted = ev->isAccepted();
        m_qwebpage->event(ev);
        ev->setAccepted(accepted);
    }
}

void WebView::mouseReleaseEvent(QMouseEvent* ev)
{
    if (m_webpage) {
        const bool accepted = ev->isAccepted();
        m_qwebpage->event(ev);
        ev->setAccepted(accepted);
    }
}

void WebView::wheelEvent(QWheelEvent* ev)
{
    if (m_webpage) {
        const bool accepted = ev->isAccepted();
        m_qwebpage->event(ev);
        ev->setAccepted(accepted);
    }
}

void WebView::stop()
{
}

void WebView::back()
{
}

void WebView::forward()
{
}

void WebView::reload()
{
}
