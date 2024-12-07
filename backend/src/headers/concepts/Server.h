#ifndef SERVER_H
#define SERVER_H

#include <QRegularExpression>
#include <QSqlDatabase>
#include <QTcpServer>
#include <QTcpSocket>
#include <QRunnable>

class Server : public QTcpServer {
    Q_OBJECT
public:
    Server(int port);
private:
    bool openDbConnections();
    std::shared_ptr<QSqlDatabase> getConnection();

    std::shared_ptr<QSqlDatabase> connection;
    QRegularExpression reqFormat;
public slots:
    void incomingConnection(qintptr socketDescriptor);
};

#endif // SERVER_H

