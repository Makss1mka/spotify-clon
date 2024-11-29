#include <QFile>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QTcpSocket>
#include "../headers/utils/Map.h"
#include "../headers/concepts/Server.h"
#include "../headers/concepts/Request.h"
#include "../headers/concepts/RouterDispatcher.h"
#include "../headers/adminModule/AdminRouter.h"
#include "../headers/userModule/UserRouter.h"
#include "../headers/musicModule/MusicRouter.h"
#include "../headers/utils/EnvFile.h"

#include <QString>

Server::Server(int port) {
    if(this->listen(QHostAddress::Any, port)) {
        qDebug() << "Server started on " << port << " port";
    } else {
        qWarning() << "Server starting error";
        exit(1);
    }

    // -----------------------------------
    // Map<QString, QString> map;
    // map.set("key1", "value1");
    // map.set("key2", "anotherValue2");
    // map.set("keychik3", "EPvalue3");
    // map.set("key4ik4", "SUIvalue4");
    // map.set("keey5", "value5");
    // Map<QString, QString>::ConstRevrseIterator iter = map.constReverseBegin();
    // qDebug() << " AAA - " << (*(++iter)).key << " - " << (*iter).value;
    // qDebug() << "item - " << (*(++iter)).key << " - " << (*(iter)).value;
    // qDebug() << "item - " << (*(++iter)).key << " - " << (*(iter)).value;
    // -----------------------------------


    if(!Server::openDbConnections()) throw "Cannot open DB connections";
    RouterDispatcher::getDispatcher().addRouter(std::make_shared<AdminRouter>());
    RouterDispatcher::getDispatcher().addRouter(std::make_shared<UserRouter>());
    RouterDispatcher::getDispatcher().addRouter(std::make_shared<MusicRouter>());
}

bool Server::openDbConnections() {
    connection = std::make_shared<QSqlDatabase>(QSqlDatabase::addDatabase("QSQLITE"));
    connection->setDatabaseName(Env::get("USERS_INFO_DB", ":/.env"));

    if(!connection->open()) {
        qDebug() << "Cannot connect to database, db path: " << Env::get("USERS_INFO_DB", ":/.env") << connection->lastError().text();
        return false;
    }
    return true;
}

void Server::incomingConnection(qintptr socketDescriptor) {
    QTcpSocket* socket = new QTcpSocket();
    qDebug() << "Client has connected" << socketDescriptor;

    if(socket->setSocketDescriptor(socketDescriptor)) {
        connect(socket, &QTcpSocket::readyRead, [socket](){
            QByteArray request = socket->readAll();
            qDebug() << "Request" << request;

            Request req = Request::parseFromQByteArray(request);

            QByteArray response = RouterDispatcher::getDispatcher().routing(req);

            socket->write(response);
            socket->flush();
        });
        connect(socket, &QTcpSocket::disconnected, [socket](){
            socket->deleteLater();
        });
    } else {
        qDebug() << "Cannot connect user " << socketDescriptor;
    }
}
