#ifndef EMULATOR_H
#define EMULATOR_H

#include <utility>

#include "Types.h"
#include "AntennaState.h"

class Emulator : public QObject
{
    Q_OBJECT

public:
    Emulator();

    AntennaStatus::Status status() const;

    const AntennaState &antennaState() const;
//    void setAntennaState(const AntennaState &antennaState);

signals:
    void statusChanged(AntennaStatus::Status status);
    void coordsChanged(AntennaState status);

private:
    void changeStatus(AntennaStatus::Status status);
    void changeCoords(int azCurrent, int elCurrent, int azTarget, int elTarget);

private:
    AntennaState antennaState_;
    //Coordinate{az,el} current_;
    //Coordinate target_;

    AntennaStatus::Status antennaStatus_{AntennaStatus::Status::S_READY};

    int testStateTimerId_{0};

protected:
    void timerEvent(QTimerEvent *event);
};
// Обновить настройки при закрытии приложения
#endif
