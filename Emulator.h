#ifndef EMULATOR_H
#define EMULATOR_H

#include <utility>

#include <QTcpSocket>

#include "Types.h"
#include "AntennaState.h"

class Emulator : public QObject
{
    Q_OBJECT

public:
    Emulator();

    const AntennaState &antennaState() const;
    AntennaState &antennaState();

    void updateCoords(int targetAz, int targetEl);

public:
    std::atomic<bool> moveAzPossible_{true};
    std::atomic<bool> moveElPossible_{true};

private:
    void setStatus(AntennaStatus::Status status);
    void setCoords(int azCurrent, int elCurrent, int azTarget, int elTarget);

    // void changeAzImpl(QTcpSocket *socket, QByteArray input, int targetAz);

private:
    AntennaState antennaState_;
    // int testStateTimerId_{0};

protected:
    void timerEvent(QTimerEvent *event);
};
// Обновить настройки при закрытии приложения
#endif
