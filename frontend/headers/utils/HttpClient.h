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

    static void sendGetRequest(const QUrl &url, std::function<void(Response*)> handler, const QString& token = "");
    static void sendPostRequest(const QUrl &url, const QJsonObject &json, std::function<void(Response*)> handler, const QString& token = "");
    static void sendPostFileRequest(const QString &url, const QByteArray &body, const QString& contentType, std::function<void(Response*)> handler, const QString& token);
    static void sendDeleteRequest(const QUrl &url, std::function<void(Response*)> handler, const QString& token = "");
    static void sendPutRequest(const QUrl &url, const QJsonObject &json, std::function<void(Response*)> handler, const QString& token = "");
    static void sendPutFileRequest(const QString &url, const QByteArray &body, const QString& contentType, std::function<void(Response*)> handler, const QString& token = "");
private:
    HttpClient();

    static QNetworkAccessManager *manager;

    static Response* parseResponse(QNetworkReply *reply);
};

#endif // HTTPCLIENT_H
