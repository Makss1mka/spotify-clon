#ifndef STATUSCODES_H
#define STATUSCODES_H

#include <QString>
#include <QByteArray>

namespace StatusCode {
    extern QString CONTINUE;
    extern QString SWITCHING_PROTOCOLS;
    extern QString OK;
    extern QString CREATED;
    extern QString ACCEPTED;
    extern QString NO_CONTENT;
    extern QString MOVED_PERMANENTLY;
    extern QString FOUND;
    extern QString NOT_MODIFIED;
    extern QString BAD_REQUEST;
    extern QString UNAUTHORIZED;
    extern QString FORBIDDEN;
    extern QString NOT_FOUND;
    extern QString METHOD_NOT_ALLOWED;
    extern QString CONFLICT;
    extern QString TOO_MANY_REQUESTS;
    extern QString INTERNAL_SERVER_ERROR;
    extern QString NOT_IMPLEMENTED;
    extern QString BAD_GETAWAY;
    extern QString SERVICE_UNAVAILABLE;
    extern QString GATEWAY_TIMEOUT;
}

#endif // STATUSCODES_H
