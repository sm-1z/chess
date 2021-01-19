#ifndef PORT_H
#define PORT_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QStringList>
#include <QDebug>
#include <QIODevice>
#include <QComboBox>
#include <QPushButton>
#include <QChar>

namespace Ui {
class Port;
}

class Port : public QWidget
{
    Q_OBJECT

public:
    explicit Port(QWidget *parent = nullptr);
    ~Port();

    void on_clearReceiveBtn_clicked();
    void on_clearSendBtn_clicked();
    void on_sendBtn_clicked();
    void on_openBtn_clicked();
    void read_data();
    //QString转16进制Hex型
    void StringToHex(QString str, QByteArray & senddata);
    char ConvertHexChar(char ch);

private:
    Ui::Port *ui;
    QSerialPort *serial;
};

#endif // PORT_H
