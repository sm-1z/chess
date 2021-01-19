#ifndef ENGINE_H
#define ENGINE_H

#include <QWidget>
#include <QProcess>
#include <handleapi.h>
#include <QShortcut>
#include <QDebug>
#include <QMouseEvent>
#include <QApplication>
#include "chess.h"


extern int From_x,From_y,To_x,To_y;
extern bool engine_flag;
namespace Ui {
class engine;
}

class engine : public QWidget
{
    Q_OBJECT

public:
    explicit engine(QWidget *parent = nullptr);
    ~engine();


private:
    Ui::engine *ui;
    QProcess *process;
    QShortcut *key;

public slots:
    void write_cmd();
    void read_data();
    void finished_process();
    void error_process();
    void write_engine();
    QString genrate_fen();
};

#endif // ENGINE_H
