#ifndef YAESUEMULATOR_QTCP_CLIENT_H
#define YAESUEMULATOR_QTCP_CLIENT_H

#include "Emulator.h"

#include <QObject>
#include <QTcpSocket>

class Client : public QObject
{
public:
    Client(QTcpSocket* socket, Emulator* emulator, QObject* parent = Q_NULLPTR);

public slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();

private:
    QTcpSocket* socket_; ///
    Emulator* emulator_;
};

#endif // CLIENT_H
