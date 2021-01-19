#ifndef HYPERAI_H
#define HYPERAI_H

#include <QWidget>
#include <QProcess>
#include <QDebug>

class hyperAI : public QWidget
{
    Q_OBJECT
public:
    explicit hyperAI(QWidget *parent = nullptr);
    void AI_intilized();

    QProcess *myProcess;

signals:

};

#endif // HYPERAI_H
