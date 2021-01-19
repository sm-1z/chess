#ifndef CHESSMOVING_H
#define CHESSMOVING_H

#include <QWidget>
#include <chesspoint.h>

class Chessmoving : public QWidget
{
    Q_OBJECT
public:
    explicit Chessmoving(QWidget *parent = nullptr);

    ChessPoint From, To;
    short ChessID;

signals:

};

#endif // CHESSMOVING_H
