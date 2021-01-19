#include "ocr.h"
#include "ui_ocr.h"

ocr::ocr(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ocr)
{
    ui->setupUi(this);

    connect(ui->ptn_recognition,&QPushButton::clicked,this,&ocr::img_upload);
    connect(ui->ptn_openfile,&QPushButton::clicked,this,&ocr::img_handler);

}

void ocr::img_handler()
{
    QString filename;
    filename=QFileDialog::getOpenFileName(this,
                                          tr("选择图像"),
                                          "",
                                          tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    if(filename.isEmpty())
    {
         return;
    }
    else
    {
        QImage* img=new QImage;

        if(! ( img->load(filename) ) ) //加载图像
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("打开图像失败!"));
            delete img;
            return;
        }

        /*    旋转图片    */
        /*QMatrix matrix;
        matrix.rotate(90.0);
        *img = img->transformed(matrix,Qt::FastTransformation);*/

        img->scaled(ui->label->size(),Qt::KeepAspectRatio);
        ui->label->setScaledContents(true);

        ui->label->setPixmap(QPixmap::fromImage(*img));
        QByteArray ba;
        QBuffer buf(&ba);
        img->save(&buf, "jpg");
        QByteArray hexed = ba.toBase64();
        buf.close();
        emit sendNewStr(QString(hexed));
        ui->textEdit->setPlainText(hexed);
        qDebug() << hexed;
        //qDebug() <<"hexed:" <<QString(hexed) << endl;
    }
}

void ocr::img_upload()
{
    QString key = "avQQpjexLKVjg4ly5jMMP88Z";
    QString secret = "z2mwh4tsvwI8L20qvGObswzurVQxfH0s";
    QSettings *configIniWrite = new QSettings("set.ini", QSettings::IniFormat);
    QDateTime time = QDateTime::currentDateTime();
    int timeT = time.toTime_t();
    configIniWrite->setValue("key", key);
    configIniWrite->setValue("secret", secret);
    if((configIniWrite->value("tokenTime").toInt() + 30*24*3600) < timeT){
        nam = new QNetworkAccessManager(this);
        QString parm = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id="+key+"&client_secret="+secret+"&";
        QUrl url(parm);
        connect(nam, &QNetworkAccessManager::finished,this, &ocr::getAccessTokenRequestFinished);
        QNetworkReply* reply = nam->get(QNetworkRequest(url));
    }
    else{
        accessToken = configIniWrite->value("accessToken").toString();
        qDebug() << accessToken << endl;
    }


    QString parm = ui->textEdit->toPlainText();
    if(parm.isEmpty()){
        QMessageBox::information(NULL, "错误", "图像数据不能为空");
        return;
    }
    nam = new QNetworkAccessManager(this);
    QUrl url;
    url.setUrl("https://aip.baidubce.com/rest/2.0/ocr/v1/accurate?access_token="+accessToken);
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));
    QByteArray byteArr;
    byteArr.append("image=");
    byteArr.append(QUrl::toPercentEncoding(parm));
    byteArr.append(QString("&recognize_granularity=small").toLatin1());
    connect(nam, &QNetworkAccessManager::finished,this, &ocr::recognitionRequestFinished);
    QNetworkReply* reply = nam->post(request,byteArr);
}

void ocr::getAccessTokenRequestFinished(QNetworkReply *reply)
{
    QNetworkReply::NetworkError err = reply->error();
    if(err != QNetworkReply::NoError) {
        qDebug() << "Failed: " << reply->errorString();
    }else {
        // 获取返回内容
        QJsonParseError json_error;
        QJsonDocument parse_doucment = QJsonDocument::fromJson(reply->readAll(), &json_error);
        if(parse_doucment.isObject()){
             QJsonObject obj = parse_doucment.object();
             accessToken = obj.take("access_token").toString();
             QSettings *configIniWrite = new QSettings("set.ini", QSettings::IniFormat);
            //向ini文件中写入内容,setValue函数的两个参数是键值对
            configIniWrite->setValue("accessToken", accessToken);
            QDateTime time = QDateTime::currentDateTime();   //获取当前时间
            int timeT = time.toTime_t();   //将当前时间转为时间戳
            configIniWrite->setValue("tokenTime", timeT);
            //写入完成后删除指针
            delete configIniWrite;
        }
    }
    nam->deleteLater();
}

void ocr::recognitionRequestFinished(QNetworkReply *reply)
{
    QNetworkReply::NetworkError err = reply->error();
    //qDebug()<<reply->readAll();
    if(err != QNetworkReply::NoError) {
        qDebug() << "Failed: " << reply->errorString();
    }else {
        // 获取返回内容
        QJsonParseError json_error;
        QJsonDocument parse_doucment = QJsonDocument::fromJson(reply->readAll(), &json_error);
        if(parse_doucment.isObject()){
            QJsonObject obj = parse_doucment.object();
            int wordsNum = obj.take("words_result_num").toInt();
            if(wordsNum > 0){
                QString res;
                QJsonDocument document;
                document.setObject(obj);
                QByteArray byteArray = document.toJson(QJsonDocument::Compact);
                res = QString(byteArray);
                qDebug() << res << endl;


                /*QJsonArray jsonArr = obj.take("words_result").toArray();

                for(int i=0;i<wordsNum;i++){

                   res.append(jsonArr[i].toObject().take("words").toString());
                   qDebug() << jsonArr[i].toObject().keys() << endl;
                   //QJsonArray jsonChars = jsonArr[i].toObject().take("chars").toArray();
                   //res.append(QString(jsonLocation[0].toObject().take("left").toInt()));
                   //qDebug() << jsonLocation[0].toObject().keys() << endl;
                   //res.append(jsonArrLocation[i].toObject().take("location").toString());
                   res.append("<br>");
                }
                ui->textEdit_2->setText(res);
                if(!res.isEmpty()){
                    QClipboard *board = QApplication::clipboard();
                    board->setText(res);
                }*/


                    if(obj.contains("words_result"))
                    {
                        QJsonValue words_result = obj.take("words_result");
                        qDebug() << words_result << endl;
                       // ui->textEdit_2->setText(words_result);
                        if(words_result.isObject())
                        {
                            qDebug() << "isObject" << endl;
                        }
                    }
            }else{
                QMessageBox::information(NULL, "提示", "无法识别图片内容");
            }
        }
    }
    nam->deleteLater();
}

ocr::~ocr()
{
    delete ui;
}
