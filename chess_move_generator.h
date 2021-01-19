#ifndef CHESS_MOVE_GENERATOR_H
#define CHESS_MOVE_GENERATOR_H

#include <QWidget>
#include "chessvariate.h"

class Chess_move_generator : public QWidget
{
    Q_OBJECT
public:
    explicit Chess_move_generator(QWidget *parent = nullptr);
    int m_MoveList[18][320];//一维为搜索深度，每四个数为一个走法
    int gengerate = 0;
    int now = 0;
    void AddMove(int from_x, int from_y, int to_x, int to_y, int gen);
    void GetRelatePiece(int gen);


signals:

};

#endif // CHESS_MOVE_GENERATOR_H
