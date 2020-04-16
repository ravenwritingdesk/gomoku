#include "state.h"
#include<iostream>
#include<iomanip>
#include<cstdlib>
using namespace std;
const long long int INF=10000000;


state::state()
{
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<15;j++)
        {
            _state[i][j]=0;
        }
    }
}

void state::put_chess(int i, int j,int color)
{
    chessman temp(i,j,color);

    _state[i][j]=color;

    _chess.push_back(temp);
    if(color == -1)
        cout<<"black "<<i<<" "<<j<<endl;
    else
        cout<<"white "<<i<<" "<<j<<endl;
}
bool state::black_win_check()
{
    int i,j;//判断横着的5个是否都相等
    for(i=0;i<=14;i++)
    for(j=0;j<=14;j++)
    if( _state[i][j]==-1&&_state[i][j+1]==-1&&_state[i][j+2]==-1&&_state[i][j+3]==-1&&_state[i][j+4]==-1)
    return 1;
    for(j=0;j<=14;j++)//判断竖着的5个是否都相等
    for(i=0;i<=14;i++)
    if(_state[i][j]==-1&&_state[i+1][j]==-1&&_state[i+2][j]==-1&&_state[i+3][j]==-1&&_state[i+4][j]==-1)
    return 1;
    for(i=0;i<=14;i++)//判断左斜5个
    for(j=0;j<=14;j++)
    if(_state[i][j]==-1&&_state[i+1][j+1]==-1&&_state[i+2][j+2]==-1&&_state[i+3][j+3]==-1&&_state[i+4][j+4]==-1)
    return 1;
    for(i=0;i<=14;i++)//右斜5个
    for(j=14;j>=0;j--)
    if(_state[i][j]==-1&&_state[i+1][j-1]==-1&&_state[i+2][j-2]==-1&&_state[i+3][j-3]==-1&&_state[i+4][j-4]==-1)
    return 1;

    return false;
}
bool state::white_win_check()
{
    int i,j;//判断横着的5个是否都相等
    for(i=0;i<=14;i++)
    for(j=0;j<=14;j++)
    if( _state[i][j]==1&&_state[i][j+1]==1&&_state[i][j+2]==1&&_state[i][j+3]==1&&_state[i][j+4]==1)
    return 1;
    for(j=0;j<=14;j++)//判断竖着的5个是否都相等
    for(i=0;i<=14;i++)
    if(_state[i][j]==1&&_state[i+1][j]==1&&_state[i+2][j]==1&&_state[i+3][j]==1&&_state[i+4][j]==1)
    return 1;
    for(i=0;i<=14;i++)//判断左斜5个
    for(j=0;j<=14;j++)
    if(_state[i][j]==1&&_state[i+1][j+1]==1&&_state[i+2][j+2]==1&&_state[i+3][j+3]==1&&_state[i+4][j+4]==1)
    return 1;
    for(i=0;i<=14;i++)//右斜5个
    for(j=14;j>=0;j--)
    if(_state[i][j]==1&&_state[i+1][j-1]==1&&_state[i+2][j-2]==1&&_state[i+3][j-3]==1&&_state[i+4][j-4]==1)
    return 1;
    return 0;
    return false;

}



