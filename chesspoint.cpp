#include "chesspoint.h"

ChessPoint::ChessPoint(QWidget *parent) : QWidget(parent)
{

}

void ChessPoint::give_value(int x, int y)
{
    int size = 90;
    heng = x/size;
    shu = y/size;
}
