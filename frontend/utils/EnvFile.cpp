#include "../headers/utils/envFile.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QString>

Env::Env() {}

QString Env::get(const QString& key) {
    QFile file("C:/Users/maksi/Desktop/PopuskPapka/C++/KuRsAcH/frontend/.env");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open env file with path: " << "C:/Users/maksi/Desktop/PopuskPapka/C++/KuRsAcH/frontend/.env";
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

void Env::set(const QString& key, const QString& value) {
    std::map<QString, QString> envMap;

    QFile file("C:/Users/maksi/Desktop/PopuskPapka/C++/KuRsAcH/frontend/.env");

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Cannot open env file with path: " << "C:/Users/maksi/Desktop/PopuskPapka/C++/KuRsAcH/frontend/.env";
        return;
    }

    QTextStream in(&file);
    //QList<QList<QString>> lines;

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.contains("=")) {
            QList<QString> keyValue = line.split("=");
            if(keyValue.size() == 2) {
                envMap[keyValue[0]] = keyValue[1];
            }
        }
    }

    envMap[key] = value;

    file.resize(0);
    QTextStream out(&file);

    for(const auto& pair : envMap) {
        out << pair.first << "=" << pair.second << "\n";
    }

    file.close();
}
