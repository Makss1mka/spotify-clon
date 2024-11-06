#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <QByteArray>
#include <QString>
#include <QException>
#include "./statusCodes.h"

class HandlingException : public QException {
public:
    explicit HandlingException(const QString& consoleMes, const QString& responseBodyMes, const QString& code);

    QString getCode();
    QString getMessage();
    QByteArray getResponseBodyData();
protected:
    QString code;
    QString responseBodyMes;
    QString message;
};

class DbException : public HandlingException {
public:
    explicit DbException(const QString& consoleMes, const QString& responseBodyMes, const QString& code);
};

class QueryException : public DbException {
public:
    explicit QueryException(const QString& consoleMes, const QString& responseBodyMes, const QString& code);
};

class ServiceUnavailableException : public DbException {
public:
    explicit ServiceUnavailableException(const QString& consoleMes, const QString& responseBodyMes);
};

class ConflictDbException : public QueryException {
public:
    explicit ConflictDbException(const QString& consoleMes, const QString& responseBodyMes);
};

class BadRequestException : public QueryException {
public:
    explicit BadRequestException(const QString& consoleMes, const QString& responseBodyMes);
};

class NotFoundException : public QueryException {
public:
    explicit NotFoundException(const QString& consoleMes, const QString& responseBodyMes);
};

class FileException : public HandlingException {
public:
    explicit FileException(const QString& consoleMes, const QString& responseBodyMes, const QString& code);
};


#endif // EXCEPTIONS_H
