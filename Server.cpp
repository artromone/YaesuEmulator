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
    qDebug() << "start server on port:" << port;

    QObject::connect(server_, &QTcpServer::newConnection, this, &Server::newConnection);

    if (!server_->listen(QHostAddress::Any, port))
    {
        qDebug() << "Server could not start:" << server_->errorString();
        emit this->stateChanged(false);
    }
    else
    {
        qDebug() << "Server started.";
        emit this->stateChanged(true);
    }
}

void Server::stop()
{
    server_->close();
    emit this->stateChanged(false);
}

bool Server::isStarted() const
{
    return server_->isListening();
}

void Server::newConnection()
{
    qDebug() << "New connection to server.";
    auto socket = server_->nextPendingConnection();

    emit this->newClient(socket);
}
