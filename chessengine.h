#ifndef CHESSENGINE_H
#define CHESSENGINE_H

#include <QWidget>
#include "chessvariate.h"

extern int m_BaseValue[15];
extern int m_FlexValue[15];


class Chessengine : public QWidget
{
    Q_OBJECT
public:
    explicit Chessengine(QWidget *parent = nullptr);
    int R_PAWN_BA[11][10] = {
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 0, 3, 6, 9, 12, 9, 6, 3, 0},
        {2, 18, 36, 56, 80, 120, 80, 56, 36, 18},
        {3, 14, 26, 42, 60, 80, 60, 42, 26, 14},
        {4, 10, 20, 30, 34, 40, 34, 30, 20, 10},
        {5, 6, 12, 18, 18, 20, 18, 18, 12, 6},
        {6, 2, 0, 8, 0, 8, 0, 8, 0, 2},
        {7, 0, 0, -2, 0, 4, 0, 2, 0, 0},
        {8, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {10, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
    int G_PAWN_BA[11][10] = {
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {4, 0, 0, -2, 0, 4, 0, 2, 0, 0},
        {5, 2, 0, 8, 0, 8, 0, 8, 0, 2},
        {6, 6, 12, 18, 18, 20, 18, 18, 12, 6},
        {7, 10, 20, 30, 34, 40, 34, 30, 20, 10},
        {8, 14, 26, 42, 60, 80, 60, 42, 26, 14},
        {9, 18, 36, 56, 80, 120, 80, 56, 36, 18},
        {10, 0, 3, 6, 9, 12, 9, 6, 3, 0},
    };
    int G_CAR_BA[11][10] = {
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, -1, 6, 2, 8, 7, 8, 2, 6, -1},
        {2, 5, 2, 5, 10, 5, 10, 10, 2, 5},
        {3, 2, 5, 3, 9, 7, 9, 3, 5, 2},
        {4, 3, 6, 5, 9, 9, 9, 5, 6, 3},
        {5, 7, 10, 9, 12, 12, 12, 9, 10, 7},
        {6, 7, 9, 7, 11, 11, 11, 7, 9, 7},
        {7, 7, 11, 10, 14, 14, 14, 10, 11, 7},
        {8, 7, 7, 7, 11, 11, 11, 7, 7, 7},
        {9, 10, 12, 12, 15, 16, 15, 11, 12, 10},
        {10, 9, 9, 7, 11, 10, 11, 7, 9, 9},
    };
    int R_CAR_BA[11][10] = {
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 9, 9, 7, 11, 10, 11, 7, 9, 9},
        {2, 10, 12, 12, 15, 16, 15, 11, 12, 10},
        {3, 7, 7, 7, 11, 11, 11, 7, 7, 7},
        {4, 7, 11, 10, 14, 14, 14, 10, 11, 7},
        {5, 7, 9, 7, 11, 11, 11, 7, 9, 7},
        {6, 7, 10, 9, 12, 12, 12, 9, 10, 7},
        {7, 3, 6, 5, 9, 9, 9, 5, 6, 3},
        {8, 2, 5, 3, 9, 7, 9, 3, 5, 2},
        {9, 5, 2, 5, 10, 5, 10, 10, 2, 5},
        {10, -1, 6, 2, 8, 7, 8, 2, 6, -1},
    };
    int G_HORSE_BA[11][10] = {
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 0, -2, 0, 0, 0, 0, 0, -2, 0},
        {2, 0, 1, 2, 2, -1, 2, 2, 1, 0},
        {3, 2, 1, 5, 5, 2, 5, 5, 1, 2},
        {4, 1, 3, 5, 3, 6, 3, 5, 3, 1},
        {5, 2, 7, 10, 9, 7, 9, 10, 7, 2},
        {6, 3, 10, 9, 11, 10, 11, 9, 10, 3},
        {7, 5, 15, 11, 15, 12, 15, 11, 15, 5},
        {8, 7, 9, 10, 12, 11, 12, 10, 9, 7},
        {9, 2, 6, 17, 10, 5, 10, 17, 6, 2},
        {10, 2, 5, 10, 7, 2, 7, 10, 5, 2},
    };
    int R_HORSE_BA[11][10] = {
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 2, 5, 10, 7, 2, 7, 10, 5, 2},
        {2, 2, 6, 17, 10, 5, 10, 17, 6, 2},
        {3, 7, 9, 10, 12, 11, 12, 10, 9, 7},
        {4, 5, 15, 11, 15, 12, 15, 11, 15, 5},
        {5, 3, 10, 9, 11, 10, 11, 9, 10, 3},
        {6, 2, 7, 10, 9, 7, 9, 10, 7, 2},
        {7, 1, 3, 5, 3, 6, 3, 5, 3, 1},
        {8, 2, 1, 5, 5, 2, 5, 5, 1, 2},
        {9, 0, 1, 2, 2, -1, 2, 2, 1, 0},
        {10, 0, -2, 0, 0, 0, 0, 0, -2, 0},
    };
    int R_CANON_BA[11][10] = {
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 0, 0, 1, 3, 3, 3, 1, 0, 0},
        {2, 0, 1, 2, 3, 3, 3, 2, 1, 0},
        {3, 2, 0, 5, 3, 6, 3, 5, 0, 2},
        {4, 0, 0, 0, 1, 2, 1, 0, 0, 0},
        {5, -1, 0, 2, 1, 3, 1, 2, 0, -1},
        {6, 0, 0, 0, 1, 5, 1, 0, 0, 0},
        {7, 0, 0, -1, 2, 6, 2, -1, 0, 0},
        {8, 1, 1, 0, -6, -5, -6, 0, 1, 1},
        {9, 1, 1, 0, -2, -9, -2, 0, 1, 1},
        {10, 3, 2, 0, -6, -7, -6, 0, 1, 2},
    };
    int G_CANON_BA[11][10] = {
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 3, 2, 0, -6, -7, -6, 0, 1, 2},
        {2, 1, 1, 0, -2, -9, -2, 0, 1, 1},
        {3, 1, 1, 0, -6, -5, -6, 0, 1, 1},
        {4,  0, 0, -1, 2, 6, 2, -1, 0, 0},
        {5, 0, 0, 0, 1, 5, 1, 0, 0, 0},
        {6, -1, 0, 2, 1, 3, 1, 2, 0, -1},
        {7, 0, 0, 0, 1, 2, 1, 0, 0, 0},
        {8, 2, 0, 5, 3, 6, 3, 5, 0, 2},
        {9, 0, 1, 2, 3, 3, 3, 2, 1, 0},
        {10, 0, 0, 1, 3, 3, 3, 1, 0, 0},
    };
    int G_ELEPHANT_BA[11][10] = {
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 0, 0, 5, 0, 0, 0, 5, 0, 0},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {3, 2, 0, 0, 0, 10, 0, 0, 0, 2},
        {4, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {5, 0, 0, 1, 0, 0, 0, 1, 0, 0},
        {6, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {8, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {10, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
    int R_ELEPHANT_BA[11][10] = {
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {4, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {5, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {6, 0, 0, 1, 0, 0, 0, 1, 0, 0},
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {8, 2, 0, 0, 0, 10, 0, 0, 0, 2},
        {9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {10, 0, 0, 5, 0, 0, 0, 5, 0, 0},
    };
    int G_BISHOP_BA[11][10] = {
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 0, 0, 0, 5, 0, 5, 0, 0, 0},
        {2, 0, 0, 0, 0, 10, 0, 0, 0, 0},
        {3, 0, 0, 0, 2, 0, 2, 0, 0, 0},
        {4, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {5, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {6, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {8, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {10, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
    int R_BISHOP_BA[11][10] = {
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {4, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {5, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {6, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {8, 0, 0, 0, 2, 0, 2, 0, 0, 0},
        {9, 0, 0, 0, 0, 10, 0, 0, 0, 0},
        {10, 0, 0, 0, 5, 0, 5, 0, 0, 0},
    };
    int G_KING_BA[11][10] = {
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 0, 0, 0, 5, 10, 5, 0, 0, 0},
        {2, 0, 0, 0, 2, 3, 2, 0, 0, 0},
        {3, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {4, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {5, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {6, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {8, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {10, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
    int R_KING_BA[11][10] = {
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {4, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {5, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {6, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {8, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {9, 0, 0, 0, 2, 3, 2, 0, 0, 0},
        {10, 0, 0, 0, 5, 10, 5, 0, 0, 0},
    };
    int GetPosisionValue(int x, int y);

signals:

};

#endif // CHESSENGINE_H
