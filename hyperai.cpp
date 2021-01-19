#include "hyperai.h"

hyperAI::hyperAI(QWidget *parent) : QWidget(parent)
{
    QString program = "cmd.exe";
    //QStringList arguments;
    //arguments << "ELLEYE.exe";
    myProcess = new QProcess(parent);

    myProcess->setProcessChannelMode(QProcess::MergedChannels);
    connect(myProcess, &QProcess::readyRead,  [&](){
        QByteArray bytes = myProcess->readAll();
        QString msg = QString::fromLocal8Bit(bytes);
        qDebug() << "read data:" << msg << endl;
    });
    connect(myProcess, &QProcess::readyReadStandardOutput,  [&](){
        QByteArray bytes = myProcess->readAll();
        QString msg = QString::fromLocal8Bit(bytes);
        qDebug() << "read data:" << msg << endl;
    });
    myProcess->start(program, QStringList(""), QIODevice::ReadWrite);
    qDebug() << "象眼引擎启动";
    AI_intilized();
}

void hyperAI::AI_intilized()
{
//    QString cmd = "ELEEYE.exe\r\n";
//    QByteArray qbarr = cmd.toLatin1();
//    char *ch1 = qbarr.data();
//    qint64 len = cmd.length();
//    myProcess->write(ch1, len);
//    cmd.clear();
//    cmd = "ucci\r\n";
//    qbarr = cmd.toLatin1();
//    char *ch2 = qbarr.data();
//    len = cmd.length();
//    myProcess->write(ch2, len);
//    QByteArray bytes = myProcess->readAll();
//    QString msg = QString::fromLocal8Bit(bytes);
//    qDebug() << msg;
    QString cmd = "dir\r\n";
    QByteArray qbarr = cmd.toLatin1();
    char *ch1 = qbarr.data();
    qint64 len = cmd.length();
    myProcess->write(ch1, len);
    qDebug() << "write_data" << cmd <<endl;

//    QByteArray bytes = myProcess->readAll();
//    QString msg = QString::fromLocal8Bit(bytes);
//    qDebug() << "read data:" << msg << endl;
}
