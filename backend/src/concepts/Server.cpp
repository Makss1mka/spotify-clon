#include "../headers/concepts/RouterDispatcher.h"
#include "../headers/musicModule/MusicRouter.h"
#include "../headers/adminModule/AdminRouter.h"
#include "../headers/userModule/UserRouter.h"
#include "../headers/concepts/Request.h"
#include "../headers/concepts/Server.h"
#include "../headers/utils/EnvFile.h"
#include "../headers/utils/Map.h"
#include <QRegularExpression>
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
    //
    this->reqFormat = QRegularExpression("^(PUT|POST|DELETE|GET) \/.* HTTP\/1\.1\r\n.|\n|\r*");

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
    std::vector<Request>* waitingReqs = new std::vector<Request>;
    qDebug() << "Client has connected" << socketDescriptor;

    if(socket->setSocketDescriptor(socketDescriptor)) {
        connect(socket, &QTcpSocket::readyRead, [this, waitingReqs, socket](){
            QByteArray newData = socket->readAll();
            qDebug() << "\nRequest" << newData.mid(0, 500) << " LEN " << newData.size();

            if (this->reqFormat.match(newData).hasMatch() == false) {
                socket->write("HTTP/1.1 400 Bad Request\r\n"
                        "Content-Type: text/plain\r\n"
                        "Content-Length: 24\r\n"
                        "\r\n"
                        "Incorrect request format");
                socket->flush();
                return;
            }

            Request req;
            req.parseFromQByteArrayWithoutBodyParsing(newData);

            try {
                if(req.headers.get("content-length").toInt() != req.bodyNoneJson.size()) {
                    bool isFound = false;
                    for(int i = 0; i < waitingReqs->size(); i++) {
                        if((*waitingReqs)[i].headers.get("x-request-id") == req.headers.get("x-request-id") && (*waitingReqs)[i].isBodyNoneJson == true
                            && req.isBodyNoneJson == true) {
                            (*waitingReqs)[i].bodyNoneJson += req.bodyNoneJson;

                            if ((*waitingReqs)[i].headers.get("content-length").toInt() == (*waitingReqs)[i].bodyNoneJson.size()) {
                                (*waitingReqs)[i].parseBody();

                                QByteArray response = RouterDispatcher::getDispatcher().routing((*waitingReqs)[i]);
                                socket->write(response);
                                socket->flush();

                                waitingReqs->erase(waitingReqs->begin() + i);
                            } else {
                                socket->write("HTTP/1.1 200 OK\r\n"
                                        "Content-Type: text/plain\r\n"
                                        "\r\n");
                                socket->flush();
                            }

                            isFound = true;
                            break;
                        }
                    }

                    if (isFound == false) {
                        waitingReqs->push_back(req);
                        socket->write("HTTP/1.1 200 OK\r\n"
                                "Content-Type: text/plain\r\n"
                                "\r\n");
                        socket->flush();
                    }
                } else {
                    if(req.isBodyJsonArray || req.isBodyJsonObj || req.isBodyNoneJson) req.parseBody();

                    QByteArray response = RouterDispatcher::getDispatcher().routing(req);
                    socket->write(response);
                    socket->flush();
                }
            } catch (...) {
                if(req.isBodyJsonArray || req.isBodyJsonObj || req.isBodyNoneJson) req.parseBody();

                QByteArray response = RouterDispatcher::getDispatcher().routing(req);
                socket->write(response);
                socket->flush();
            }
        });
        connect(socket, &QTcpSocket::disconnected, [waitingReqs, socket](){
            delete waitingReqs;
            socket->deleteLater();
        });
    } else {
        qDebug() << "Cannot connect user " << socketDescriptor;
    }
}
