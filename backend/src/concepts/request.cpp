#include "../headers/concepts/Request.h"
#include <QByteArray>
#include <QByteArrayAlgorithms>
#include <QList>
#include <QDebug>

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
    qDebug() << "Body: ";
    for(auto& [key, value] : body) {
        qDebug() << "   " << key << " : " << value;
    }
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

    if(splitedRawUrl.length() > 1) {
        for(auto& oneQueryPair : splitedRawUrl[1].split('&')) {
            QList<QByteArray> splitedOneQueryPair = oneQueryPair.split('=');
            parsedReq.query[splitedOneQueryPair[0]] = splitedOneQueryPair[1];
        }
    }

    // Headers parsing
    tempInd = 1;
    QByteArray oneHeaderPair = splitedRawReq[tempInd];
    while (oneHeaderPair != "\n") {
        QList<QByteArray> splitedOneHeaderPair = oneHeaderPair.mid(1).split(':');
        parsedReq.headers[splitedOneHeaderPair[0]] = splitedOneHeaderPair[1].mid(1);

        oneHeaderPair = splitedRawReq[++tempInd];
    }

    // Body parsing
    if(splitedRawReq[tempInd + 1] == "") {
        return parsedReq;
    }

    QList<QByteArray> splitedBody = splitedRawReq[tempInd + 1].mid(2, splitedRawReq[tempInd + 1].length() - 3).replace("\"", "").split(',');
    for(auto &oneBodyPair : splitedBody) {
        tempInd = oneBodyPair.indexOf(':');
        parsedReq.body[oneBodyPair.mid(0, tempInd)] = oneBodyPair.mid(tempInd + 1);
    }

    return parsedReq;
}
