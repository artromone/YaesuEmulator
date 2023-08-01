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
        S_UNDEFINED,    // дефолтное состоянии при запуске приложения
        S_CONNECTED,    // успех при подключении
        S_DISCONNECTED, // отключился
        S_PORT_BUSY     // порт занят
    };
    Q_ENUMS(State)

public:
    ServerState() : QObject() {}

    static void registerType()
    {
        qmlRegisterType<ServerState>("YaesuEmulator", 1, 0, "ServerState");
    }
};

class AntennaState : public QObject
{
    Q_OBJECT

public:
    enum State
    {
        S_READY,
        S_MOVETO,
        S_MANUAL
    };
    Q_ENUMS(State)

public:
    AntennaState() : QObject() {}

    static const QString text(State state) {
        if (S_READY == state) return tr("Готова");
        if (S_MOVETO== state) return tr("Выход в точку");
        if (S_MANUAL== state) return tr("Ручное");
        return tr("Неизвестно");
    }

    static void registerType()
    {
        qmlRegisterType<AntennaState>("YaesuEmulator", 1, 0, "AntennaState");
    }
};

// NOTE для того, чтоб можно было пользоваться внутри метаобъектной системы
Q_DECLARE_METATYPE(ServerState::State)
Q_DECLARE_METATYPE(AntennaState::State)

#endif
