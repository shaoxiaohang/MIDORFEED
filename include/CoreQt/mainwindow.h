#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QOpenGLWindow>>

namespace Ui {
class MainWindow;
}

class MainWindow : public QOpenGLWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
