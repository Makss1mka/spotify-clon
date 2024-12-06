#include "../headers/utils/EnvFile.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QString>

Env::Env() {}

QString Env::get(const QString& key) {
    QString envFilePath = "C:/Users/maksi/Desktop/PopuskPapka/C++/KuRsAcH/backend/.env";

    QFile file(envFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open env file with path: " << envFilePath;
        return "";
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.startsWith(key + "=")) {
            QString value = line.mid(key.length() + 1);
            return value;
        }
    }

    return "";
}
