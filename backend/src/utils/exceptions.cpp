#include "../headers/utils/exceptions.h"
#include "../headers/utils/statusCodes.h"

HandlingException::HandlingException(const std::string &consoleMes, const QByteArray& responseBodyMes, StatusCode code)
    : std::runtime_error(consoleMes), responseBodyMes(responseBodyMes), code(code) {}

DbException::DbException(const std::string &consoleMes, const QByteArray& responseBodyMes, StatusCode code)
    : HandlingException(consoleMes, responseBodyMes, code) {}

FileException::FileException(const std::string &consoleMes, const QByteArray& responseBodyMes, StatusCode code)
    : HandlingException(consoleMes, responseBodyMes, code) {}

QueryException::QueryException(const std::string &consoleMes, const QByteArray& responseBodyMes, StatusCode code)
    : DbException(consoleMes, responseBodyMes, code) {}

ConflictDbException::ConflictDbException(const std::string &consoleMes, const QByteArray& responseBodyMes)
    : QueryException(consoleMes, responseBodyMes, CONFLICT) {}

BadRequestException::BadRequestException(const std::string &consoleMes, v responseBodyMes)
    : QueryException(consoleMes, responseBodyMes, BAD_REQUEST) {}
