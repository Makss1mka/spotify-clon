#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include "../headers/concepts/Server.h"
#include "../headers/concepts/Request.h"
#include "../headers/concepts/RouterDispatcher.h"
#include "../headers/adminModule/AdminRouter.h"

#include "../headers/utils/envFile.h"

Server::Server(int port) {
    if(this->listen(QHostAddress::Any, port)) {
        qDebug() << "Server started on " << port << " port";
    } else {
        qWarning() << "Server starting error";
        exit(1);
    }

    RouterDispatcher::getDispatcher().addRouter(AdminRouter());
}

void Server::incomingConnection(qintptr socketDescriptor) {
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    qDebug() << "Client has connected" << socketDescriptor;
}

void Server::slotReadyRead() {
    QByteArray request = socket->readAll();
    qDebug() << "Request" << request;

    Request req = Request::parseFromQByteArray(request);

    QByteArray response = RouterDispatcher::getDispatcher().routing(req);

    socket->write(response);
    socket->flush();
}


// void Server::sendToClient(QString str) {
//     Data.clear();
//     QDataStream out(&Data, QIODevice::WriteOnly);
//     out.setVersion(QDataStream::Qt_6_7);
//     out << str;
//     socket->write(Data);
// }

// if (request.contains("GET /get ")) {
//
// } else if(request.contains("GET /getBilly ")) {
//     QFile file("../../../assets/billy.jpg");
//     if(file.exists()) qDebug() << "Penis";
//     if(file.open(QIODevice::ReadOnly)) {
//         QByteArray fileContent = file.readAll();
//         file.close();

//         response = "HTTP/1.1 200 OK\r\n"
//                    "Content-Type: image/jpeg\r\n"
//                    "Content-Length: " + QByteArray::number(fileContent.size()) + "\r\n"
//                                                               "\r\n";
//         response.append(fileContent);

//         //qDebug() << fileContent;
//     } else {
//         response = "HTTP/1.1 404 Not Found\r\n"
//                    "Content-Type: text/plain\r\n"
//                    "Content-Length: 16\r\n"
//                    "\r\n"
//                    "Cannot send file";
//         qWarning() << "Cannot send file";
//     }
// } else {
//     response = "HTTP/1.1 404 Not Found\r\n"
//                "Content-Type: text/plain\r\n"
//                "Content-Length: 9\r\n"
//                "\r\n"
//                "Not Found";
// }
