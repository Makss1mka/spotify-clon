#ifndef ENVFILE_H
#define ENVFILE_H

#include <QString>

class Env {
public:
    static QString get(QString key, QString envFilePath);

    Env(const Env&) = delete;
    void operator=(const Env&) = delete;
private:
    Env();
};

#endif // ENVFILE_H
