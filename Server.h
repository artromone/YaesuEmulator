#ifndef YAESUEMULATOR_QTCP_SERVER_H
#define YAESUEMULATOR_QTCP_SERVER_H

#include <QObject>
#include <QTcpServer>

class Server: public QObject
{
public:
  explicit Server(QObject *parent = Q_NULLPTR);

public slots:
  void newConnection();

private:
  QTcpServer *server_;
};
#endif
//Список подключенных клиентов
