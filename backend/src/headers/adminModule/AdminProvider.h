#ifndef ADMINPROVIDER_H
#define ADMINPROVIDER_H

#include "../concepts/Provider.h"
#include <QByteArray>

class AdminProvider : public Provider {
public:
    AdminProvider();
    QByteArray getAllUserInfo();
};

#endif // ADMINPROVIDER_H
