#include <QDebug>
#include <QTcpSocket>
#include <memory>
#include "Server.h"
#include "Settings.h"

Server::Server(QObject* parent) : QObject(parent)
{
    server_ = new QTcpServer();
}

void Server::start(int port)
{
    QObject::connect(server_, &QTcpServer::newConnection,
                     this, &Server::newConnection);

    if (!server_->listen(QHostAddress::Any, port))
    {
        qDebug() << "Server could not start.";
    }
    else
    {
        qDebug() << "Server started.";
    }
}

void Server::stop()
{
    server_->close();
}

void Server::newConnection()
{
    auto socket = server_->nextPendingConnection();

    QObject::connect(socket, &QTcpSocket::disconnected, this, [&] { delete socket; });

    socket->write("Hello client.\n");
}
