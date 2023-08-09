#ifndef YAESUEMULATOR_QTCP_SERVER_H
#define YAESUEMULATOR_QTCP_SERVER_H

#include <QObject>
#include <QTcpServer>

#include "Types.h"

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject* parent = Q_NULLPTR);

    void start(int port);
    void stop();

    bool isStarted() const;
    ServerStatus::Status state() const;

signals:
    void newClient(QTcpSocket* socket);
    void stateChanged(ServerStatus::Status state);

private slots:
    void onNewConnection();

private:
    void changeState(ServerStatus::Status state);

private:
    QTcpServer* server_;
    ServerStatus::Status state_ {ServerStatus::Status::S_UNDEFINED};
};

#endif
