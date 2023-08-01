#include "Emulator.h"

#include <QDebug>
#include <QTimerEvent>

Emulator::Emulator():
//     azCurrent_(0),
//     elCurrent_(0),
//     azTarget_(0),
//     elTarget_(0),
     speedAz_(5),
     speedEl_(5)
{
    testStateTimerId_ = this->startTimer(2000);
}

//int Emulator::getAzCurrent() const
//{
//    return azCurrent_;
//}
//int Emulator::getElCurrent() const
//{
//    return elCurrent_;
//}

//int Emulator::getAzTarget() const
//{
//    return azTarget_;
//}
//int Emulator::getElTarget() const
//{
//    return elTarget_;
//}

int Emulator::getSpeedAz() const
{
    return speedAz_;
}
int Emulator::getSpeedEl() const
{
    return speedEl_;
}

AntennaState::State Emulator::state() const
{
    return state_;
}

void Emulator::changeState(AntennaState::State state)
{
    if (state_ != state)
    {
        qDebug() << "Antenna state changed" << state_ << "->" << state;

        state_ = state;
        emit this->stateChanged(state_);
    }
}

void Emulator::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == testStateTimerId_)
    {
        //azCurrent_ += 1;
        this->changeState((AntennaState::State)(((int)state_ + 1) % 4));
    }
}
