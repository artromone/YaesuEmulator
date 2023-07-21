#ifndef YAESUEMULATOR_QTCP_CLIENT_H
#define YAESUEMULATOR_QTCP_CLIENT_H

#include <QObject>
#include <QTcpSocket>

class TcpClient : public QObject
{
public:
    explicit TcpClient(QObject *parent = Q_NULLPTR);

public slots:
  void onConnected();
  void onDisconnected();
  void onReadyRead();

private:
  QTcpSocket *socket_;
};

#endif // CLIENT_H
