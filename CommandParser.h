#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <unordered_map>
#include <QTcpSocket>

#include "Emulator.h"

class CommandParser
{
public:
    std::unordered_map< char, std::function< void(QTcpSocket* socket_, QByteArray input)> > dict;

public:
    void createDictOfCommands(Emulator* emulator);

private:
    Emulator* emulator_;

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
