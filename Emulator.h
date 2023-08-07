#ifndef EMULATOR_H
#define EMULATOR_H

#include <utility>

#include <QTcpSocket>

#include "Types.h"
#include "AntennaState.h"
#include "Settings.h"

enum class Diraction
{
    D_Left,
    D_Right,
    D_UP,
    D_Down
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

protected:
    void timerEvent(QTimerEvent *event);

private:
    void setStatus(AntennaStatus::Status status);

private:
    AntennaState antennaState_;
    int testStateTimerId_{0};
};
#endif
