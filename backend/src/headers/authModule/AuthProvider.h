#ifndef AUTHPROVIDER_H
#define AUTHPROVIDER_H

#include "../concepts/Provider.h"
#include "../concepts/Request.h"
#include <QByteArray>

class AuthProvider : public Provider {
public:
    AuthProvider();
    QByteArray registerUser(const QString& login, const QString& email, const QString& password);
    QByteArray authUser(const QString& login, const QString& email, const QString& password);
};

#endif // AUTHPROVIDER_H