void state::react()
{  
    int x,y;
    AI(&x,&y);
    put_chess(y,x,1);
}
int state::positionValue(int row, int col)
{
    int n = 1, k = 0, k1, k2, K1, K2, X1, Y1, Z1, X2, Y2, Z2, temp;

        int a[2][4][4] = { 40,400,3000,10000,6,10,600,10000,20,120,200,0,6,10,500,0,30,300,2500,5000,2,8,300,8000,26,160,0,0,4,20,300,0 };

        /* 数组a中储存己方和对方共32种棋型的值  己方0对方1    活0冲1空活2空冲3    子数0-3（0表示1个子，3表示4个子） */

        while (n != 5) {

            k1 = chessType(n, row, col); n += 4;            /* k1,k2为2个反方向的棋型编号 */

            k2 = chessType(n, row, col); n -= 3;

            if (k1>k2) { temp = k1; k1 = k2; k2 = temp; }  /* 使编号小的为k1,大的为k2 */

            K1 = k1; K2 = k2;       /* K1 K2储存k1 k2的编号 */

            Z1 = k1 % 10; Z2 = k2 % 10; k1 /= 10; k2 /= 10; Y1 = k1 % 10; Y2 = k2 % 10; k1 /= 10; k2 /= 10; X1 = k1 % 10; X2 = k2 % 10;

            /* X Y Z分别表示 己方0对方1    活0冲1空活2空冲3    子数0-3（0表示1个子，3表示4个子） */

            if (K1 == -1) { if (K2<0) { k += 0; continue; } else k += a[X2][Y2][Z2] + 5; continue; };    /* 空棋型and其他 */

            if (K1 == -2) { if (K2<0) { k += 0; continue; } else k += a[X2][Y2][Z2] / 2; continue; };       /* 边界冲棋型and其他 */

            if (K1 == -3) { if (K2<0) { k += 0; continue; } else k += a[X2][Y2][Z2] / 3; continue; };    /* 边界空冲棋型and其他 */

            if (((K1>-1 && K1<4) && ((K2>-1 && K2<4) || (K2>9 && K2<14))) || ((K1>99 && K1<104) && ((K2>99 && K2<104) || (K2>109 && K2<114)))) {

                /* 己活己活 己活己冲 对活对活 对活对冲 的棋型赋值*/

                if (Z1 + Z2 >= 2) { k += a[X2][Y2][3]; continue; }

                else { k += a[X2][Y2][Z1 + Z2 + 1]; continue; }

            }

            if (((K1>9 && K1<14) && (K2>9 && K2<14)) || ((K1>109 && K1<114) && (K2>109 && K2<114))) {

                /* 己冲己冲 对冲对冲 的棋型赋值*/

                if (Z1 + Z2 >= 2) { k += 10000; continue; }

                else { k += 0; continue; }

            }

            if (((K1>-1 && K1<4) && ((K2>99 && K2<104) || (K2>109 && K2<114))) || ((K1>9 && K1<14) && ((K2>99 && K2<104) || (K2>109 && K2<114)))) {

                /* 己活对活 己活对冲 己冲对活 己冲对冲 的棋型赋值*/

                if (Z1 == 3 || Z2 == 3) { k += 10000; continue; }

                else { k += a[X2][Y2][Z2] + a[X1][Y1][Z1] / 4; continue; }

            }

            else { k += a[X1][Y1][Z1] + a[X2][Y2][Z2]; continue; }    /* 其他棋型的赋值 */

        }

        return k;
}
int state::chessType(int n, int p, int q)
{
    int k, m = 0;  /* 棋型号注解:  己活000-003 己冲010-013 对活100-103 对冲110-113 己空活020-023 己空冲030-033 对空活120-123 对空冲130-133 空-1 边界冲-2 边界空冲-3*/

        goStep(n, &p, &q);

        if (p<0 || p>14 || q<0 || q>14) k = -2;                                      /* 边界冲棋型 */

        switch (_state[q+1][p+1]) {

        case 1: {

            m++; goStep(n, &p, &q);

            if (p<0 || p>14 || q<0 || q>14) { k = m + 9; return k; }

            while (_state[q+1][p+1] == 1) { m++; goStep(n, &p, &q); if (p<0 || p>14 || q<0 || q>14) { k = m + 9; return k; } }

            if (_state[q+1][p+1] == 0) k = m - 1;                         /* 己方活棋型 */

            else k = m + 9;                                         /* 己方冲棋型 */

        }break;

        case -1: {

            m++; goStep(n, &p, &q);

            if (p<0 || p>14 || q<0 || q>14) { k = m + 109; return k; }

            while (_state[q+1][p+1] == -1) { m++; goStep(n, &p, &q); if (p<0 || p>14 || q<0 || q>14) { k = m + 109; return k; } }

            if (_state[q+1][p+1] == 0) k = m + 99;                         /* 对方活棋型 */

            else k = m + 109;                                        /* 对方冲棋型 */

        }break;

        case 0: {

            goStep(n, &p, &q);

            if (p<0 || p>14 || q<0 || q>14) { k = -3; return k; }         /* 边界空冲棋型 */

            switch (_state[q+1][p+1]) {

            case 1: {

                m++; goStep(n, &p, &q);

                if (p<0 || p>14 || q<0 || q>14) { k = m + 29; return k; }

                while (_state[q+1][p+1] == 1) { m++; goStep(n, &p, &q); if (p<0 || p>14 || q<0 || q>14) { k = m + 29; return k; } }

                if (_state[q+1][p+1] == 0) k = m + 19;                      /* 己方空活棋型 */

                else k = m + 29;                                      /* 己方空冲棋型 */

            }break;

            case -1: {

                m++; goStep(n, &p, &q);

                if (p<0 || p>14 || q<0 || q>14) { k = m + 129; return k; }

                while (_state[q+1][p+1] == -1) { m++; goStep(n, &p, &q); if (p<0 || p>14 || q<0 || q>14) { k = m + 129; return k; } }

                if (_state[q+1][p+1] == 0) k = m + 119;                     /* 对方空活棋型 */

                else k = m + 129;                                     /* 对方空冲棋型 */

            }break;

            case 0: k = -1; break;                                         /* 空棋型 */

            }

        }break;

        }

        return k;
}


void state::show(QPainter *painter)
{
    int i;
    for(i=0;i<_chess.size();i++)
    {
        _chess[i].show(painter);
    }
}
void state::goStep(int n, int *i, int *j)
{
    switch (n) {

        case 1: *i += 1; break;

        case 2: *i += 1; *j += 1; break;

        case 3: *j += 1; break;

        case 4: *i -= 1; *j += 1; break;

        case 5: *i -= 1; break;

        case 6: *i -= 1; *j -= 1; break;

        case 7: *j -= 1; break;

        case 8: *i += 1; *j -= 1; break;

        }
}
void state::AI(int *p, int *q)
{
    int i, j, value, max = 0, bestRow, bestCol;        /* I J为下点坐标 */

        for (j = 0;j<15; j++)

            for (i = 0; i<15; i++)

                if (_state[j][i] == 0) {      /* 历遍棋盘，遇到空点则计算价值，取最大价值点下子。 */

                    value = positionValue(i-1, j-1);

                    if (value >= max) { bestRow = i; bestCol = j; max = value; }

                }


        *p = bestRow; *q = bestCol;
}
