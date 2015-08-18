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

private:
    WebView* m_view;
};

#endif
