#ifndef OCR_H
#define OCR_H

#include <QWidget>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>
#include <QImage>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include "networker.h"
#include <QBuffer>
#include <QSettings>
#include <QClipboard>

namespace Ui {
class ocr;
}

class ocr : public QWidget
{
    Q_OBJECT

public:
    explicit ocr(QWidget *parent = nullptr);
    ~ocr();
    void img_handler();
    void img_upload();
    void getAccessTokenRequestFinished(QNetworkReply* reply);
    void recognitionRequestFinished(QNetworkReply* reply);

signals:
    void sendNewStr(QString);

private:
    Ui::ocr *ui;
    QString accessToken;
    QNetworkAccessManager *nam;
};

#endif // OCR_H
