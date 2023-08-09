#ifndef TYPES_H
#define TYPES_H

#include <QObject>
#include <QQmlEngine>

class ServerStatus : public QObject
{
    Q_OBJECT

public:
    enum Status
    {
        S_UNDEFINED,
        S_CONNECTED,
        S_DISCONNECTED,
        S_PORT_BUSY
    };
    Q_ENUMS(Status)

public:
    ServerStatus() : QObject() {}

    static void registerType()
    {
        qmlRegisterType<ServerStatus>("YaesuEmulator", 1, 0, "ServerState");
    }
};

class AntennaStatus : public QObject
{
    Q_OBJECT

public:
    enum Status
    {
        S_READY,
        S_MOVETO,
        S_MANUAL
    };
    Q_ENUMS(Status)

public:
    AntennaStatus() : QObject() {}

    static const QString text(Status status) {
        if (S_READY == status) return tr("Готова");
        if (S_MOVETO== status) return tr("Выход в точку");
        if (S_MANUAL== status) return tr("Ручное");
        return tr("Неизвестно");
    }

    static void registerType()
    {
        qmlRegisterType<AntennaStatus>("YaesuEmulator", 1, 0, "AntennaStatus");
    }
};

Q_DECLARE_METATYPE(ServerStatus::Status)
Q_DECLARE_METATYPE(AntennaStatus::Status)

#endif
