#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <unordered_map>
#include <QTcpSocket>

#include "Emulator.h"

class CommandParser
{
public:
    void createDictOfCommands(Emulator* emulator);
    std::unordered_map<char,
       std::function< void(QTcpSocket* socket_, QByteArray input)> > dict;
private:
    Emulator* emulator_;
//    std::atomic<bool> moveAzPossible_{true};
//    std::atomic<bool> moveElPossible_{true};
    void moveAzImpl(QTcpSocket *socket, QByteArray input, int targetAz);
    void moveElImpl(QTcpSocket *socket, QByteArray input, int targetEl);

private:
    void stop(QTcpSocket* socket, QByteArray input);
    void stopAz(QTcpSocket* socket, QByteArray input);
    void stopEl(QTcpSocket* socket, QByteArray input);
    void setPos(QTcpSocket* socket, QByteArray input);
    void moveUp(QTcpSocket* socket, QByteArray input);
    void moveDown(QTcpSocket* socket, QByteArray input);
    void moveLeft(QTcpSocket* socket, QByteArray input);
    void moveRight(QTcpSocket* socket, QByteArray input);
    void setAzSpeed(QTcpSocket* socket, QByteArray input);
    void sendState(QTcpSocket* socket);
};

#endif
