#include <QFile>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QTcpSocket>
#include "../headers/concepts/Server.h"
#include "../headers/concepts/Request.h"
#include "../headers/concepts/RouterDispatcher.h"
#include "../headers/adminModule/AdminRouter.h"
#include "../headers/authModule/AuthRouter.h"
#include "../headers/musicModule/MusicRouter.h"
#include "../headers/utils/envFile.h"

Server::Server(int port) {
    if(this->listen(QHostAddress::Any, port)) {
        qDebug() << "Server started on " << port << " port";
    } else {
        qWarning() << "Server starting error";
        exit(1);
    }

    if(!Server::openDbConnections()) throw "Cannot open DB connections";
    RouterDispatcher::getDispatcher().addRouter(std::make_shared<AdminRouter>());
    RouterDispatcher::getDispatcher().addRouter(std::make_shared<AuthRouter>());
    RouterDispatcher::getDispatcher().addRouter(std::make_shared<MusicRouter>());
}

bool Server::openDbConnections() {
    connection = std::make_shared<QSqlDatabase>(QSqlDatabase::addDatabase("QSQLITE"));
    connection->setDatabaseName(env::get("USERS_INFO_DB", ":/.env"));

    if(!connection->open()) {
        qDebug() << "Cannot connect to database, db path: " << env::get("USERS_INFO_DB", ":/.env") << connection->lastError().text();
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
