#include "../headers/utils/statusCodes.h"
#include <QString>

namespace StatusCode {
    QString CONTINUE = "100 Continue";
    QString SWITCHING_PROTOCOLS = "101 Switching Protocols";
    QString OK = "200 OK";
    QString CREATED = "201 Created";
    QString ACCEPTED = "202 Accepted";
    QString NO_CONTENT = "204 No Content";
    QString MOVED_PERMANENTLY = "301 Moved Permanently";
    QString FOUND = "302 Found";
    QString NOT_MODIFIED = "304 Not Modified";
    QString BAD_REQUEST = "400 Bad Request";
    QString UNAUTHORIZED = "401 Unauthorized";
    QString FORBIDDEN = "403 Forbidden";
    QString NOT_FOUND = "404 Not Found";
    QString METHOD_NOT_ALLOWED = "405 Method Not Allowed";
    QString CONFLICT = "409 Conflict";
    QString TOO_MANY_REQUESTS = "429 Too Many Requests";
    QString INTERNAL_SERVER_ERROR = "500 Internal Server Error";
    QString NOT_IMPLEMENTED = "501 Not Implemented";
    QString BAD_GETAWAY = "502 Bad Gateway";
    QString SERVICE_UNAVAILABLE = "503 Service Unavailable";
    QString GATEWAY_TIMEOUT = "504 Gateway Timeout";
}
