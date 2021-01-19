#ifndef CHESS_H
#define CHESS_H


#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <Qt>
#include "chessimages.h"
#include "chessmoving.h"
#include "chessvariate.h"
#include "hyperai.h"
#include "engine.h"

extern bool bRedTrue;  //红棋先下标志
namespace Ui {
class Chess;
}

class Chess : public QWidget
{
    Q_OBJECT

public:
    explicit Chess(QWidget *parent = nullptr);
    ~Chess();

    ChessImages pictures[32];//棋子类型
    int size = 90;//棋子尺寸
    int selectID; //选中棋子[-1:选棋子 || 非-1：走棋子]
    int clickId; //点击鼠标选中棋子的ID

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void chessInitialize();//棋子初始化
    QString success = "";//胜利标志

    bool getRowCol(QPoint pt, int &row, int &col);
    QPoint center(int row, int col);
    bool isAttack();


    QTimer *timer = new QTimer(this);

    void timer_detect();
    void ui_update();

private:
    Ui::Chess *ui;






};

#endif // CHESS_H
