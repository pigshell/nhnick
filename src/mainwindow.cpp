#include <QtWidgets>
#include <QtWebKitWidgets>
#include "mainwindow.h"
#include "webview.h"

MainWindow::MainWindow()
    :QMainWindow()
{
    m_view = new WebView(this);
    QToolBar* toolBar = addToolBar(tr("Navigation"));
    /*
    toolBar->addAction(view->pageAction(QWebPage::Back));
    toolBar->addAction(view->pageAction(QWebPage::Forward));
    toolBar->addAction(view->pageAction(QWebPage::Reload));
    toolBar->addAction(view->pageAction(QWebPage::Stop));
    */
    setCentralWidget(m_view);
}

MainWindow::~MainWindow()
{
    delete m_view;
}

WebView* MainWindow::view()
{
    return m_view;
}
