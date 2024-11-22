#include "../headers/utils/HttpClient.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <functional>
#include <QUrl>

HttpClient::HttpClient() {
    manager = new QNetworkAccessManager();
}

void HttpClient::sendGetRequest(const QUrl &url, std::function<void(Response*)> handler) {
    QNetworkRequest request(url);

    QNetworkReply *reply = manager->get(request);

    reply->connect(reply, &QNetworkReply::finished, [this, reply, handler]() {
        handler(parseResponse(reply));
    });
}

void HttpClient::sendPostRequest(const QUrl &url, const QJsonObject &json, std::function<void(Response*)> handler) {
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, QJsonDocument(json).toJson());

    reply->connect(reply, &QNetworkReply::finished, [this, reply, handler]() {
        Response* response = parseResponse(reply);
        handler(response);
    });
}

void HttpClient::sendPutRequest(const QUrl &url, const QJsonObject &json, std::function<void(Response*)> handler) {
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->put(request, QJsonDocument(json).toJson());

    reply->connect(reply, &QNetworkReply::finished, [this, reply, handler]() {
        handler(parseResponse(reply));
    });
}

void HttpClient::sendDeleteRequest(const QUrl &url, std::function<void(Response*)> handler) {
    QNetworkRequest request(url);

    QNetworkReply *reply = manager->deleteResource(request);

    reply->connect(reply, &QNetworkReply::finished, [this, reply, handler]() {
        handler(parseResponse(reply));
    });
}

HttpClient::Response* HttpClient::parseResponse(QNetworkReply *reply) {
    Response* response = new Response();

    response->statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    for (auto &header : reply->rawHeaderList()) {
        response->headers[header] = reply->rawHeader(header);
    }

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray rawBody = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(rawBody);

        if (jsonDoc.isObject()) {
            response->isBodyJsonObj = true;
            response->bodyJsonObj = jsonDoc.object();
        } else if (jsonDoc.isArray()) {
            response->isBodyJsonArray = true;
            response->bodyJsonArray = jsonDoc.array();
        }
    } else {
        response->isBodyNoneJson = true;
        response->body = reply->readAll();
    }
    reply->deleteLater();

    return response;
}
