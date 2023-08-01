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

    AntennaStatus::Status state() const;

    AntennaState antennaState() const;
    void setAntennaState(const AntennaState &antennaState);

signals:
    void stateChanged(AntennaStatus::Status state);
    void coordsChanged(AntennaState state);

private:
    void changeState(AntennaStatus::Status state);
    void changeCoords(AntennaState state);

private:
    AntennaState antennaState_;
    AntennaStatus::Status state_{AntennaStatus::Status::S_READY};

    int testStateTimerId_{0};

protected:
    void timerEvent(QTimerEvent *event);
};
// Обновить настройки при закрытии приложения
#endif
