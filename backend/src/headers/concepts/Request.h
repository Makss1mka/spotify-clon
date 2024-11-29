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
    static Request parseFromQByteArray(QByteArray rawReq);
    static bool isInt(const QString& str);

    Request();
    void print();

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
