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
  auto socket = std::make_shared<QTcpSocket>(server_->nextPendingConnection());
  socket->write("Hello client.\n");
  socket->flush();
  socket->waitForBytesWritten(3000);
  socket->close();
}
