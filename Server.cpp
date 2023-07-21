#include "Server.h"

#include "Settings.h"

#include <QDebug>
#include <QTcpSocket>

#include <memory>

TcpServer::TcpServer(QObject* parent) : QObject(parent)
{
    Settings* settings = new Settings();
    server_ = new QTcpServer();

    QObject::connect(server_, &QTcpServer::newConnection, this, &TcpServer::newConnection);

    if (!server_->listen(settings->address, settings->port))
    {
        qDebug() << "Server could not start.";
    }
    else
    {
        qDebug() << "Server started.";
    }
}

void TcpServer::newConnection()
{
    auto socket = server_->nextPendingConnection();

    QObject::connect(socket, &QTcpSocket::disconnected, this, [&] { delete socket; });

    socket->write("Hello client.\n");
    //    socket->flush();
    //    socket->waitForBytesWritten(3000);
    //    socket->close();
}
