#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <QtWidgets>

class WebView;
class QLineEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
    WebView* view();

public slots:
    void urlChanged(const QUrl& url);

private slots:
    void urlEntered();

private:
    WebView* m_view;
    QLineEdit* location;

    QAction* backAct;
    QAction* forwardAct;
    QAction* reloadAct;
    QAction* stopAct;
};

#endif
