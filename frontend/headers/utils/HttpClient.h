#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonArray>
#include <functional>

class HttpClient {
public:
    HttpClient();

    class Response {
    public:
        int statusCode;
        std::map<QByteArray, QByteArray> headers;

        bool isBodyJsonObj = false;
        QJsonObject bodyJsonObj;

        bool isBodyJsonArray = false;
        QJsonArray bodyJsonArray;

        bool isBodyNoneJson = false;
        QByteArray body;
    };

    void sendGetRequest(const QUrl &url, std::function<void(const Response&)> handler);
    void sendPostRequest(const QUrl &url, const QJsonObject &json, std::function<void(const Response&)> handler);
    void sendDeleteRequest(const QUrl &url, std::function<void(const Response&)> handler);
    void sendPutRequest(const QUrl &url, const QJsonObject &json, std::function<void(const Response&)> handler);
private:
    QNetworkAccessManager *manager;

    Response parseResponse(QNetworkReply *reply);
};

#endif // HTTPCLIENT_H
