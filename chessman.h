#ifndef CHESSMAN_H
#define CHESSMAN_H
#include<QImage>
#include<QPainter>
class chessman
{
public:
    chessman(int a, int b,int color);
    void show(QPainter *painter);
private:
    static QImage _black;
    static QImage _white;
    static const int N=35;
    int col;
    int x;
    int y;
};

#endif // CHESSMAN_H
