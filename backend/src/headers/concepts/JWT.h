#ifndef JWT_H
#define JWT_H

#include "./Request.h"
#include <QJsonObject>
#include <QByteArray>
#include <QString>

class JWT {
public:
    JWT();

    static QByteArray creaateToken(const QString& credits, int userId, const QString& secret, int expiresInSeconds);
    static bool verifyToken(const QByteArray& token, const QString& secret);
    static void verifyTokenAndThrow(const Request& token, const QString& secret);
    static QString getUsernameFromToken(const QByteArray& token);
    static int getUserIdFromToken(const QByteArray& token);
private:
    static QByteArray toBase64(const QJsonObject& cryptable);
    static QByteArray sign(const QByteArray& message, const QString& secret);
};

#endif // JWT_H
