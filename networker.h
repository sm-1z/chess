#ifndef NETWORKER_H
#define NETWORKER_H
#include <iostream>
#include <QObject>
#include <QMap>
#include <QByteArray>
#include <QList>
#include <QNetworkReply>
#include <QNetworkAccessManager>

enum EMRequestType
{
    emRequestAccessToken,
    emRequestAccessOCR,
    emRequestTypeEnd,
};
Q_DECLARE_FLAGS(EMRequestTypeFlags,EMRequestType)
Q_DECLARE_OPERATORS_FOR_FLAGS(EMRequestTypeFlags)


class NetWorker : public QObject
{
    Q_OBJECT

    typedef QMap<QNetworkReply*,EMRequestTypeFlags> NetworkRequest;
public:
    ~ NetWorker();
    static NetWorker* instance();

public slots:
    EMRequestTypeFlags fetchAccessToken(QString client_id, QString client_secret);

    EMRequestTypeFlags fetchPictureOCR(QString access_token,
                                       QByteArray base64_img,
                                       QString language_type="CHN_ENG",
                                       QString detect_direction="false",
                                       QString detect_language="false",
                                       QString probability="false");

    static QString machineIp4();
    static QString reportNetworkReplyError(QNetworkReply::NetworkError err);

signals:
     void emitError(QString aServerError,QByteArray data,EMRequestTypeFlags flag);
     void emitDataFinished(QByteArray data, EMRequestTypeFlags flag);

public slots:
    void replyFinished(QNetworkReply* replay);
    void slotError(QNetworkReply::NetworkError ){}
    void slotSslErrors(QList<QSslError>){}

public:
    explicit NetWorker(QObject *parent = 0);
    Q_DISABLE_COPY(NetWorker)

private:
    QNetworkAccessManager* mNetmanager;
    NetworkRequest mRequest;
    static NetWorker* mInstance;
};

#endif // NETWORKER_H
#ifndef NETWORKER_H
#define NETWORKER_H

#include <QObject>

class NetWorker : public QObject
{
    Q_OBJECT
public:
    explicit NetWorker(QObject *parent = nullptr);

signals:

};

#endif // NETWORKER_H
