#include "engine.h"
#include "ui_engine.h"


int From_x=0,From_y = 0,To_x = 0, To_y = 0;
bool engine_flag = false;
engine::engine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::engine)
{

    ui->setupUi(this);
    setWindowTitle("cmd text");
    //setWindowFlags(windowFlags() | Qt::Dialog);
    ui->lineEdit->setText(tr("ELEEYE"));
    ui->textEdit->setLineWrapMode(QTextEdit::NoWrap);

    /* 新建process */
    process = new QProcess(this);
    process->setProcessChannelMode(QProcess::MergedChannels);

    /* 回车 */
    ui->pushButton_Enter->setFocus();
    ui->pushButton_Enter->setShortcut(QKeySequence::InsertParagraphSeparator);
    ui->pushButton_Enter->setShortcut(Qt::Key_Enter);
    ui->pushButton_Enter->setShortcut(Qt::Key_Return);

    /* 按键相关 */
    connect(ui->pushButton,SIGNAL(clicked()),ui->lineEdit,SLOT(clear()));                           //清除命令行
    connect(ui->pushButton_Enter,SIGNAL(clicked()),this,SLOT(write_cmd()));                         //回车按钮
    connect(ui->pushButton_Clear,SIGNAL(clicked()),ui->textEdit,SLOT(clear()));                     //清除文本框按钮
    connect(ui->pushButton_engine,SIGNAL(clicked()),this,SLOT(write_engine()));

    /* 命令行相关 */
    connect(process,SIGNAL(readyRead()),this,SLOT(read_data()));                                    //读命令行数据
    connect(process,SIGNAL(readyReadStandardOutput()),this,SLOT(read_data()));                      //读命令行标准数据（兼容）
    connect(process,SIGNAL(errorOccurred(QProcess::ProcessError)),this,SLOT(error_process()));      //命令行错误处理
    connect(process,SIGNAL(finished(int)),this,SLOT(finished_process()));                           //命令行结束处理

    /* 焦点相关 */
    connect(ui->pushButton,SIGNAL(clicked()),ui->lineEdit,SLOT(setFocus()));
    connect(ui->pushButton_Enter,SIGNAL(clicked()),ui->lineEdit,SLOT(setFocus()));
    connect(ui->pushButton_Clear,SIGNAL(clicked()),ui->lineEdit,SLOT(setFocus()));

    process->start("cmd.exe");
}

engine::~engine()
{
    process->close();
    delete ui;
    delete process;

    ui = NULL;
    process = NULL;

    qDebug() << "end Engine" << endl;
}

void engine::write_cmd()
{
    /* 获得命令，\r\n代替键盘的Enter，没有则不会执行 */
    QString cmd = ui->lineEdit->text() + "\r\n";
    ui->lineEdit->clear();
    ui->lineEdit->setFocus();

    /* 转为char*并写入 */
    QByteArray qbarr = cmd.toLatin1();
    char *ch = qbarr.data();
    qint64 len = cmd.length();
    process->write(ch, len);

    /* 信息输出 */
    qDebug() << "Success:write_cmd：" << cmd << endl;
}

