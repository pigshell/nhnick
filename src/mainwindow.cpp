/*
  Copyright (C) 2015 Coriolis Technologies Pvt Ltd, info@coriolis.co.in
  Author: Ganesh Varadarajan

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.
  
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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
