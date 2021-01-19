#include "chess.h"
#include "ui_chess.h"

bool bRedTrue = true;

Chess::Chess(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chess)
{
    ui->setupUi(this);
    chessInitialize();


    connect(timer, &QTimer::timeout, this, &Chess::ui_update);//要自定义update函数实现自己的功能哟
    timer->start(3000);//设置时间间隔为3000毫秒

}

void Chess::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QPen background = p.pen();
    background.setColor(Qt::black);//棋盘线颜色
    background.setWidth(2);//棋盘线宽度
    p.setPen(background);
    //绘制18条竖线
    for (short n = 1;n<10;n++) {
        p.drawLine(size*n,size,size*n,size*5);
        p.drawLine(size*n,size*6,size*n,size*10);
    }
    //绘制9条横线
    for (short n = 1;n<=10;n++) {
        p.drawLine(size,size*n,size*9,size*n);
    }
    //绘制士所走斜线
    p.drawLine(size*4,size,size*6,size*3);
    p.drawLine(size*6,size,size*4,size*3);
    p.drawLine(size*4,size*8,size*6,size*10);
    p.drawLine(size*6,size*8,size*4,size*10);
    //绘制中间两条竖线
    p.drawLine(size,size*5,size,size*6);
    p.drawLine(size*9,size*5,size*9,size*6);
    //绘制楚河汉界
    QPointF point(size*2.6,size*5.7);
    p.setFont(QFont("Arial",30));
    p.drawText(point,"楚河                汉界");
    //绘制棋子
    for (short n=0;n<32;n++) {
        p.drawImage(pictures[n].point,pictures[n].photo);
    }
    p.end();

}
void Chess::chessInitialize()
{
    //设置棋子图片
    pictures[0].photo.load(":/new/prefix1/hche.gif");
    pictures[1].photo.load(":/new/prefix1/hma.gif");
    pictures[2].photo.load(":/new/prefix1/hxiang.gif");
    pictures[3].photo.load(":/new/prefix1/hshi.gif");
    pictures[4].photo.load(":/new/prefix1/hjiang.gif");
    pictures[5].photo.load(":/new/prefix1/hshi.gif");
    pictures[6].photo.load(":/new/prefix1/hxiang.gif");
    pictures[7].photo.load(":/new/prefix1/hma.gif");
    pictures[8].photo.load(":/new/prefix1/hche.gif");
    pictures[9].photo.load(":/new/prefix1/hpao.gif");
    pictures[10].photo.load(":/new/prefix1/hpao.gif");
    for (short n=11;n<16;n++) {
        pictures[n].photo.load(":/new/prefix1/hbing.gif");
        pictures[n+5].photo.load(":/new/prefix1/gzu.gif");
    }
    pictures[21].photo.load(":/new/prefix1/gpao.gif");
    pictures[22].photo.load(":/new/prefix1/gpao.gif");
    pictures[23].photo.load(":/new/prefix1/gche.gif");
    pictures[24].photo.load(":/new/prefix1/gma.gif");
    pictures[25].photo.load(":/new/prefix1/gxiang.gif");
    pictures[26].photo.load(":/new/prefix1/gshi.gif");
    pictures[27].photo.load(":/new/prefix1/gjiang.gif");
    pictures[28].photo.load(":/new/prefix1/gshi.gif");
    pictures[29].photo.load(":/new/prefix1/gxiang.gif");
    pictures[30].photo.load(":/new/prefix1/gma.gif");
    pictures[31].photo.load(":/new/prefix1/gche.gif");
    //设置棋子坐标
    for (short n=1;n<10;n++) {
        pictures[n-1].point.setX(size*n-size/2);
        pictures[n-1].point.setY(size*10-size/2);
        pictures[n-1].Chess_point.shu = n;
        pictures[n-1].Chess_point.heng = 10;
    }
    pictures[9].point.setX(size*2-size/2);
    pictures[9].point.setY(size*8-size/2);
    pictures[9].Chess_point.shu = 2;
    pictures[9].Chess_point.heng = 8;
    pictures[10].point.setX(size*8-size/2);
    pictures[10].point.setY(size*8-size/2);
    pictures[10].Chess_point.shu = 8;
    pictures[10].Chess_point.heng = 8;
    for (short n=1;n<6;n++) {
        pictures[n+10].point.setX(size*(2*n-1)-size/2);
        pictures[n+10].point.setY(size*7-size/2);
        pictures[n+10].Chess_point.shu = (2*n-1);
        pictures[n+10].Chess_point.heng = 7;

        pictures[n+15].point.setX(size*(2*n-1)-size/2);
        pictures[n+15].point.setY(size*4-size/2);
        pictures[n+15].Chess_point.shu = (2*n-1);
        pictures[n+15].Chess_point.heng = 4;
    }
    pictures[21].point.setX(size*2-size/2);
    pictures[21].point.setY(size*3-size/2);
    pictures[21].Chess_point.shu = 2;
    pictures[21].Chess_point.heng = 3;
    pictures[22].point.setX(size*8-size/2);
    pictures[22].point.setY(size*3-size/2);
    pictures[22].Chess_point.shu = 8;
    pictures[22].Chess_point.heng = 3;
    for (short n=1;n<10;n++) {
        pictures[n+22].point.setX(size*n-size/2);
        pictures[n+22].point.setY(size-size/2);
        pictures[n+22].Chess_point.shu = n;
        pictures[n+22].Chess_point.heng = 1;
    }
    //设置棋子大小，以及死亡后位置
    for (short i=0;i<32;i++) {
        pictures[i].point.setHeight(size);
        pictures[i].point.setWidth(size);
        pictures[i].endx = -254;
        pictures[i].endy = (3.5-4)*40;
    }
    //设置棋子颜色
    for (short i =0;i <16;i ++) {
        pictures[i].Chesscolor = true;
        pictures[i+16].Chesscolor = false;
    }
    selectID = -1;
    bRedTrue = true;
}

