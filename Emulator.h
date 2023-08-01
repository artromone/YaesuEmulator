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

    AntennaState antennaState() const;
    void setAntennaState(const AntennaState &antennaState);

signals:
    void statusChanged(AntennaStatus::Status status);
    void coordsChanged(AntennaState status);

private:
    void changeStatus(AntennaStatus::Status status);
    void changeCoords(AntennaState state);

private:
    AntennaState antennaState_;
    AntennaStatus::Status antennaStatus_{AntennaStatus::Status::S_READY};

    int testStateTimerId_{0};

protected:
    void timerEvent(QTimerEvent *event);
};
// Обновить настройки при закрытии приложения
#endif
