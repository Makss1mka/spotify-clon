#ifndef REQUEST_H
#define REQUEST_H

#include <map>
#include <QByteArray>
#include <QString>

class Request {
public:
    static Request parseFromQByteArray(QByteArray rawReq);

    Request();
    void print();

    QString method;
    QString url;
    std::map<QString, QString> query;
    std::map<QString, QString> headers;
    std::map<QString, QString> body;
};

#endif // REQUEST_H
