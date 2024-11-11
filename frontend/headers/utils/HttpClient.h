#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QUrl>

class HttpClient {
public:
    HttpClient();

    void sendGetRequest(const QUrl &url);

    void sendPostRequest(const QUrl &url, const QJsonObject &json);

private:
    QNetworkAccessManager *manager;

    void processReply(QNetworkReply *reply);
};

#endif // HTTPCLIENT_H
