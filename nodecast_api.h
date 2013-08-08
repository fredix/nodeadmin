#ifndef NODECAST_API_H
#define NODECAST_API_H

#include <QtNetwork>
#include <QThread>
#include <QJsonDocument>
#include <QMessageBox>
#include <QMutex>

class Nodecast_api : public QObject
{
    Q_OBJECT

public:
    explicit Nodecast_api(QString a_server, QString m_http_port, QObject *parent = 0);
    ~Nodecast_api();
    void users_get(QString admin_token);
    void nodes_get(QString admin_token);
    void node_post(QString admin_token);

    QString m_credentials;
    QString m_filename;
    QString m_server;
    QString m_user_email;
    QString m_user_password;

    QString m_http_port;
    QString m_node_uuid;
    QString m_node_password;
    QString m_push_method;
    QNetworkAccessManager *m_network;


public slots:
    void slotRequestFinished(QNetworkReply *);
    void replyError(QNetworkReply::NetworkError errorCode);

private slots:
    void init();
    void session_get(QString uuid);

signals:
    void api_error(QString error);
    void httpResponse(int http_error);
    void users_Changed(QVariantMap user);
    void nodes_Changed(QVariantMap node);

    void status_Changed(QString status, QString filename);
    void get_Token(QString token);

private:
    QMutex *m_mutex;
    void payload_push();
    QString session_uuid;
    QTimer *session_get_timer;
    QByteArray *m_content;
    QNetworkReply *m_reply;
    QUrl url_get;
    QUrl url_push;
    QNetworkRequest m_request;
    QAuthenticator *m_auth;
    QString m_post_response;
    int m_http_error;


};


#endif // NODECAST_API_H
