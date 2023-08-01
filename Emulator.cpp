#include "Emulator.h"

#include <QDebug>
#include <QTimerEvent>

Emulator::Emulator():
    antennaState_(AntennaState())
{
    testStateTimerId_ = this->startTimer(2000);
}

AntennaStatus::Status Emulator::status() const
{
    return antennaStatus_;
}

AntennaState Emulator::antennaState() const
{
    return antennaState_;
}

void Emulator::setAntennaState(const AntennaState &antennaState)
{
    antennaState_ = AntennaState(antennaState);
}

void Emulator::changeStatus(AntennaStatus::Status status)
{
    if (antennaStatus_ != status)
    {
        qDebug() << "Antenna status changed" << antennaStatus_ << "->" << status;

        antennaStatus_ = status;
        emit this->statusChanged(antennaStatus_);
    }
}

void Emulator::changeCoords(AntennaState state)
{
    if (antennaState_ != state)
    {
        qDebug() << "Antenna state changed.";

        antennaState_ = state;
        emit this->coordsChanged(antennaState_);
    }
}

void Emulator::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == testStateTimerId_)
    {
        qDebug() << "1 Antenna AZ." << antennaState_.azCurrent();
        antennaState_.setAzCurrent(antennaState_.azCurrent() + 1);
        changeCoords(antennaState_);
        this->changeStatus((AntennaStatus::Status)(((int)antennaStatus_ + 1) % 4));
    }
}
