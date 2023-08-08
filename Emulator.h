#ifndef EMULATOR_H
#define EMULATOR_H

#include <utility>

#include <QTcpSocket>

#include "Types.h"
#include "AntennaState.h"
#include "Settings.h"

enum class Diraction
{
    D_LEFT,
    D_RIGHT,
    D_UP,
    D_DOWN
};

class Emulator : public QObject
{
    Q_OBJECT
public:
    Emulator();

    const AntennaState &anState() const;

    void updateCoords();

    void moveTo(int az, int el);
    void move(Diraction diraction);
    void stop();

    void setSpeed(int azSpeed, int elSpeed);

    bool isLockedTunnel() const;
    void setTunnelLocked(bool value);

protected:
    void timerEvent(QTimerEvent *event);

private:
    void setStatus(AntennaStatus::Status status);

private:
    AntennaState antennaState_;
    int testStateTimerId_{0};
    bool isLockedTunnel_{false};
};

#endif
