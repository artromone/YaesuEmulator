#include "Client.h"
#include <QDebug>
#include "Settings.h"

TcpClient::TcpClient(QObject *parent): QObject(parent)
{
  Settings * settings = new Settings();
  socket_ = new QTcpSocket();

  socket_->connectToHost(settings->address, settings->port);

  QObject::connect(socket_, &QTcpSocket::readyRead,
                   this, &TcpClient::onReadyRead);
}

void TcpClient::onReadyRead()
{
    QByteArray data = socket_->readAll();
    qDebug() << data;
    socket_->write("OK!\n");
}
