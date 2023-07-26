#ifndef YAESUEMULATOR_QTCP_SERVER_H
#define YAESUEMULATOR_QTCP_SERVER_H

#include <QObject>
#include <QTcpServer>

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject* parent = Q_NULLPTR);

    void start(int port);
    void stop();

signals:
    void onStart(QTcpSocket* socket);
    void newClient(QTcpSocket* socket);

public slots:
    void newConnection();

private:
    QTcpServer* server_;
};
#endif
