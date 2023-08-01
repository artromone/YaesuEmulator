#ifndef WIDGET_H
#define WIDGET_H

#include "Emulator.h"
#include "Server.h"
#include "Settings.h"

#include <QColor>
#include <QObject>

class QQmlContext;

class Widget : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString logMsg READ logMsg)
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(ServerStatus::Status serverState READ serverState NOTIFY serverStateChanged)
    Q_PROPERTY(QPair<QPair<int,int>, QPair<int,int>> antennaCoords
               READ antennaCoords /*WRITE setAntennaCoords*/ NOTIFY antennaCoordsChanged)
    Q_PROPERTY(AntennaStatus::Status antennaState READ antennaState /*WRITE setAntennaState*/ NOTIFY antennaStateChanged)

public:
    explicit Widget(QQmlContext& context,
                    Server* server,
                    Emulator* emulator,
                    QObject* parent = Q_NULLPTR);

    Q_INVOKABLE QColor color() const;
    Q_INVOKABLE void changeServerState(bool state);
    Q_INVOKABLE const QString antennaStateString(AntennaStatus::Status state) const;

    QString logMsg() const;
    int port() const;
    QPair<QPair<int,int>, QPair<int,int>> antennaCoords() const;
    ServerStatus::Status serverState() const;
    AntennaStatus::Status antennaState() const;

    void setPort(int value);

signals:
    void logMessage(const QString& msg);
    void portChanged();
    void antennaCoordsChanged();
    void serverStateChanged();
    void antennaStateChanged();

private:
    void init();
    void sendLogMessage(const QString& message);

private:
    Server* const server_;
    Emulator* emulator_;
};

#endif
