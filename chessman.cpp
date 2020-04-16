#include "chessman.h"
#include<QRect>
QImage chessman::_black=QImage(":/images/black(1).png");// you need to change the pic address
QImage chessman::_white=QImage(":/images/white(1).png");
chessman::chessman(int a, int b, int color)
{
    x=a;
    y=b;
    col=color;

}
void chessman::show(QPainter *painter)
{
    if(col==-1)
    painter->drawImage(QRect(x*N+14,y*N+14,20,20),QImage(":/images/black(1).png"),QRect(0,0,84,84));
    else
    painter->drawImage(QRect(x*N+14,y*N+14,20,20),QImage(":/images/white(1).png"),QRect(0,0,84,84));
}

