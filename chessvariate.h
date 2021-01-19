#ifndef CHESSVARIATE_H
#define CHESSVARIATE_H

#define NOCHESS 0
#define R_KING 1 //红帅
#define R_CAR 2 //红车
#define R_HORSE 3 //红马
#define R_CANON 4 //红炮
#define R_BISHOP 5 //红士
#define R_ELEPHANT 6 //红相
#define R_PAWN 7 //红兵
#define R_BEGIN R_KING
#define R_END R_PAWN
#define G_KING 8 //绿将
#define G_CAR 9 //绿车
#define G_HORSE 10 //绿马
#define G_CANON 11 //绿炮
#define G_BISHOP 12 //绿士
#define G_ELEPHANT 13 //绿象
#define G_PAWN 14 //绿卒
#define G_BEGIN G_KING
#define G_END G_PAWN
#define CRed -1
#define CmkGreen -2
#define ISred(x) (x>=R_BEGIN && x<=R_END)
#define ISgreen(x) (x>=G_BEGIN && x<=G_END)
#define IsSameSide(x,y) ((ISred(x)&&ISred(y))||(ISgreen(x)&&ISgreen(y)))

#include <QWidget>
#include <QDebug>
#include <chesspoint.h>

extern int number[11][10];//棋盘二维数组

class Chessvariate : public QWidget
{
    Q_OBJECT
public:
    explicit Chessvariate(QWidget *parent = nullptr);

    static void pictureID_to_ChessID(int x);//转换函数
    static bool ISCanMove(int From_heng,int From_shu, int To_heng, int To_shu);//判断函数
    static bool ISValidMove(int From_heng,int From_shu, int To_heng, int To_shu);//判断函数进阶


signals:

};

#endif // CHESSVARIATE_H