void Chess::mousePressEvent(QMouseEvent *e)
{
    QPoint pt = e->pos();
    int row, col;

    //判断点击是否在棋盘内
    if(!getRowCol(pt,row,col))
        return;
    if(engine_flag == false){
        clickId = -1;
        short i;
        for (i = 0;i <= 31;i++) {
            if(pictures[i].Chess_point.heng == row && pictures[i].Chess_point.shu == col && pictures[i].life == 1)
                break;
        }
        if(i < 32){
            clickId = i;
            //qDebug() << clickId;
        }
        if(selectID == -1)//选中棋子
        {
            if(clickId != -1)
            {
                if(bRedTrue == pictures[clickId].Chesscolor){
                    selectID = clickId;
                    qDebug() << selectID;
                }

            }
        }
        else//走棋子
        {
            int From_heng = pictures[selectID].Chess_point.heng;
            int From_shu = pictures[selectID].Chess_point.shu;
            int To_heng = row;
            int To_shu = col;
            //qDebug() << "success";
            qDebug() << Chessvariate::ISValidMove(From_heng, From_shu, To_heng, To_shu);


                int pre_x=pictures[selectID].Chess_point.heng,pre_y= pictures[selectID].Chess_point.shu,aft_x=pictures[clickId].Chess_point.heng,aft_y=pictures[clickId].Chess_point.shu;
                pictures[clickId].Chess_point.heng = 0;
                pictures[clickId].Chess_point.shu = 0;
                pictures[selectID].Chess_point.heng = row;
                pictures[selectID].Chess_point.shu = col;
                int temp =  number[To_heng][To_shu];
                number[To_heng][To_shu] = number[From_heng][From_shu];
                number[From_heng][From_shu] = NOCHESS;
                if(isAttack())
                {
                    QMessageBox message1(QMessageBox::NoIcon, "被将军", "无法走棋");
                    message1.exec();
                    pictures[clickId].Chess_point.heng = aft_x;
                    pictures[clickId].Chess_point.shu = aft_y;
                    pictures[selectID].Chess_point.heng = pre_x;
                    pictures[selectID].Chess_point.shu = pre_y;
                    number[From_heng][From_shu] = number[To_heng][To_shu];
                    number[To_heng][To_shu] = temp;
                    clickId = -1;
                    selectID = -1;
                }
                else
                {
                    pictures[clickId].Chess_point.heng = aft_x;
                    pictures[clickId].Chess_point.shu = aft_y;
                    pictures[selectID].Chess_point.heng = pre_x;
                    pictures[selectID].Chess_point.shu = pre_y;
                    number[From_heng][From_shu] = number[To_heng][To_shu];
                    number[To_heng][To_shu] = temp;
                }


            if(Chessvariate::ISValidMove(From_heng, From_shu, To_heng, To_shu) and pictures[selectID].life != 0){
                number[To_heng][To_shu] = number[From_heng][From_shu];
                number[From_heng][From_shu] = NOCHESS;
                pictures[clickId].point.setX(pictures[clickId].endx);
                pictures[clickId].point.setY(pictures[clickId].endy);
                pictures[clickId].point.setHeight(size);
                pictures[clickId].point.setWidth(size);
                pictures[clickId].Chess_point.heng = 0;
                pictures[clickId].Chess_point.shu = 0;
                pictures[selectID].Chess_point.heng = row;
                pictures[selectID].Chess_point.shu = col;
                pictures[selectID].point.setX(size*col - size/2);
                pictures[selectID].point.setY(size*row - size/2);
                pictures[selectID].point.setHeight(size);
                pictures[selectID].point.setWidth(size);
                qDebug() << "success";
                //QString fen = genrate_fen();
                //qDebug() << fen;
                if(clickId != -1)
                    pictures[clickId].life = 0;
                selectID = -1;
                bRedTrue = !bRedTrue;
                timer_detect();
            }
        }
    }
    else
    {
        int from_id = -1, to_id = -1;
        short i;
        for (i = 0;i <= 31;i++) {
            if(pictures[i].Chess_point.heng == From_x && pictures[i].Chess_point.shu == From_y && pictures[i].life == 1)
                break;
        }
        if(i < 32){
            from_id = i;
        }
        for (i = 0;i <= 31;i++) {
            if(pictures[i].Chess_point.heng == To_x && pictures[i].Chess_point.shu == To_y && pictures[i].life == 1)
                break;
        }
        if(i < 32){
            to_id = i;
        }
        number[To_x][To_y] = number[From_x][From_y];
        number[From_x][From_y] = NOCHESS;
        pictures[to_id].point.setX(pictures[to_id].endx);
        pictures[to_id].point.setY(pictures[to_id].endy);
        pictures[to_id].point.setHeight(size);
        pictures[to_id].point.setWidth(size);
        pictures[to_id].Chess_point.heng = 0;
        pictures[to_id].Chess_point.shu = 0;
        pictures[from_id].Chess_point.heng = To_x;
        pictures[from_id].Chess_point.shu = To_y;
        pictures[from_id].point.setX(size*To_y - size/2);
        pictures[from_id].point.setY(size*To_x - size/2);
        pictures[from_id].point.setHeight(size);
        pictures[from_id].point.setWidth(size);
        bRedTrue = !bRedTrue;
        timer_detect();
        if(to_id != -1)
            pictures[to_id].life = 0;

        engine_flag =  false;
    }

    update();
    if(isAttack())
    {
        QString jiangjun = "";
        if(bRedTrue)
            jiangjun += "绿方将军";
        else
            jiangjun += "红方将军";
        QMessageBox message1(QMessageBox::NoIcon, "将军", jiangjun);
        message1.exec();
    }


    if(pictures[4].life != 1 || pictures[27].life != 1){
        if(pictures[4].life != 1){
            success.append("绿方胜利");
        }
        else if(pictures[27].life != 1){
            success.append("红方胜利");
        }
        QMessageBox message(QMessageBox::NoIcon, "对局结束", success);
        message.exec();
    }
}

