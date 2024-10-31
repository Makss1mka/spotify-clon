#ifndef AUTHPROVIDER_H
#define AUTHPROVIDER_H

#include "../concepts/Provider.h"
#include "../concepts/Request.h"
#include <QByteArray>

class AuthProvider : public Provider {
public:
    AuthProvider();
    QByteArray registerUser(QString& login, QString& email, QString& password);
    QByteArray authUser(QString& login, QString& email, QString& password);
};

#endif // AUTHPROVIDER_H
