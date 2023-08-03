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
    void sendState(QTcpSocket* socket_);
    void setPos(QTcpSocket* socket_, QByteArray input);
    void setAzSpeed(QTcpSocket* socket_, QByteArray input);
};

#endif
