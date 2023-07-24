#ifndef YAESUEMULATOR_QTCP_CLIENT_H
#define YAESUEMULATOR_QTCP_CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include "Emulator.h"

class Client : public QObject
{
public:
    explicit Client(QObject *parent = Q_NULLPTR);

public slots:
  void onConnected();
  void onDisconnected();
  void onReadyRead();

private:
  QTcpSocket *socket_; ///
  Emulator emulator_;
};

#endif // CLIENT_H