void engine::read_data()
{
    /* 接收数据 */
    QByteArray bytes = process->readAll();

    /* 显示 */
    QString msg = QString::fromLocal8Bit(bytes);
    ui->textEdit->append(msg);
    ui->textEdit->update();

    /* 信息输出 */
    qDebug() << "Success:read_data:" << msg << endl;

    QString strmove = "";
    if(msg.contains("bestmove"))
    {
        int i = msg.indexOf("bestmove ") + 9;
        strmove += msg.mid(i,4);
        qDebug() <<  "bestmove " << strmove << endl;

        if(strmove[0] == 'a')
            From_y = 1;
        else if(strmove[0] == 'b')
            From_y = 2;
        else if(strmove[0] == 'c')
            From_y = 3;
        else if(strmove[0] == 'd')
            From_y = 4;
        else if(strmove[0] == 'e')
            From_y = 5;
        else if(strmove[0] == 'f')
            From_y = 6;
        else if(strmove[0] == 'g')
            From_y = 7;
        else if(strmove[0] == 'h')
            From_y = 8;
        else if(strmove[0] == 'i')
            From_y = 9;
        else
            From_y = 0;

        if(strmove[1] == '9')
            From_x = 1;
        else if(strmove[1] == '8')
            From_x = 2;
        else if(strmove[1] == '7')
            From_x = 3;
        else if(strmove[1] == '6')
            From_x = 4;
        else if(strmove[1] == '5')
            From_x = 5;
        else if(strmove[1] == '4')
            From_x = 6;
        else if(strmove[1] == '3')
            From_x = 7;
        else if(strmove[1] == '2')
            From_x = 8;
        else if(strmove[1] == '1')
            From_x = 9;
        else if(strmove[1] == '0')
            From_x = 10;
        else
            From_x = 0;

        if(strmove[2] == 'a')
            To_y = 1;
        else if(strmove[2] == 'b')
            To_y = 2;
        else if(strmove[2] == 'c')
            To_y = 3;
        else if(strmove[2] == 'd')
            To_y = 4;
        else if(strmove[2] == 'e')
            To_y = 5;
        else if(strmove[2] == 'f')
            To_y = 6;
        else if(strmove[2] == 'g')
            To_y = 7;
        else if(strmove[2] == 'h')
            To_y = 8;
        else if(strmove[2] == 'i')
            To_y = 9;
        else
            To_y = 0;

        if(strmove[3] == '9')
            To_x = 1;
        else if(strmove[3] == '8')
            To_x = 2;
        else if(strmove[3] == '7')
            To_x = 3;
        else if(strmove[3] == '6')
            To_x = 4;
        else if(strmove[3] == '5')
            To_x = 5;
        else if(strmove[3] == '4')
            To_x = 6;
        else if(strmove[3] == '3')
            To_x = 7;
        else if(strmove[3] == '2')
            To_x = 8;
        else if(strmove[3] == '1')
            To_x = 9;
        else if(strmove[3] == '0')
            To_x = 10;
        else
            To_x = 0;

        qDebug() << From_x << From_y << To_x << To_y << endl;
        engine_flag = true;

    }

}

void engine::finished_process()
{
    /* 接收数据 */
    int flag = process->exitCode();

    /* 信息输出 */
    qDebug() << "Success:finishedProcess():" << flag << endl;
}

void engine::error_process()
{
    /* 接收数据 */
    int err_code  = process->exitCode();
    QString err = process->errorString();

    /* 显示 */
    ui->textEdit->append(QString("error coed:%1").arg(err_code));
    ui->textEdit->append(err);

    /* 信息输出 */
    qDebug() << "Success:error_process():" << err << endl;
}
void engine::write_engine()
{
    QString cmd = genrate_fen() + " b" + "\r\n";//引擎执红w，执黑b

    /* 转为char*并写入 */
    QByteArray qbarr = cmd.toLatin1();
    char *ch = qbarr.data();
    qint64 len = cmd.length();
    process->write(ch, len);

    /* 信息输出 */
    qDebug() << "Success:write_cmd：" << cmd << endl;

    cmd = "go depth 10\r\n"; // 引擎工作模式
    qbarr = cmd.toLatin1();
    char *ch2 = qbarr.data();
    len = cmd.length();
    process->write(ch2, len);
    qDebug() << "Success:write_cmd：" << cmd << endl;
}
QString engine::genrate_fen()
{
    QString fen_string = "position fen ";
        for(int i=1; i<11; i++)
        {
            int count = 0;
            for(int j=1; j<11;j++)
            {
                if(number[i][j] == NOCHESS)
                    count++;
                else
                {
                    QString st = "";
                    switch(number[i][j])
                    {
                    case R_CAR:
                        st = "R";
                        break;
                    case R_CANON:
                        st = "C";
                        break;
                    case R_HORSE:
                        st = "N";
                        break;
                    case R_ELEPHANT:
                        st = "B";
                        break;
                    case R_BISHOP:
                        st = "A";
                        break;
                    case R_PAWN:
                        st = "P";
                        break;
                    case R_KING:
                        st = "K";
                        break;
                    case G_CAR:
                        st = "r";
                        break;
                    case G_CANON:
                        st = "c";
                        break;
                    case G_HORSE:
                        st = "n";
                        break;
                    case G_ELEPHANT:
                        st = "b";
                        break;
                    case G_BISHOP:
                        st = "s";
                        break;
                    case G_PAWN:
                        st = "p";
                        break;
                    case G_KING:
                        st = "k";
                        break;
                    }
                    if(count == 0)
                        fen_string += st;
                    else
                    {
                        QString strcount = QString::number(count);
                        fen_string +=  strcount + st;
                        count = 0;
                    }
                }
            }
            if(count>0)
            {
                QString strcount = QString::number(count);
                fen_string += strcount;
            }
            fen_string += "/";
        }
    return fen_string;
}

