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

    AntennaStatus::Status status() const;

    const AntennaState &antennaState() const;
    AntennaState &getModifiableAntennaState();

    void changeAz(QTcpSocket *socket, QByteArray input, int targetAz);
    void changeEl(QTcpSocket *socket, QByteArray input, int targetEl);

public:
    std::atomic<bool> moveAzPossible_{true};
    std::atomic<bool> moveElPossible_{true};

signals:
    void statusChanged(AntennaStatus::Status status);
    void coordsChanged(AntennaState status);

private:
    void changeStatus(AntennaStatus::Status status);
    void changeCoords(int azCurrent, int elCurrent, int azTarget, int elTarget);

    // void changeAzImpl(QTcpSocket *socket, QByteArray input, int targetAz);

private:
    AntennaState antennaState_;
    AntennaStatus::Status antennaStatus_{AntennaStatus::Status::S_READY};
    // int testStateTimerId_{0};

protected:
    void timerEvent(QTimerEvent *event);
};
// Обновить настройки при закрытии приложения
#endif
