#include "webview.h"
#include "phantom.h"

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
    setPage(0, 0);
}

WebPage* WebView::page()
{
    return m_webpage;
}

void WebView::setPage(WebPage* wp, QWebPage* qwp, bool ro)
{
    if (m_webpage) {
        m_webpage->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
        m_webpage->mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
        disconnect(0, 0, this, 0);
    }

    m_webpage = wp;
    m_qwebpage = qwp;
    readonly = ro;

    if (!m_webpage) {
        return;
    }

    m_qwebpage->setViewportSize(size());
    m_webpage->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAsNeeded);
    m_webpage->mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAsNeeded);
    connect(m_webpage, SIGNAL(repaintRequested(const int, const int, const int, const int)), this, SLOT(handleRepaintRequested(const int, const int, const int, const int)));
    connect(m_qwebpage, SIGNAL(scrollRequested(int, int, const QRect&)), this, SLOT(handleScrollRequested(int, int, const QRect&)));
    connect(m_webpage, SIGNAL(urlChanged(const QUrl&)), this, SLOT(handleUrlChanged(const QUrl&)));
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
    if (m_webpage) {
        m_webpage->stop();
    }
}

void WebView::back()
{
    if (m_webpage) {
        m_webpage->goBack();
    }
}

void WebView::forward()
{
    if (m_webpage) {
        m_webpage->goForward();
    }
}

void WebView::reload()
{
    if (m_webpage) {
        m_webpage->reload();
    }
}

void WebView::handleUrlChanged(const QUrl& url)
{
    emit urlChanged(url);
}

void WebView::handleUrlEntered(const QString& url)
{
    if (m_webpage) {
        QVariant op("get");
        m_webpage->openUrl(url, op, Phantom::instance()->defaultPageSettings());
    }
}
