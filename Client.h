#ifndef YAESUEMULATOR_QTCP_CLIENT_H
#define YAESUEMULATOR_QTCP_CLIENT_H

#include "Emulator.h"

#include <QObject>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    Client(QTcpSocket* socket, Emulator* emulator, QObject* parent = Q_NULLPTR);
    ~Client() override;

    QTcpSocket* socket() const { return socket_; }

    int id() const { return id_; }

public slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();

signals:
    void disconnected();

private:
    QTcpSocket* socket_;
    Emulator* emulator_;
    const int id_;
};

#endif // CLIENT_H
