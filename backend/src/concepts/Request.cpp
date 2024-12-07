#include "../headers/concepts/Request.h"
#include <QByteArrayAlgorithms>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QByteArray>
#include <QUrlQuery>
#include <QList>
#include <QPair>
#include <QUrl>

Request::Request() {
    isEmpty = true;
}

void Request::clear() {

}

void Request::print() {
    qDebug() << "Method: " << method << "\nUrl: " << url << "\nQuery: ";
    for(auto& [key, value] : query) {
        qDebug() << "   " << key << " : " << value;
    }
    qDebug() << "Headers: ";
    for(auto& [key, value] : headers) {
        qDebug() << "   " << key << " : " << value;
    }

    if (isBodyJsonArray == true) qDebug() << "Body: " << bodyJsonArray;
    if (isBodyJsonObj == true) qDebug() << "Body: " << bodyJsonObj;
    if (isBodyNoneJson == true) qDebug() << "Body: " << bodyNoneJson;
}

void Request::printWithoutPrety() {
    QString result = "";

    result += "Method: " + method + " Url: " + url + " Query: ";
    for(auto& [key, value] : query) {
        result +=  " " + key + " : " + value;
    }
    result += " Headers: ";
    for(auto& [key, value] : headers) {
        result += " " + key + " : " + value;
    }

    qDebug() << result;
    if (isBodyJsonArray == true) qDebug() << "Body: " << bodyJsonArray;
    if (isBodyJsonObj == true) qDebug() << "Body: " << bodyJsonObj;
    if (isBodyNoneJson == true) qDebug() << "Body: " << bodyNoneJson;
}

void Request::parseBody() {
    QJsonDocument jsonDoc = QJsonDocument::fromJson(bodyNoneJson);
    if (!jsonDoc.isNull()) {
        if (jsonDoc.isObject()) {
            isBodyJsonObj = true;
            bodyJsonObj = jsonDoc.object();
        } else if (jsonDoc.isArray()) {
            isBodyJsonArray = true;
            bodyJsonArray = jsonDoc.array();
        }
        isBodyNoneJson = false;
    }
}

void Request::parseFromQByteArrayWithoutBodyParsing(QByteArray rawReq) {
    if (rawReq == "") {
        return;
    }

    QList<QByteArray> splitedRawReq = rawReq.split('\r');
    int tempInd = splitedRawReq[0].indexOf(" /");

    // Parsing method
    this->method = splitedRawReq[0].mid(0, tempInd);

    // Url-Query Parsing
    QByteArray rawUrl = splitedRawReq[0].mid(tempInd + 1, splitedRawReq[0].indexOf(" ", tempInd + 1) - this->method.length() - 1);
    QList<QByteArray> splitedRawUrl = rawUrl.split('?');

    this->url = splitedRawUrl[0];

    if (splitedRawUrl.size() > 1) {
        QUrlQuery query = QUrlQuery(splitedRawUrl[1]);

        QList<QPair<QString, QString>> items = query.queryItems();
        for(const QPair<QString, QString> &item : items) {
            this->query[item.first] = item.second;
        }
    }

    // Headers parsing
    tempInd = 1;
    QByteArray oneHeaderPair = splitedRawReq[tempInd];
    while (oneHeaderPair != "\n") {
        QList<QByteArray> splitedOneHeaderPair = oneHeaderPair.mid(1).split(':');
        this->headers.set(splitedOneHeaderPair[0], splitedOneHeaderPair[1].mid(1));

        oneHeaderPair = splitedRawReq[++tempInd];
    }

    // Body extracting
    if(splitedRawReq[tempInd + 1] != "" && splitedRawReq[tempInd + 1] != '\n') {
        tempInd++;
        //qDebug() << "first  " << splitedRawReq[tempInd];

        this->bodyNoneJson = splitedRawReq[tempInd++].mid(1);

        for(; tempInd < splitedRawReq.size(); tempInd++) {
            this->bodyNoneJson += '\r' + splitedRawReq[tempInd];
        }

        this->isBodyNoneJson = true;
    }

    this->isEmpty = false;
}

bool Request::isInt(const QString& str) {
    bool ok;
    str.toInt(&ok);
    return ok;
}
