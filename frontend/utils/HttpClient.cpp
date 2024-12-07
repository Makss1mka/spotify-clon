#include "../headers/utils/HttpClient.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <QTcpSocket>
#include <functional>
#include <QString>
#include <QUuid>
#include <QUrl>

QNetworkAccessManager* HttpClient::manager = new QNetworkAccessManager();
HttpClient::HttpClient() {}

void HttpClient::sendGetRequest(const QUrl &url, std::function<void(Response*)> handler, const QString& token) {
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentLengthHeader, 0);
    request.setRawHeader("X-Request-ID", QUuid::createUuid().toByteArray());
    if(token != "") request.setRawHeader("authorization", token.toUtf8());

    QNetworkReply *reply = manager->get(request);

    reply->connect(reply, &QNetworkReply::finished, [reply, handler]() {
        handler(parseResponse(reply));
    });
}

void HttpClient::sendPostRequest(const QUrl &url, const QJsonObject &json, std::function<void(Response*)> handler, const QString& token) {
    QNetworkRequest request(url);
    request.setRawHeader("X-Request-ID", QUuid::createUuid().toByteArray());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(QJsonDocument(json).toJson().size()));

    if(token != "") request.setRawHeader("Authorization", token.toUtf8());

    QNetworkReply *reply = manager->post(request, QJsonDocument(json).toJson());

    reply->connect(reply, &QNetworkReply::finished, [reply, handler]() {
        Response* response = parseResponse(reply);
        handler(response);
    });
}

void HttpClient::sendPostFileRequest(const QString &url, const QByteArray &body, const QString& contentType, std::function<void(Response*)> handler, const QString& token) {
    QTcpSocket* socket = new QTcpSocket();
    socket->connectToHost("localhost", 3000);

    if(!socket->waitForConnected(5000)) {
        qCritical() << "Cannot connect to server";
        return;
    }

    QString uuid = QUuid::createUuid().toString();
    QString header = "POST " + url + " HTTP/1.1"
            "\r\nhost: localhost:3000\r\ncontent-type: " + contentType +
            "\r\ncontent-length: " + QString::number(body.size()) +
            "\r\nconnection: Keep-Alive"
            "\r\nauthorization: " + token +
            "\r\nx-request-id: " + uuid +                         +
            "\r\naccept-encoding: gzip, deflate"
            "\r\naccept-language: ru-BY,en,*"
            "\r\nuser-agent: Mozilla/5.0"
            "\r\n"
            "\r\n";

    QByteArray packet = header.toUtf8();
    qDebug() << packet;

    for(int i = 0, k = 0; i < body.size(); i++) {
        packet += body[i];
        k++;

        if(k == 40000) {
            socket->write(packet);
            socket->flush();
            socket->waitForReadyRead();

            packet = header.toUtf8();
            k = 0;
        }
    }

    socket->write(packet);
    socket->flush();

    QObject::connect(socket, &QTcpSocket::readyRead, [socket](){
        qDebug() << "recieve";
    });
}

void HttpClient::sendPutRequest(const QUrl &url, const QJsonObject &json, std::function<void(Response*)> handler, const QString& token) {
    QNetworkRequest request(url);
    request.setRawHeader("X-Request-ID", QUuid::createUuid().toByteArray());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(QJsonDocument(json).toJson().size()));

    if(token != "") request.setRawHeader("Authorization", token.toUtf8());

    QNetworkReply *reply = manager->put(request, QJsonDocument(json).toJson());

    reply->connect(reply, &QNetworkReply::finished, [reply, handler]() {
        handler(parseResponse(reply));
    });
}

void HttpClient::sendPutFileRequest(const QString &url, const QByteArray &body, const QString& contentType, std::function<void(Response*)> handler, const QString& token) {
    QTcpSocket* socket = new QTcpSocket();
    socket->connectToHost("localhost", 3000);

    if(!socket->waitForConnected(5000)) {
        qCritical() << "Cannot connect to server";
        return;
    }

    QString uuid = QUuid::createUuid().toString();
    QString header = "PUT " + url + " HTTP/1.1"
            "\r\nhost: localhost:3000\r\ncontent-type: " + contentType +
            "\r\ncontent-length: " + QString::number(body.size()) +
            "\r\nconnection: Keep-Alive"
            "\r\nx-request-id: " + uuid +                         +
            "\r\naccept-encoding: gzip, deflate"
            "\r\naccept-language: ru-BY,en,*"
            "\r\nuser-agent: Mozilla/5.0"
            "\r\n"
            "\r\n";

    QByteArray packet = header.toUtf8();
    qDebug() << packet;

    for(int i = 0, k = 0; i < body.size(); i++) {
        packet += body[i];
        k++;

        if(k == 40000) {
            socket->write(packet);
            socket->flush();
            socket->waitForReadyRead();

            packet = header.toUtf8();
            k = 0;
        }
    }

    socket->write(packet);
    socket->flush();

    QObject::connect(socket, &QTcpSocket::readyRead, [socket](){
        qDebug() << "recieve";
    });
}

void HttpClient::sendDeleteRequest(const QUrl &url, std::function<void(Response*)> handler, const QString& token) {
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentLengthHeader, 0);
    request.setRawHeader("X-Request-ID", QUuid::createUuid().toByteArray());
    if(token != "") request.setRawHeader("Authorization", token.toUtf8());

    QNetworkReply *reply = manager->deleteResource(request);

    reply->connect(reply, &QNetworkReply::finished, [reply, handler]() {
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
        } else {
            response->isBodyNoneJson = true;
            response->body = rawBody;
        }
    } else {
        response->isBodyNoneJson = true;
        response->body = reply->readAll();
    }
    reply->deleteLater();

    return response;
}
