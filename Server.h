#ifndef YAESUEMULATOR_QTCP_SERVER_H
#define YAESUEMULATOR_QTCP_SERVER_H

#include "Types.h"

#include <QObject>
#include <QTcpServer>

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject* parent = Q_NULLPTR);

    void start(int port);
    void stop();

    bool isStarted() const;
    ServerState::State state() const;

signals:
    void newClient(QTcpSocket* socket);
    void stateChanged(ServerState::State state);

private slots: // никак не связано с внешним миром
    void onNewConnection();

private:
    void changeState(ServerState::State state);

private:
    QTcpServer* server_;
    ServerState::State state_ {ServerState::State::S_UNDEFINED};
};

#endif
