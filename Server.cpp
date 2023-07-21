#include "Server.h"
#include <QTcpSocket>
#include <QDebug>
#include <memory>
#include "Settings.h"

TcpServer::TcpServer(QObject *parent): QObject(parent)
{
  Settings * settings = new Settings();
  server_ = new QTcpServer();

  QObject::connect(server_, &QTcpServer::newConnection,
                   this, &TcpServer::newConnection);

  if (server_->listen(settings->address, settings->port))
  {
    qDebug() << "Server started.";
  }
  else
  {
    qDebug() << "Server could not start.";
  }
}

void TcpServer::newConnection()
{
  auto socket = std::make_shared<QTcpSocket>(server_->nextPendingConnection());
  qDebug() << "Hello client.";
  socket->write("Hello client.");
  //socket->flush();
  socket->waitForBytesWritten(3000);
}
