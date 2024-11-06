#include "../headers/utils/exceptions.h"
#include "../headers/utils/statusCodes.h"
#include <QString>
#include <QException>

HandlingException::HandlingException(const QString& consoleMes, const QString& responseBodyMes, const QString& code)
    : message(consoleMes), responseBodyMes(responseBodyMes), code(code) {}

DbException::DbException(const QString& consoleMes, const QString& responseBodyMes, const QString& code)
    : HandlingException(consoleMes, responseBodyMes, code) {}

FileException::FileException(const QString& consoleMes, const QString& responseBodyMes, const QString& code)
    : HandlingException(consoleMes, responseBodyMes, code) {}

QueryException::QueryException(const QString& consoleMes, const QString& responseBodyMes, const QString& code)
    : DbException(consoleMes, responseBodyMes, code) {}

ServiceUnavailableException::ServiceUnavailableException(const QString& consoleMes, const QString& responseBodyMes)
    : DbException(consoleMes, responseBodyMes, StatusCode::SERVICE_UNAVAILABLE) {}

ConflictDbException::ConflictDbException(const QString& consoleMes, const QString& responseBodyMes)
    : QueryException(consoleMes, responseBodyMes, StatusCode::CONFLICT) {}

BadRequestException::BadRequestException(const QString& consoleMes, const QString& responseBodyMes)
    : QueryException(consoleMes, responseBodyMes, StatusCode::BAD_REQUEST) {}

NotFoundException::NotFoundException(const QString& consoleMes, const QString& responseBodyMes)
    : QueryException(consoleMes, responseBodyMes, StatusCode::NOT_FOUND) {}

QString HandlingException::getCode() {
    return this->code;
}

QString HandlingException::getMessage() {
    return message;
}

QByteArray HandlingException::getResponseBodyData() {
    return this->responseBodyMes.toUtf8();
}
