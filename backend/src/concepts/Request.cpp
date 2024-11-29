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

Request::Request() {}

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

Request Request::parseFromQByteArray(QByteArray rawReq) {
    Request parsedReq;

    if (rawReq == "") {
        return parsedReq;
    }

    QList<QByteArray> splitedRawReq = rawReq.split('\r');
    int tempInd = splitedRawReq[0].indexOf(" /");

    // Parsing method
    parsedReq.method = splitedRawReq[0].mid(0, tempInd);

    // Url-Query Parsing
    QByteArray rawUrl = splitedRawReq[0].mid(tempInd + 1, splitedRawReq[0].indexOf(" ", tempInd + 1) - parsedReq.method.length() - 1);
    QList<QByteArray> splitedRawUrl = rawUrl.split('?');

    parsedReq.url = splitedRawUrl[0];

    if (splitedRawUrl.size() > 1) {
        QUrlQuery query = QUrlQuery(splitedRawUrl[1]);

        QList<QPair<QString, QString>> items = query.queryItems();
        for(const QPair<QString, QString> &item : items) {
            parsedReq.query[item.first] = item.second;
        }
    }

    // Headers parsing
    tempInd = 1;
    QByteArray oneHeaderPair = splitedRawReq[tempInd];
    while (oneHeaderPair != "\n") {
        QList<QByteArray> splitedOneHeaderPair = oneHeaderPair.mid(1).split(':');
        parsedReq.headers.set(splitedOneHeaderPair[0], splitedOneHeaderPair[1].mid(1));

        oneHeaderPair = splitedRawReq[++tempInd];
    }

    // Body parsing
    if(splitedRawReq[tempInd + 1] == "") {
        return parsedReq;
    }

    QJsonDocument jsonDoc = QJsonDocument::fromJson(splitedRawReq[tempInd + 1]);
    if (!jsonDoc.isNull()) {
        if (jsonDoc.isObject()) {
            parsedReq.isBodyJsonObj = true;
            parsedReq.bodyJsonObj = jsonDoc.object();
        } else if (jsonDoc.isArray()) {
            parsedReq.isBodyJsonArray = true;
            parsedReq.bodyJsonArray = jsonDoc.array();
        }
    } else {
        parsedReq.isBodyNoneJson = true;
        parsedReq.bodyNoneJson = splitedRawReq[tempInd + 1];
    }

    return parsedReq;
}

bool Request::isInt(const QString& str) {
    bool ok;
    str.toInt(&ok);
    return ok;
}
