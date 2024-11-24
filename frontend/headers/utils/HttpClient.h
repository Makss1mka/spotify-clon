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
    HttpClient(const HttpClient&) = delete;
    void operator=(const HttpClient&) = delete;

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

    static void sendGetRequest(const QUrl &url, std::function<void(Response*)> handler);
    static void sendPostRequest(const QUrl &url, const QJsonObject &json, std::function<void(Response*)> handler);
    static void sendDeleteRequest(const QUrl &url, std::function<void(Response*)> handler);
    static void sendPutRequest(const QUrl &url, const QJsonObject &json, std::function<void(Response*)> handler);
private:
    HttpClient();

    static QNetworkAccessManager *manager;

    static Response* parseResponse(QNetworkReply *reply);
};

#endif // HTTPCLIENT_H
