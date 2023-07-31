#include "Server.h"

#include "Application.h"
#include "Client.h"
#include "Settings.h"

#include <QDebug>
#include <QTcpSocket>

#include <memory>

Server::Server(QObject* parent):
    QObject(parent),
    server_(new QTcpServer()),
    isOk_(true)
{}

void Server::start(int port)
{
    qDebug() << "Attempt to start server on port:" << port;

    QObject::connect(server_, &QTcpServer::newConnection, this, &Server::newConnection);

    if (!server_->listen(QHostAddress::Any, port))
    {
        qDebug() << "Server could not start:" << server_->errorString();
        isOk_ = false;
        emit this->okChanged(isOk_);
        emit this->stateChanged(false);
    }
    else
    {
        qDebug() << "Server started.";
        isOk_ = true;
        emit this->okChanged(isOk_);
        emit this->stateChanged(true);
    }
}

void Server::stop()
{
    qDebug() << "Server stopped.";

    server_->close();
    emit this->stateChanged(false);
}

bool Server::isStarted() const
{
    return server_->isListening();
}

bool Server::isOk() const
{
    return isOk_;
}

void Server::newConnection()
{
    auto socket = server_->nextPendingConnection();
    qDebug() << "New connection to server from" << socket->peerAddress();

    emit this->newClient(socket);
}
