#include "../headers/utils/HttpClient.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>

HttpClient::HttpClient() {
    manager = new QNetworkAccessManager();
}

void HttpClient::sendGetRequest(const QUrl &url) {
    QNetworkRequest request(url);

    QNetworkReply *reply = manager->get(request);

    reply->connect(reply, &QNetworkReply::finished, [this, reply]() {
        processReply(reply);
    });
}

void HttpClient::sendPostRequest(const QUrl &url, const QJsonObject &json) {
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, QJsonDocument(json).toJson());

    reply->connect(reply, &QNetworkReply::finished, [this, reply]() {
        processReply(reply);
    });
}

void HttpClient::processReply(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        qDebug() << "Response:" << response;
    } else {
        qDebug() << "Error:" << reply->errorString();
    }
    reply->deleteLater();
}
