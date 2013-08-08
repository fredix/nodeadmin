#include "nodecast_api.h"


Nodecast_api::Nodecast_api(QString a_server, QString a_http_port, QObject *parent) : m_server(a_server), m_http_port(a_http_port), QObject(parent)
{
    m_mutex = new QMutex();
    m_network = new QNetworkAccessManager(this);
    m_post_response = "";
    m_http_error = 0;
    m_push_method = "http";
    session_uuid = "";

    m_request.setRawHeader("content-type", "application/xml");

    this->connect( m_network, SIGNAL(finished(QNetworkReply *)),SLOT(slotRequestFinished(QNetworkReply *)));
}



Nodecast_api::~Nodecast_api()
{
    delete(m_network);
}

void Nodecast_api::init()
{


    //this->connect(this, SIGNAL(uuid_Changed(QString), this, SLOT())

//    payload_push();

 /*   session_get_timer = new QTimer();
    connect(session_get_timer, SIGNAL(timeout()), this, SLOT(session_get (QString)), Qt::DirectConnection);
    session_get_timer->start (2000);
    */
}


// curl -H "X-user-email: user@email.com" -H "X-user-password: password" http://zerogwAPI:8000/ftpauth
void Nodecast_api::users_get(QString admin_token)
{
   // m_mutex->lock();

    m_request.setRawHeader("X-admin-token", admin_token.toLatin1());

    url_get.setUrl("http://" + m_server + ":" + m_http_port + "/users/");

    qDebug() << "users_get " << " SERVER : " << m_server;
    m_request.setUrl(url_get);
    m_reply = m_network->get(m_request);
}



// curl -H "X-user-email: user@email.com" -H "X-user-password: password" http://zerogwAPI:8000/ftpauth
void Nodecast_api::nodes_get(QString admin_token)
{
  //  m_mutex->lock();

    m_request.setRawHeader("X-user-token", admin_token.toLatin1());

    url_get.setUrl("http://" + m_server + ":" + m_http_port + "/nodes/");

    qDebug() << "nodes_get " << " SERVER : " << m_server;
    m_request.setUrl(url_get);
    m_reply = m_network->get(m_request);
}



// curl -H "X-user-email: user@email.com" -H "X-user-password: password" http://zerogwAPI:8000/ftpauth
void Nodecast_api::node_post(QString admin_token)
{
  //  m_mutex->lock();
   // QJsonDocument json;


    m_request.setRawHeader("X-user-token", "e5c71ae4-533a-474c-acb1-84fc688ff707");
    //m_request.setRawHeader("X-node-name", admin_token.toLatin1());

    url_get.setUrl("http://" + m_server + ":" + m_http_port + "/nodes/");

    qDebug() << "node_post " << " SERVER : " << m_server;
    m_request.setUrl(url_get);
    m_reply = m_network->post(m_request, admin_token.toLatin1());
}




// Get infos about a payload
// curl http://127.0.0.1:4567/session/e90b54bd-5e63-4c12-9e6b-0731f58c0e01
void Nodecast_api::session_get(QString uuid)
{

    if (!uuid.isEmpty())
    {
        url_get.setUrl("http://" + m_server + ":" + m_http_port + "/session/" + uuid);

        qDebug() << "session_get " << m_node_uuid << " SERVER : " << m_server;
        m_request.setUrl(url_get);

        m_reply = m_network->get(m_request);
    }

}


/*
 * curl -H "X-node-uuid: 0d7f9bdc-37a2-4290-be41-62598bd7a525"
 *      -H "X-node-password: 6786a141-6dff-4f91-891a-a9107915ad76"
 *      -H "X-workflow-uuid: 9ace693a-a4e2-4140-872f-a8382b82731c"
 *      -H "X-payload-type: junk"
 *      -d '{ "filename": "toto.mp4" }' http://127.0.0.1:4567/payload/push/
 */

