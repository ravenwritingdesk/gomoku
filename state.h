#ifndef STATE_H
#define STATE_H
#include<QImage>
#include"chessman.h"
#include<vector>
#include"QPainter"
using namespace std;
class state
{
public:
    state();
    void put_chess(int i, int j, int color);
    void show(QPainter *painter);
    bool black_win_check();
    bool white_win_check();
    void react();
    int positionValue(int row, int col);
    int chessType(int n, int p, int q);
    void goStep(int n, int *i, int *j);
    void AI(int *p, int *q);


private:
    vector<chessman> _chess; // to store each chessman
    int _state[15][15];// the chessboard is 15x15, number from 0 to 14

};

#endif // STATE_H
