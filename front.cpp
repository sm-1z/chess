#include "front.h"
#include "ui_front.h"

front::front(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::front)
{
    ui->setupUi(this);
}

front::~front()
{
    delete ui;
}