void Nodecast_api::payload_push()
{


    //qDebug() << "payload and pass : " << m_credentials;


    //QDateTime timestamp = QDateTime::currentDateTime();
    //QString s_timestamp = "geekast_" + timestamp.toString("hhmmssz-ddMMyyyy")  + ".json";


    //QString json = "{\"format\":\"json\", \"length\":\"58\"}";


    //qDebug() << "JSON : " << json;

    //QVariantMap payload;
    //payload.insert("filename", m_filename);
    //QString json = QxtJSON::stringify(payload);

    QString json = "{\"filename\": \"" + m_filename + "\"}";

    //m_request.setRawHeader("Authorization", "Basic " + QByteArray((m_credentials).toAscii()).toBase64());
    m_request.setRawHeader("content-type", "multipart/form-data");
    //m_request.setRawHeader("Host", url.encodedHost());

    m_request.setRawHeader("User-Agent", "pumituploader");
    m_request.setRawHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    m_request.setRawHeader("Accept-Language", "en,en-us;q=0.7,en;q=0.3");
    m_request.setRawHeader("Accept-Encoding", "gzip,deflate");
    m_request.setRawHeader("Accept-Charset", "windows-1251,utf-8;q=0.7,*;q=0.7");
    m_request.setRawHeader("Keep-Alive", "300");
    m_request.setRawHeader("Connection", "keep-alive");
    m_request.setRawHeader("X-node-uuid", "0d7f9bdc-37a2-4290-be41-62598bd7a525");
    m_request.setRawHeader("X-node-password", "6786a141-6dff-4f91-891a-a9107915ad76");
    m_request.setRawHeader("X-workflow-uuid", "9ace693a-a4e2-4140-872f-a8382b82731c");
    m_request.setRawHeader("X-payload-type", "video");


    //request.setRawHeader("Referer", QString("http://%1data.cod.ru/").arg(region).toAscii());
    //m_request.setRawHeader("Content-Type", QByteArray("multipart/form-data; boundary=").append(boundaryRegular));

    // qDebug() << QString::fromAscii(QByteArray(m_request.rawHeader( "Authorization" )).fromBase64());

 //   qDebug() << m_request.rawHeader( "Authorization" ) << m_credentials.toAscii().toBase64();


        url_push.setUrl("http://" + m_server + ":" + m_http_port + "/payload/push/");
        qDebug() << "PAYLOAD PUSH : " << m_filename;
        m_request.setUrl(url_push);
        m_reply = m_network->post(m_request, json.toUtf8());



    this->connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(replyError(QNetworkReply::NetworkError)));



}



void Nodecast_api::slotRequestFinished(QNetworkReply *) {

    m_http_error = m_reply->error();
    qDebug() << "HTTP ERROR : " << m_http_error;

    emit httpResponse(m_http_error);

    m_post_response = m_reply->readAll();


    qDebug() << "HTTP RESPONSE : " << m_post_response;

    QJsonDocument json = QJsonDocument::fromJson(m_post_response.toLatin1());

    QVariant vjson = json.toVariant();
    qDebug() << "VARIANT: " << vjson;

    if (vjson.toMap().contains("users"))
    {

       // QJsonDocument users = vjson.toMap()["users"].toJsonDocument();


        QVariantList users = vjson.toMap()["users"].toList();


        //QVariantList users = json.toVariant().value("users").toList();
        foreach (QVariant user, users)
        {
            QVariantMap user_info = user.toMap();

            //qDebug() << "EMAIL  : " << user_info["email"].toString();

            emit users_Changed(user_info);
        }


    }

    if (vjson.toMap().contains("nodes"))
    {

       // QJsonDocument users = vjson.toMap()["users"].toJsonDocument();


        QVariantList nodes = vjson.toMap()["nodes"].toList();


        //QVariantList users = json.toVariant().value("users").toList();
        foreach (QVariant node, nodes)
        {
            QVariantMap node_info = node.toMap();

            //qDebug() << "EMAIL  : " << user_info["email"].toString();

            emit nodes_Changed(node_info);
        }


    }

    else if (vjson.toMap().contains("status"))
    {
        QString status = vjson.toMap()["status"].toString();
        emit status_Changed(status, m_filename);
    }
    else if (vjson.toMap().contains("token"))
    {
        QString token = vjson.toMap()["token"].toString();
        emit get_Token(token);
    }
    else if(vjson.toMap().contains("error"))
    {
  /*      QMessageBox::information(this, tr("FTP"),
                                 tr("Unable to login to the FTP server, error : "
                                    "%1. Please check that email or password are correct.")
                                 .arg(vjson.toMap()["code"].toString()));
*/
        qDebug() << "API ERROR1 : " << vjson.toMap()["error"].toString();
        qDebug() << "API ERROR1 : " << vjson.toMap()["code"].toString();

        qDebug() << "API ERROR1 : " << tr("Unable to login to the FTP server"
                                  ". error : %1 , code : %2")
                               .arg(vjson.toMap()["error"].toString()).arg(vjson.toMap()["code"].toString());

        emit api_error(tr("Unable to login to the FTP server"
                          ". error : %1 , code : %2")
                       .arg(vjson.toMap()["error"].toString()).arg(vjson.toMap()["code"].toString()));

        qDebug() << "API ERROR2";
        //{"code":"unknown user","error":"auth"}"
    }

    m_post_response = "";

    //m_mutex->unlock();
}




void Nodecast_api::replyError(QNetworkReply::NetworkError errorCode)
{

    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    switch(errorCode)
    {
    case QNetworkReply::TimeoutError:
    {
        qDebug() << "Push::replyError HTTP ERROR TIMEOUT !";
        //m_requestList.remove(QString::fromStdString(m_request));
        reply->deleteLater();
        //finished();
    }
    case QNetworkReply::HostNotFoundError:
    {
        qDebug() << "Push::replyError HOST NOT FOUND";
        //m_requestList.remove(QString::fromStdString(m_request));
        reply->deleteLater();
        //finished();
    }
    case QNetworkReply::ConnectionRefusedError:
    {
        qDebug() << "Push::replyError Connection refused";
        //m_requestList.remove(QString::fromStdString(m_request));
        reply->deleteLater();
        //finished();
    }

    default:
    {
        qDebug() << "Push::replyError HTTP ERROR DEFAULT ! errorcode : " << errorCode;
        break;
    }
    }
}
