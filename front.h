#ifndef FRONT_H
#define FRONT_H

#include <QDialog>

namespace Ui {
class front;
}

class front : public QDialog
{
    Q_OBJECT

public:
    explicit front(QWidget *parent = nullptr);
    ~front();

private:
    Ui::front *ui;
};

#endif // FRONT_H
