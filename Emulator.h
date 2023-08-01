#ifndef EMULATOR_H
#define EMULATOR_H

#include <utility>

#include "Types.h"

class Emulator : public QObject
{
    Q_OBJECT

public:
    Emulator();

//    int getAzCurrent() const;
//    int getElCurrent() const;

//    int getAzTarget() const;
//    int getElTarget() const;

    int getSpeedAz() const;
    int getSpeedEl() const;

    AntennaState::State state() const;

signals:
    void stateChanged(AntennaState::State state);
    void coordsChanged(QPair<QPair<int,int>, QPair<int,int>> state);

private:
    void changeState(AntennaState::State state);
    void changeCoords(QPair<QPair<int,int>, QPair<int,int>> state);

private:
//    int azCurrent_;
//    int elCurrent_;
//    int azTarget_;
//    int elTarget_;
    QPair<int,int> currCoords_;
    QPair<int,int> targetCoords_;
    int speedAz_;
    int speedEl_;
    AntennaState::State state_{AntennaState::State::S_READY};

    int testStateTimerId_{0};

    // QObject interface
protected:
    void timerEvent(QTimerEvent *event);
};
// Обновить настройки при закрытии приложения
#endif
