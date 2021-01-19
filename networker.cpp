#include "networker.h"
#include <QUrlQuery>
#include <QHostInfo>

NetWorker* NetWorker::mInstance = NULL;

NetWorker* NetWorker::instance()
{
    mInstance = (NULL==mInstance)?(new NetWorker):mInstance;
    return mInstance;
}

NetWorker::NetWorker(QObject *parent)
    : QObject(parent)
    , mNetmanager(new QNetworkAccessManager(this))
{
    connect(mNetmanager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));
}

NetWorker::~NetWorker()
{
    delete mNetmanager;
    mNetmanager = NULL;

    delete mInstance;
    mInstance = NULL;
}

void NetWorker::replyFinished(QNetworkReply* apReply)
{
    // NetworkerReply error
    if(apReply->error()!= QNetworkReply::NoError)
    {
        QByteArray data =  apReply->readAll();
        emit emitError(reportNetworkReplyError(apReply->error()),data,mRequest[apReply]);
    }
    else
    {
         // 没有错误，返回读取的数据
         QByteArray data =  apReply->readAll();
         emit emitDataFinished(data,mRequest[apReply]);
         apReply->deleteLater();
    }

    mRequest.remove(apReply);
}

/*

from urllib import parse,request
import ssl

host = 'https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=Bjm0X1hsLxrxsyA3hyuSUuke&client_secret=P6CBRGWnmTUSOboM0Dao5ZUI51SW8ODE'
req = request.Request(host,headers={'Content-Type':'application/json; charset=UTF-8'})
res = request.urlopen(req)
res = res.read()
print(res)

*/
EMRequestTypeFlags NetWorker::fetchAccessToken(QString client_id, QString client_secret)
{
    QNetworkRequest request;

    QUrl url("https://aip.baidubce.com/oauth/2.0/token?");
    QUrlQuery query;
    query.addQueryItem("grant_type","client_credentials");
    query.addQueryItem("client_id",client_id);
    query.addQueryItem("client_secret", client_secret);
    url.setQuery(query);
    request.setUrl(url);
    request.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json; charset=UTF-8"));
    QNetworkReply* reply = mNetmanager->get(request);
    reply->ignoreSslErrors();
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(slotSslErrors(QList<QSslError>)));
    mRequest[reply] = emRequestAccessToken;

    return mRequest[reply];
}

/*

from urllib import parse,request
import ssl
import base64
host = 'https://aip.baidubce.com/rest/2.0/ocr/v1/general_basic/token?access_token=24.ae2a4c83a7a4778a2d12395b62b68099.2592000.1529261360.282335-11263768'
with open(r"D:\CommonUser\Documents\BookCode\QT\Test\screen_assist\ss.png", 'rb') as f:
    data = base64.b64encode(f.read())
textmod={'image': data,}
textmod = parse.urlencode(textmod).encode(encoding='utf-8')
req = request.Request(host,headers={'Content-Type':'application/x-www-form-urlencoded'},data=textmod,)
res = request.urlopen(req)
res = res.read()
print(res)

*/
EMRequestTypeFlags NetWorker::fetchPictureOCR(QString access_token,
                                              QByteArray base64_img,
                                              QString language_type,
                                              QString detect_direction,
                                              QString detect_language,
                                              QString probability)
{
    QNetworkRequest request;

    QUrl url("https://aip.baidubce.com/rest/2.0/ocr/v1/accurate");
    QUrlQuery query;
    query.addQueryItem("access_token",access_token);
    url.setQuery(query);
    request.setUrl(url);
    request.setRawHeader(QByteArray("Content-Type"), QByteArray("application/x-www-form-urlencoded"));
    base64_img = base64_img.toPercentEncoding();
    QByteArray postData;
    postData.append(QString("image=").toLatin1()+base64_img);
    postData.append(QString("&language_type="+language_type).toLatin1());
    postData.append(QString("&detect_direction="+detect_direction).toLatin1());
    postData.append(QString("&detect_language="+detect_language).toLatin1());
    postData.append(QString("&probability="+probability).toLatin1());

    QNetworkReply* reply = mNetmanager->post(request,postData);
    reply->ignoreSslErrors();
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(slotSslErrors(QList<QSslError>)));
    mRequest[reply] = emRequestAccessOCR;

    return mRequest[reply];
}



QString NetWorker::machineIp4()
{
    QString ip4("127.0.0.1");
    QString localHostName = QHostInfo::localHostName();
    QHostInfo info = QHostInfo::fromName(localHostName);
    foreach(QHostAddress address, info.addresses())
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol)
        {
            ip4 = address.toString();
            break;
        }
    }

    return ip4;
}

