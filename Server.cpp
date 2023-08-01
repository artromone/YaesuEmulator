#include "Server.h"

#include "Application.h"
#include "Client.h"
#include "Settings.h"

#include <QDebug>
#include <QTcpSocket>

#include <memory>

Server::Server(QObject* parent) : QObject(parent), server_(new QTcpServer())
{
}

void Server::start(int port)
{
    qDebug() << "Attempt to start server on port:" << port;

    QObject::connect(server_, &QTcpServer::newConnection, this, &Server::onNewConnection);

    if (!server_->listen(QHostAddress::Any, port))
    {
        qDebug() << "Server could not start:" << server_->errorString();
        this->changeState(ServerState::State::S_PORT_BUSY);
    }
    else
    {
        qDebug() << "Server started.";
        this->changeState(ServerState::State::S_CONNECTED);
    }
}

void Server::stop()
{
    qDebug() << "Server stopped.";

    server_->close();
    this->changeState(ServerState::State::S_DISCONNECTED);
}

bool Server::isStarted() const
{
    return server_->isListening();
}

ServerState::State Server::state() const
{
    return state_;
}

void Server::onNewConnection()
{
    auto socket = server_->nextPendingConnection();
    qDebug() << "New connection to server from" << socket->peerAddress();

    emit this->newClient(socket);
}

void Server::changeState(ServerState::State state)
{
    if (state_ != state)
    {
        qDebug() << "Server state changed" << state_ << "->" << state;

        state_ = state;
        emit this->stateChanged(state_);
    }
}
