#ifndef ENVFILE_H
#define ENVFILE_H

#include <QString>

class Env {
public:
    static QString get(const QString& key);
    static void set(const QString& key, const QString& value);

    Env(const Env&) = delete;
    void operator=(const Env&) = delete;
private:
    Env();
};

#endif // ENVFILE_H
