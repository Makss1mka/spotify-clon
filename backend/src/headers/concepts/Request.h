#ifndef REQUEST_H
#define REQUEST_H

#include <map>
#include <QByteArray>
#include <iostream>

class Request {
public:
    static Request parseFromQByteArray(QByteArray rawReq);

    Request();
    void print();

    QByteArray method;
    QByteArray url;
    std::map<QByteArray, QByteArray> query;
    std::map<QByteArray, QByteArray> headers;
    std::map<QByteArray, QByteArray> body;
};

#endif // REQUEST_H
