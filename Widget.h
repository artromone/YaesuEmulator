#ifndef WIDGET_H
#define WIDGET_H

#include <QColor>
#include <QObject>
#include <QQmlContext>

#include "Emulator.h"
#include "Server.h"
#include "Settings.h"
#include "AntennaState.h"

class Widget : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(ServerStatus::Status serverState READ serverState NOTIFY serverStateChanged)
    Q_PROPERTY(AntennaStatus::Status antennaStatus READ antennaStatus NOTIFY antennaStateChanged)
    Q_PROPERTY(int az READ az NOTIFY antennaStateChanged)
    Q_PROPERTY(int el READ el NOTIFY antennaStateChanged)
    Q_PROPERTY(int targetAz READ targetAz NOTIFY antennaStateChanged)
    Q_PROPERTY(int targetEl READ targetEl NOTIFY antennaStateChanged)
    Q_PROPERTY(bool autoConnect READ autoConnect CONSTANT)
    Q_PROPERTY(bool tunnelLocked WRITE setTunnelLocked CONSTANT)

public:
    explicit Widget(QQmlContext& context,
                    Server* server,
                    Emulator* emulator,
                    QObject* parent = Q_NULLPTR);

    Q_INVOKABLE void changeServerState(bool state);
    Q_INVOKABLE const QString antennaStatusString(AntennaStatus::Status status) const;
    Q_INVOKABLE void changeAutoconectOption(bool autoconnect);
    Q_INVOKABLE void setTunnelLocked(bool value);

    int port() const;
    void setPort(int value);

    ServerStatus::Status serverState() const;

    AntennaStatus::Status antennaStatus() const;

    int az() const;
    int el() const;
    int targetAz() const;
    int targetEl() const;
    int autoConnect() const;

signals:
    void portChanged();

    void serverStateChanged();

    void emulatorChanged();
    void antennaStateChanged();

private:
    void init();
    void sendLogMessage(const QString& message, int logType);

private:
    Server* const server_;
    Emulator* const emulator_;
};

#endif
