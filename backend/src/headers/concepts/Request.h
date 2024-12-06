#ifndef REQUEST_H
#define REQUEST_H

#include <map>
#include <QByteArray>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include "../utils/Map.h"

class Request {
public:
    static bool isInt(const QString& str);

    Request();
    void print();
    void clear();
    void printWithoutPrety();
    void parseFromQByteArrayWithoutBodyParsing(QByteArray rawReq);
    void parseBody();

    bool isEmpty;
    QString method;
    QString url;
    std::map<QString, QString> query;
    Map<QString, QString> headers;

    bool isBodyJsonObj = false;
    QJsonObject bodyJsonObj;

    bool isBodyJsonArray = false;
    QJsonArray bodyJsonArray;

    bool isBodyNoneJson = false;
    QByteArray bodyNoneJson;
};

#endif // REQUEST_H
