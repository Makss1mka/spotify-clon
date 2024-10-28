#ifndef ENVFILE_H
#define ENVFILE_H

#include <QString>

namespace env {

QString get(QString key, QString envFilePath);

}

#endif // ENVFILE_H
