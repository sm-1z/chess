#ifndef CHESSPOINT_H
#define CHESSPOINT_H

#include <QWidget>

class ChessPoint : public QWidget
{
    Q_OBJECT
public:
    explicit ChessPoint(QWidget *parent = nullptr);

    int heng;//棋盘坐标
    int shu;
    void give_value(int x, int y);//返回棋子坐标

signals:

};

#endif // CHESSPOINT_H
