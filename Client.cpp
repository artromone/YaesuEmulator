#include "Client.h"

#include "Settings.h"

#include <QDebug>

static int COUNTER = 0;

Client::Client(QTcpSocket* socket, Emulator* emulator, QObject* parent)
    : QObject(parent), socket_(socket), emulator_(emulator), id_(COUNTER++)
{
    QObject::connect(socket_, &QTcpSocket::connected, this, &Client::onConnected);
    QObject::connect(socket_, &QTcpSocket::disconnected, this, &Client::onDisconnected);
    QObject::connect(socket_, &QTcpSocket::readyRead, this, &Client::onReadyRead);
}

Client::~Client()
{
    qDebug() << "~Client";
}

void Client::onConnected()
{
    qDebug() << "Client connected.";
}

void Client::onDisconnected()
{
    qDebug() << "Disconnected.";

    emit this->disconnected();
    //    emit this->disconnected(id_);
}

void Client::onReadyRead()
{
    QByteArray data = socket_->readAll();
    qDebug() << "Read data:" << data;
    QByteArray newData = QByteArray::fromStdString(std::to_string(data.toInt() + 1));
    socket_->write(newData);
    qDebug() << "Sent data:" << newData;
}
