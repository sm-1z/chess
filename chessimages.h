#ifndef CHESSIMAGES_H
#define CHESSIMAGES_H

#include <QWidget>
#include "chesspoint.h"

class ChessImages : public QWidget
{
    Q_OBJECT
public:
    explicit ChessImages(QWidget *parent = nullptr);

    QRectF point;//界面坐标
    QImage photo;
    int life = 1;//是否存活
    bool Chesscolor;//棋子颜色
    ChessPoint Chess_point;//棋盘坐标
    double endx;//死后移动位置
    double endy;
signals:

};

#endif // CHESSIMAGES_H
