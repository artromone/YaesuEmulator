#include "Server.h"

#include "Application.h"
#include "Client.h"
#include "Settings.h"

#include <QDebug>
#include <QTcpSocket>

#include <memory>

Server::Server(QObject* parent) : QObject(parent)
{
    server_ = new QTcpServer();
}

void Server::start(int port)
{
    QObject::connect(server_, &QTcpServer::newConnection, this, &Server::newConnection);

    if (!server_->listen(QHostAddress::Any, port))
    {
        qDebug() << "Server could not start:" << server_->errorString();
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
    qDebug() << "New connection to server.";
    auto socket = server_->nextPendingConnection();

    emit this->newClient(socket);
}
