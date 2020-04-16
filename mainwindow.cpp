#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QImage>
#include<QPainter>
#include<iostream>
#include <QMessageBox>
using namespace std;
int mouse_flag=0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),_mystate(),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _mystate.put_chess(7,7,1); // you can put a chess first.
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QPoint p=event->pos();
        int m=(p.x()-22)/35.0+0.5;
        int n=(p.y()-22)/35.0+0.5;
        //cout<<"black "<<m<<" "<<n<<endl;

        _mystate.put_chess(m,n,-1);
        if(_mystate.black_win_check()==true)
        {
            QMessageBox::information(NULL, "恭喜", "祝贺你，你赢了", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        }
        /*now is your turn*/
        else
        {
            _mystate.react();
            if(_mystate.white_win_check()==true)
            {
                QMessageBox::information(NULL, "抱歉", "很遗憾，你输了", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            }
        }

    }
    repaint();

}
void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter *pa;
    pa=new QPainter();
    pa->begin(this);
    pa->drawPixmap(rect(),QPixmap(":/images/state.bmp"));//you need to change the pic address

    _mystate.show(pa);
    pa->end();
    delete pa;
}
