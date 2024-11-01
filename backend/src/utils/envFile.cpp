#include "../headers/utils/envFile.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QString>

QString env::get(QString key, QString envFilePath) {
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
