#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <QByteArray>
#include "./statusCodes.h"

class HandlingException : public std::runtime_error {
public:
    explicit HandlingException(const std::string& consoleMes, const QByteArray& responseBodyMes, StatusCode code);

    StatusCode getCode();
    QByteArray getResponseBodyData();
protected:
    StatusCode code;
    QByteArray responseBodyMes;
};

class DbException : public HandlingException {
public:
    explicit DbException(const std::string& consoleMes, const QByteArray& responseBodyMes, StatusCode code);
};

class QueryException : public HandlingException {
public:
    explicit QueryException(const std::string& consoleMes, const QByteArray& responseBodyMes, StatusCode code);
};

class ConflictDbException : public QueryException {
    explicit ConflictDbException(const std::string& consoleMes, const QByteArray& responseBodyMes);
};

class BadRequestException : public QueryException {
    explicit BadRequestException(const std::string& consoleMes, const QByteArray& responseBodyMes);
};

class FileException : public HandlingException {
    explicit FileException(const std::string& consoleMes, const QByteArray& responseBodyMes, StatusCode code);
}


#endif // EXCEPTIONS_H
