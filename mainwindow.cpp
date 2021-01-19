#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    connect(ui->actionOpen,&QAction::triggered,this,&MainWindow::engine_open);
//    connect(ui->actionClose,&QAction::triggered,this,&MainWindow::engine_close);
//    connect(ui->actionOpen_2,&QAction::triggered,this,&MainWindow::port_open);
//    connect(ui->actionClose_2,&QAction::triggered,this,&MainWindow::port_close);



}

MainWindow::~MainWindow()
{
    delete ui;
}



//void MainWindow::engine_open()
//{
//    e->move(1000, 100);
//    e->show();
//}

//void MainWindow::engine_close()
//{
//    e->close();
//}
//void MainWindow::port_open()
//{
//    p->move(1000,500);
//    p->show();
//}
//void MainWindow::port_close()
//{
//    p->close();
//}
