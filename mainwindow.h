#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QMouseEvent>
#include <QMainWindow>
#include"state.h"
#include"chessman.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;
    state _mystate;

};

#endif // MAINWINDOW_H
