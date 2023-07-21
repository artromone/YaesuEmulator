#include "Client.h"
#include <QDebug>
#include "Settings.h"

TcpClient::TcpClient(QObject *parent): QObject(parent)
{
  Settings * settings = new Settings();
  socket_ = new QTcpSocket();

  QObject::connect(socket_, &QTcpSocket::connected, this, &TcpClient::onConnected);
  QObject::connect(socket_, &QTcpSocket::disconnected, this, &TcpClient::onDisconnected);
  QObject::connect(socket_, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);

  socket_->connectToHost(settings->address, settings->port);
  //socket_->open(QIODevice::ReadWrite);

  if (!socket_->waitForConnected(5000))
  {
      qDebug() << "Error: " << socket_->errorString();
  }
  else
  {
      qDebug() << "Test.";
      socket_->write("Test.");
  }
}

void TcpClient::onConnected()
{
    qDebug() << "Client connected.";
    socket_->write("I am client.");
}

void TcpClient::onDisconnected()
{
    qDebug() << "Disconnected.";
}

void TcpClient::onReadyRead()
{
    qDebug() << "Reading data.";
    QByteArray data = socket_->readAll();
    qDebug() << data;
    qDebug() << "Reading success.";
    socket_->write("Reading success.");
    socket_->waitForBytesWritten(1000);
}
