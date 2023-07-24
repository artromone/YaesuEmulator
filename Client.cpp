#include "Client.h"

#include "Settings.h"

#include <QDebug>

Client::Client(QTcpSocket* socket, Emulator* emulator, QObject* parent)
    : QObject(parent), socket_(socket), emulator_(emulator)
{
    QObject::connect(socket_, &QTcpSocket::connected, this, &Client::onConnected);
    QObject::connect(socket_, &QTcpSocket::disconnected, this, &Client::onDisconnected);
    QObject::connect(socket_, &QTcpSocket::readyRead, this, &Client::onReadyRead);
}

// Client::Client(QObject *parent): QObject(parent)
//{
//   Settings settings;
//   socket_ = new QTcpSocket();

//  QObject::connect(socket_, &QTcpSocket::connected, this, &Client::onConnected);
//  QObject::connect(socket_, &QTcpSocket::disconnected, this, &Client::onDisconnected);
//  QObject::connect(socket_, &QTcpSocket::readyRead, this, &Client::onReadyRead);

//  socket_->connectToHost(settings.address, settings.port);

//  if (!socket_->waitForConnected(1000))
//  {
//      qDebug() << "Error: " << socket_->errorString();
//  }
//  else
//  {
//      qDebug() << "Test.";
//      socket_->write("Test.");
//  }
//}

void Client::onConnected()
{
    qDebug() << "Client connected.";
    // socket_->write("Client connected.");
}

void Client::onDisconnected()
{
    qDebug() << "Disconnected.";
}

void Client::onReadyRead()
{
    qDebug() << "Reading data:";
    QByteArray data = socket_->readAll();
    qDebug() << data;
    socket_->waitForBytesWritten(1000);
}
