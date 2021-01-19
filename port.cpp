#include "port.h"
#include "ui_port.h"

Port::Port(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Port)
{
    ui->setupUi(this);
    //设置波特率菜单
    QStringList baud;
    baud << "1200" << "4800" << "9600" << "115200";
    ui->baudBox->addItems(baud);
    ui->baudBox->setCurrentIndex(3);
    //设置数据位菜单
    QStringList bitNum;
    bitNum << "8";
    ui->bitNumBox->addItems(bitNum);
    ui->bitNumBox->setCurrentIndex(0);
    //设置校验位菜单
    QStringList parityNum;
    parityNum << "0" << "1" << "2";
    ui->parityBox->addItems(parityNum);
    ui->parityBox->setCurrentIndex(0);
    //设置停止位菜单
    QStringList stopNum;
    stopNum << "1" << "2";
    ui->stopBox->addItems(stopNum);
    ui->stopBox->setCurrentIndex(0);
    //查找可用的串口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);

        if(serial.open(QIODevice::ReadWrite))
        {
            ui->portBox->addItem(serial.portName());
            serial.close();
        }
    }

    //关闭发送按钮
    ui->sendBtn->setEnabled(false);
    qDebug()<<tr("界面设定成功");
    //连接打开串口
    connect(ui->openBtn,&QPushButton::clicked,this,&Port::on_openBtn_clicked);
    //连接发送数据
    connect(ui->sendBtn,&QPushButton::clicked,this,&Port::on_sendBtn_clicked);
    //连接清空接受窗口
    connect(ui->clearReceiveBtn,&QPushButton::clicked,this,&Port::on_clearReceiveBtn_clicked);
    //连接清空发送窗口
    connect(ui->clearSendBtn,&QPushButton::clicked,this,&Port::on_clearSendBtn_clicked);
}

Port::~Port()
{
    delete ui;
}
//清空接收窗口
void Port::on_clearReceiveBtn_clicked()
{
    ui->receiveText->clear();
}
//清空发送窗口
void Port::on_clearSendBtn_clicked()
{
    ui->sendText->clear();
}
//发送数据
void Port::on_sendBtn_clicked()
{
    //QByteArray senddata;
    //StringToHex(ui->sendText->toPlainText(),senddata);
    //serial->write(senddata);
    QByteArray senddata = ui->sendText->toPlainText().toUtf8();
    QByteArray data_format = "\r\n";
    serial->write(senddata);
    serial->write(data_format);
    qDebug() << tr(senddata);
}
//打开串口
void Port::on_openBtn_clicked()
{
    if(ui->openBtn->text() == tr("打开串口"))
    {
        serial = new QSerialPort;
        //设置串口名
        serial->setPortName(ui->portBox->currentText());
        qDebug() << "串口名:" << ui->portBox->currentText() << endl;
        //打开串口
        serial->setBaudRate(ui->baudBox->currentText().toInt());
        switch (ui->baudBox->currentText().toInt()) {
        case 1200:
            serial->setBaudRate(QSerialPort::Baud1200);
            break;
        case 4800:
            serial->setBaudRate(QSerialPort::Baud4800);
            break;
        case 9600:
            serial->setBaudRate(QSerialPort::Baud9600);
            break;
        case 115200:
            serial->setBaudRate(QSerialPort::Baud115200);
            break;
        default:
            break;
        }

        //设置数据位数
        switch(ui->bitNumBox->currentIndex())
        {
            case 8:
                serial->setDataBits(QSerialPort::Data8);
            break;
            default:
            break;
        }
        //设置奇偶校验
        switch (ui->parityBox->currentIndex()) {
        case 0:
            serial->setParity(QSerialPort::NoParity);
            break;
        default:
            break;
        }
        //设置停止位
        switch (ui->stopBox->currentIndex()) {
        case 1:
            serial->setStopBits(QSerialPort::OneStop);
            break;
        case 2:
            serial->setStopBits(QSerialPort::TwoStop);
            break;
        default:
            break;
        }
        //设置流控制
        serial->setFlowControl(QSerialPort::NoFlowControl);
        serial->open(QIODevice::ReadWrite);
        if(serial->isOpen())
        {
        //关闭设置菜单功能
            ui->portBox->setEnabled(false);
            ui->baudBox->setEnabled(false);
            ui->bitNumBox->setEnabled(false);
            ui->parityBox->setEnabled(false);
            ui->stopBox->setEnabled(false);
            ui->openBtn->setText(tr("关闭串口"));
            ui->sendBtn->setEnabled(true);
        }
        else {
            qDebug() << "串口打开失败" << endl;
        }
        //连接信号槽
        QObject::connect(serial,&QIODevice::readyRead,this,&Port::read_data);

    }
    else
    {
        //关闭串口
        serial->clear();
        serial->close();
        serial->deleteLater();
        //恢复设置功能
        ui->portBox->setEnabled(true);
        ui->baudBox->setEnabled(true);
        ui->bitNumBox->setEnabled(true);
        ui->parityBox->setEnabled(true);
        ui->stopBox->setEnabled(true);
        ui->openBtn->setText(tr("打开串口"));
        ui->sendBtn->setEnabled(true);
    }
}

void Port::read_data()
{
    static QByteArray buf;
    buf += serial->readAll();
    if(!buf.isEmpty())
    {
        //QString str = ui->receiveText->toPlainText();
        QString str = QString::fromLocal8Bit(buf);
        //ui->receiveText->clear();
        ui->receiveText->insertPlainText(str);
        buf.clear();
    }
}

void Port::StringToHex(QString str, QByteArray & senddata)
{
    int hexdata,lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    senddata.resize(len/2);
    char lstr,hstr;
    for(int i=0;i<len;)
    {
        hstr = str[i].toLatin1();
        if(hstr == ' ')
        {
            i++;
            continue;
        }
        i++;
        if(i>=len)
            break;
        lstr =str[i].toLatin1();
        hexdata = ConvertHexChar(hstr);
        lowhexdata = ConvertHexChar(lstr);
        if((hexdata == 16)||(lowhexdata == 16)){
            break;
        }
        else {
            hexdata = hexdata * 16 + lowhexdata;
        }
        i++;
        senddata[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    senddata.resize(hexdatalen);
}
char Port::ConvertHexChar(char ch)
{
    if((ch>='0')&&(ch<='9'))
        return ch-0x30;
    else if ((ch>='A')&&(ch<='F')) {
        return ch-'A'+10;
    }
    else if ((ch>='a')&&(ch<='f')) {
        return ch-'a'+10;
    }
    else {
        return ch-ch;
    }
}
