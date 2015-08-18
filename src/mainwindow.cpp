#include <QtWidgets>
#include <QtWebKitWidgets>
#include "mainwindow.h"
#include "webview.h"

MainWindow::MainWindow()
    :QMainWindow()
{
    m_view = new WebView(this);
    
    backAct = new QAction(tr("&Back"), this);
    forwardAct = new QAction(tr("&Forward"), this);
    reloadAct = new QAction(tr("&Reload"), this);
    stopAct = new QAction(tr("&Stop"), this);
    connect(backAct, SIGNAL(triggered()), m_view, SLOT(back()));
    connect(forwardAct, SIGNAL(triggered()), m_view, SLOT(forward()));
    connect(reloadAct, SIGNAL(triggered()), m_view, SLOT(reload()));
    connect(stopAct, SIGNAL(triggered()), m_view, SLOT(stop()));

    location = new QLineEdit(this);
    connect(location, SIGNAL(returnPressed()), this, SLOT(urlEntered()));
    connect(m_view, SIGNAL(urlChanged(const QUrl&)), this, SLOT(urlChanged(const QUrl&)));

    QToolBar* toolBar = addToolBar(tr("Navigation"));
    toolBar->addAction(backAct);
    toolBar->addAction(forwardAct);
    toolBar->addAction(reloadAct);
    toolBar->addAction(stopAct);
    toolBar->addWidget(location);

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

void MainWindow::urlEntered()
{
    QString url = location->text();
    m_view->handleUrlEntered(url);
}

void MainWindow::urlChanged(const QUrl& url)
{
    location->setText(url.toString());
}
