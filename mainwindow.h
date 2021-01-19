#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <engine.h>
#include <port.h>
#include "chess.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


//    void engine_open();
//    void engine_close();
//    void port_open();
//    void port_close();

private:
    Ui::MainWindow *ui;
//    engine *e = new engine(this);
//    Port *p = new Port(this);

};
#endif // MAINWINDOW_H
