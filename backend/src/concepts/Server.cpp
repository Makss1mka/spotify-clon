#include "../headers/concepts/RouterDispatcher.h"
#include "../headers/musicModule/MusicRouter.h"
#include "../headers/adminModule/AdminRouter.h"
#include "../headers/userModule/UserRouter.h"
#include "../headers/concepts/Request.h"
#include "../headers/concepts/Server.h"
#include "../headers/utils/EnvFile.h"
#include "../headers/utils/Map.h"
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QByteArray>
#include <QTcpSocket>
#include <QSqlError>
#include <QFile>

Server::Server(int port) {
    if(this->listen(QHostAddress::Any, port)) {
        qDebug() << "Server started on " << port << " port";
    } else {
        qWarning() << "Server starting error";
        exit(1);
    }

    if(!Server::openDbConnections()) throw "Cannot open DB connections";
    RouterDispatcher::getDispatcher().addRouter(std::make_shared<AdminRouter>());
    RouterDispatcher::getDispatcher().addRouter(std::make_shared<UserRouter>());
    RouterDispatcher::getDispatcher().addRouter(std::make_shared<MusicRouter>());
}

bool Server::openDbConnections() {
    connection = std::make_shared<QSqlDatabase>(QSqlDatabase::addDatabase("QSQLITE"));
    connection->setDatabaseName(Env::get("USERS_INFO_DB"));

    if(!connection->open()) {
        qDebug() << "Cannot connect to database, db path: " << Env::get("USERS_INFO_DB") << connection->lastError().text();
        return false;
    }
    return true;
}

void Server::incomingConnection(qintptr socketDescriptor) {
    QTcpSocket* socket = new QTcpSocket();
    qDebug() << "Client has connected" << socketDescriptor;

    if(socket->setSocketDescriptor(socketDescriptor)) {
        connect(socket, &QTcpSocket::readyRead, [socket](){
            QByteArray newData = socket->readAll();
            Request req;

            qDebug() << "\nRequest" << newData;

            req.parseFromQByteArrayWithoutBodyParsing(newData);
            req.parseBody();

            QByteArray response = RouterDispatcher::getDispatcher().routing(req);
            req.clear();

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