bool Chess::getRowCol(QPoint pt, int &row, int &col)
{
    for (row = 1;row <= 10;row++) {
        for (col = 1;col <= 9;col++) {
            QPoint temp = center(row, col);
            int x = temp.x()-pt.x();
            int y = temp.y()-pt.y();

            if(x*x+y*y<size*size/4)
            {
                return true;
            }
        }
    }
    return false;
}

QPoint Chess::center(int row, int col)
{
    QPoint rePoint;
    rePoint.rx() = col*size;
    rePoint.ry() = row*size;
    return rePoint;
}
bool Chess::isAttack()
{
    bool isattack = false;
    int RKING_x = pictures[4].Chess_point.heng,RKING_y = pictures[4].Chess_point.shu,GKING_x = pictures[27].Chess_point.heng,GKING_y = pictures[27].Chess_point.shu;
    if(bRedTrue)
        isattack = Chessvariate::ISValidMove(pictures[16].Chess_point.heng, pictures[16].Chess_point.shu, RKING_x, RKING_y) || Chessvariate::ISValidMove(pictures[17].Chess_point.heng, pictures[17].Chess_point.shu, RKING_x, RKING_y)
                || Chessvariate::ISValidMove(pictures[18].Chess_point.heng, pictures[18].Chess_point.shu, RKING_x, RKING_y) || Chessvariate::ISValidMove(pictures[19].Chess_point.heng, pictures[19].Chess_point.shu, RKING_x, RKING_y)
                || Chessvariate::ISValidMove(pictures[20].Chess_point.heng, pictures[20].Chess_point.shu, RKING_x, RKING_y) || Chessvariate::ISValidMove(pictures[21].Chess_point.heng, pictures[21].Chess_point.shu, RKING_x, RKING_y)
                || Chessvariate::ISValidMove(pictures[22].Chess_point.heng, pictures[22].Chess_point.shu, RKING_x, RKING_y) || Chessvariate::ISValidMove(pictures[23].Chess_point.heng, pictures[23].Chess_point.shu, RKING_x, RKING_y)
                || Chessvariate::ISValidMove(pictures[24].Chess_point.heng, pictures[24].Chess_point.shu, RKING_x, RKING_y) || Chessvariate::ISValidMove(pictures[27].Chess_point.heng, pictures[27].Chess_point.shu, RKING_x, RKING_y)
                || Chessvariate::ISValidMove(pictures[30].Chess_point.heng, pictures[30].Chess_point.shu, RKING_x, RKING_y) || Chessvariate::ISValidMove(pictures[31].Chess_point.heng, pictures[31].Chess_point.shu, RKING_x, RKING_y);
    else
        isattack = Chessvariate::ISValidMove(pictures[0].Chess_point.heng, pictures[0].Chess_point.shu, GKING_x, GKING_y) || Chessvariate::ISValidMove(pictures[1].Chess_point.heng, pictures[1].Chess_point.shu, GKING_x, GKING_y)
                || Chessvariate::ISValidMove(pictures[4].Chess_point.heng, pictures[4].Chess_point.shu, GKING_x, GKING_y) || Chessvariate::ISValidMove(pictures[7].Chess_point.heng, pictures[7].Chess_point.shu, GKING_x, GKING_y)
                || Chessvariate::ISValidMove(pictures[8].Chess_point.heng, pictures[8].Chess_point.shu, GKING_x, GKING_y) || Chessvariate::ISValidMove(pictures[9].Chess_point.heng, pictures[9].Chess_point.shu, GKING_x, GKING_y)
                || Chessvariate::ISValidMove(pictures[10].Chess_point.heng, pictures[10].Chess_point.shu, GKING_x, GKING_y) || Chessvariate::ISValidMove(pictures[11].Chess_point.heng, pictures[11].Chess_point.shu, GKING_x, GKING_y)
                || Chessvariate::ISValidMove(pictures[12].Chess_point.heng, pictures[12].Chess_point.shu, GKING_x, GKING_y) || Chessvariate::ISValidMove(pictures[13].Chess_point.heng, pictures[13].Chess_point.shu, GKING_x, GKING_y)
                || Chessvariate::ISValidMove(pictures[14].Chess_point.heng, pictures[14].Chess_point.shu, GKING_x, GKING_y) || Chessvariate::ISValidMove(pictures[15].Chess_point.heng, pictures[15].Chess_point.shu, GKING_x, GKING_y);
    return isattack;

}



void Chess::ui_update()
{
    QMouseEvent* press=new QMouseEvent(QEvent::MouseButtonPress,QPoint(562,544),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);

    QApplication::postEvent(this,press);

    QMouseEvent* release=new QMouseEvent(QEvent::MouseButtonRelease,QPoint(562,544),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);

    QApplication::postEvent(this,release);

    qDebug() << "mouse clicked" << endl;

}

void Chess::timer_detect()
{
    if(bRedTrue == true)
    {
        timer->start(3000);
        qDebug() << "timer start" << endl;
    }
    else
    {
        timer->stop();
        qDebug() << "timer stop" << endl;
    }
}

Chess::~Chess()
{
    delete ui;
}
