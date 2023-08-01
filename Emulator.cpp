#include "Emulator.h"

#include <QDebug>
#include <QTimerEvent>

Emulator::Emulator():
    antennaState_(AntennaState())
{
    testStateTimerId_ = this->startTimer(2000);
}

AntennaStatus::Status Emulator::state() const
{
    return state_;
}

void Emulator::setAntennaState(const AntennaState &antennaState)
{
    antennaState_ = AntennaState(antennaState);
}

void Emulator::changeState(AntennaStatus::Status state)
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
        this->changeState((AntennaStatus::Status)(((int)state_ + 1) % 4));
    }
}
