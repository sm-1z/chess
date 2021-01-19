#include "chessengine.h"


int m_BaseValue[15] = {0, 10000, 1000, 420, 480, 170, 160, 60, 10000, 1000, 420, 480, 170, 160, 60};
int m_FlexValue[15] = {0, 6, 12, 6, 1, 1, 15, 0, 6, 12, 6, 1, 1, 15};


Chessengine::Chessengine(QWidget *parent) : QWidget(parent)
{

}

int Chessengine::GetPosisionValue(int x, int y)
{
    switch (number[x][y]) {
    case R_CAR:
        return R_CAR_BA[x][y];
        break;
    case G_CAR:
        return G_CAR_BA[x][y];
        break;
    case R_HORSE:
        return R_HORSE_BA[x][y];
        break;
    case G_HORSE:
        return G_HORSE_BA[x][y];
        break;
    case R_CANON:
        return R_CANON_BA[x][y];
        break;
    case G_CANON:
        return G_CANON_BA[x][y];
        break;
    case R_PAWN:
        return R_PAWN_BA[x][y];
        break;
    case G_PAWN:
        return G_PAWN_BA[x][y];
        break;
    case R_ELEPHANT:
        return R_ELEPHANT_BA[x][y];
        break;
    case G_ELEPHANT:
        return G_ELEPHANT_BA[x][y];
        break;
    case R_BISHOP:
        return R_BISHOP_BA[x][y];
        break;
    case G_BISHOP:
        return G_BISHOP_BA[x][y];
        break;
    case R_KING:
        return R_KING_BA[x][y];
        break;
    case G_KING:
        return G_KING_BA[x][y];
        break;
    default:
        return 0;
    }
}
