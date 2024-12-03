#include "../headers/utils/exceptions.h"
#include "../headers/concepts/Request.h"
#include "../headers/concepts/JWT.h"
#include <QCryptographicHash>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <QDateTime>
#include <QString>
#include <QList>

JWT::JWT() {}

QByteArray JWT::creaateToken(const QString& credits, int userId, const QString& secret, int expiresInSeconds) {
    QJsonObject header;
    header["alg"] = "HS256";
    header["typ"] = "JWT";

    QJsonObject payload;
    payload["id"] = userId;
    payload["credits"] = credits;
    payload["iat"] = QDateTime::currentSecsSinceEpoch();
    payload["exp"] = QDateTime::currentSecsSinceEpoch() + expiresInSeconds;

    QByteArray headerBase64 = toBase64(header);
    QByteArray payloadBase64 = toBase64(payload);
    QByteArray signature = sign(headerBase64 + "." + payloadBase64, secret);

    return headerBase64 + "." + payloadBase64 + "." + signature;
}

bool JWT::verifyToken(const QByteArray& token, const QString& secret) {
    QList<QByteArray> parts = token.split('.');
    if (parts.size() != 3) return false;

    if (sign(parts[0] + "." + parts[1], secret) != parts[2]) return false;

    QByteArray payloadJson = QByteArray::fromBase64(parts[1], QByteArray::Base64UrlEncoding);
    QJsonObject obj = QJsonDocument::fromJson(payloadJson).object();
    if (obj.contains("exp")) {
        qint64 exp = obj["exp"].toInteger();
        qint64 currentTime = QDateTime::currentSecsSinceEpoch();
        if (exp < currentTime) {
            return false;
        }
    } else {
        return false;
    }

    return true;
}

void JWT::verifyTokenAndThrow(const Request& request, const QString& secret) {
    if (request.headers.count("authorization") == 0) {
        throw BadRequestException(
            "Request without token",
            "Request without token"
        );
    }

    if (JWT::verifyToken(request.headers.get("authorization").toUtf8(), secret) == false) {
        throw QueryException(
            "Invalid token",
            "Invalid token",
            StatusCode::UNAUTHORIZED
        );
    }
}

QString JWT::getUsernameFromToken(const QByteArray& token) {
    QList<QByteArray> parts = token.split('.');
    if (parts.size() != 3) return "";

    QByteArray payloadJson = QByteArray::fromBase64(parts[1], QByteArray::Base64UrlEncoding);
    QJsonDocument doc = QJsonDocument::fromJson(payloadJson);
    QJsonObject obj = doc.object();

    return obj["credits"].toString();
}

int JWT::getUserIdFromToken(const QByteArray& token) {
    QList<QByteArray> parts = token.split('.');
    if (parts.size() != 3) return -1;

    QByteArray payloadJson = QByteArray::fromBase64(parts[1], QByteArray::Base64UrlEncoding);
    QJsonDocument doc = QJsonDocument::fromJson(payloadJson);
    QJsonObject obj = doc.object();

    return obj["id"].toInt();
}

QByteArray JWT::toBase64(const QJsonObject& cryptable) {
    return QJsonDocument(cryptable).toJson(QJsonDocument::Compact).toBase64(QByteArray::Base64UrlEncoding | QByteArray::OmitTrailingEquals);
}

QByteArray JWT::sign(const QByteArray& message, const QString& secret) {
    QByteArray key = secret.toUtf8();
    qDebug() << QCryptographicHash::hash(message + key, QCryptographicHash::Sha256).toBase64(QByteArray::Base64UrlEncoding | QByteArray::OmitTrailingEquals);
    return QCryptographicHash::hash(message + key, QCryptographicHash::Sha256).toBase64(QByteArray::Base64UrlEncoding | QByteArray::OmitTrailingEquals);
}