QString NetWorker::reportNetworkReplyError(QNetworkReply::NetworkError err)
{
    switch(err)
    {
    case QNetworkReply::NoError:
        return QString(tr("no error condition."));

    case QNetworkReply::ConnectionRefusedError:
        return QString(tr("the remote server refused the connection (the server is not accepting requests)."));

    case QNetworkReply::RemoteHostClosedError:
        return QString(tr("the remote server closed the connection prematurely, before the entire reply was received and processed."));

    case QNetworkReply::HostNotFoundError:
        return QString(tr("he remote host name was not found (invalid hostname)."));

    case QNetworkReply::TimeoutError:
        return QString(tr("the connection to the remote server timed out."));

    case QNetworkReply::OperationCanceledError:
        return QString(tr("the operation was canceled via calls to abort() or close() before it was finished."));

    case QNetworkReply::SslHandshakeFailedError:
        return QString(tr("the SSL/TLS handshake failed and the encrypted channel could not be established. The sslErrors() signal should have been emitted."));

    case QNetworkReply::TemporaryNetworkFailureError:
        return QString(tr("the connection was broken due to disconnection from the network, however the system has initiated roaming to another access point. The request should be resubmitted and will be processed as soon as the connection is re-established."));

    case QNetworkReply::NetworkSessionFailedError:
        return QString(tr("the connection was broken due to disconnection from the network or failure to start the network."));

    case QNetworkReply::BackgroundRequestNotAllowedError:
        return QString(tr("the background request is not currently allowed due to platform policy."));

    case QNetworkReply::TooManyRedirectsError:
        return QString(tr("while following redirects, the maximum limit was reached. The limit is by default set to 50 or as set by QNetworkRequest::setMaxRedirectsAllowed(). (This value was introduced in 5.6.)."));

    case QNetworkReply::InsecureRedirectError:
        return QString(tr("while following redirects, the network access API detected a redirect from a encrypted protocol (https) to an unencrypted one (http). (This value was introduced in 5.6.)."));

    case QNetworkReply::ProxyConnectionRefusedError:
        return QString(tr("the connection to the proxy server was refused (the proxy server is not accepting requests)."));

    case QNetworkReply::ProxyConnectionClosedError:
        return QString(tr("the proxy server closed the connection prematurely, before the entire reply was received and processed."));

    case QNetworkReply::ProxyNotFoundError:
        return QString(tr("the proxy host name was not found (invalid proxy hostname)."));

    case QNetworkReply::ProxyTimeoutError:
        return QString(tr("the connection to the proxy timed out or the proxy did not reply in time to the request sent."));

    case QNetworkReply::ProxyAuthenticationRequiredError:
        return QString(tr("the proxy requires authentication in order to honour the request but did not accept any credentials offered (if any)."));

    case QNetworkReply::ContentAccessDenied:
        return QString(tr("the access to the remote content was denied (similar to HTTP error 401)."));

    case QNetworkReply::ContentOperationNotPermittedError:
        return QString(tr("the operation requested on the remote content is not permitted."));

    case QNetworkReply::ContentNotFoundError:
        return QString(tr("the remote content was not found at the server (similar to HTTP error 404)."));

    case QNetworkReply::AuthenticationRequiredError:
        return QString(tr("the remote server requires authentication to serve the content but the credentials provided were not accepted (if any)."));

    case QNetworkReply::ContentReSendError:
        return QString(tr("the request needed to be sent again, but this failed for example because the upload data could not be read a second time."));

    case QNetworkReply::ContentConflictError:
        return QString(tr("the request could not be completed due to a conflict with the current state of the resource."));

    case QNetworkReply::ContentGoneError:
        return QString(tr("the requested resource is no longer available at the server."));

    case QNetworkReply::InternalServerError:
        return QString(tr("the server encountered an unexpected condition which prevented it from fulfilling the request."));

    case QNetworkReply::OperationNotImplementedError:
        return QString(tr("the server does not support the functionality required to fulfill the request."));

    case QNetworkReply::ServiceUnavailableError:
        return QString(tr("the server is unable to handle the request at this time."));

    case QNetworkReply::ProtocolUnknownError:
        return QString(tr("the Network Access API cannot honor the request because the protocol is not known."));

    case QNetworkReply::ProtocolInvalidOperationError:
        return QString(tr("the requested operation is invalid for this protocol."));

    case QNetworkReply::UnknownNetworkError:
        return QString(tr("an unknown network-related error was detected."));

    case QNetworkReply::UnknownProxyError:
        return QString(tr("an unknown proxy-related error was detected."));

    case QNetworkReply::UnknownContentError:
        return QString(tr("an unknown error related to the remote content was detected."));

    case QNetworkReply::ProtocolFailure:
        return QString(tr("a breakdown in protocol was detected (parsing error, invalid or unexpected responses, etc.)."));

    case QNetworkReply::UnknownServerError:
        return QString(tr("an unknown error related to the server response was detected"));
    default:
        return QString(tr("unknown error."));
    };
}

