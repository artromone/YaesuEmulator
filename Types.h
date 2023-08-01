#ifndef TYPES_H
#define TYPES_H

#include <QObject>
#include <QQmlEngine>

class ServerState : public QObject
{
    Q_OBJECT

public:
    enum State
    {
        S_UNDEFINED, // дефолтное состоянии при запуске приложения
        S_CONNECTED,    // успех при подключении
        S_DISCONNECTED, // отключился
        S_PORT_BUSY     // порт занят
    };
    Q_ENUMS(State)

public:
    ServerState() : QObject() { }

    static void registerType()
    {
        qmlRegisterType<ServerState>("YaesuEmulator", 1, 0, "ServerState");
    }
};

// NOTE для того, чтоб можно было пользоваться внутри метаобъектной системы
Q_DECLARE_METATYPE(ServerState::State);

#endif // TYPES_H
