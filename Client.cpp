#include "Client.h"

#include "Settings.h"
#include "Utils.h"

#include <QDebug>

Client::Client(QTcpSocket* socket, Emulator* emulator, QObject* parent)
    : QObject(parent), socket_(socket), emulator_(emulator)
{
    QObject::connect(socket_, &QTcpSocket::connected, this, &Client::onConnected);
    QObject::connect(socket_, &QTcpSocket::disconnected, this, &Client::onDisconnected);
    QObject::connect(socket_, &QTcpSocket::readyRead, this, &Client::onReadyRead);
}

void Client::onConnected()
{
    qDebug() << "Client connected.";
}

void Client::onDisconnected()
{
    qDebug() << "Disconnected.";
}

void Client::onReadyRead()
{
    QByteArray data = socket_->readAll();
    qDebug() << "Read data:" << data;
    socket_->write(qIntToByte(qByteToInt(data) + 1));
    socket_->waitForBytesWritten(1000);
}
