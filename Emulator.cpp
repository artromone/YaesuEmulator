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

const AntennaState &Emulator::antennaState() const
{
    return antennaState_;
}

//void Emulator::setAntennaState(const AntennaState &antennaState)
//{
//    antennaState_ = AntennaState(antennaState);
//}

void Emulator::changeStatus(AntennaStatus::Status status)
{
    if (antennaStatus_ != status)
    {
        qDebug() << "Antenna status changed" << antennaStatus_ << "->" << status;

        antennaStatus_ = status;
        emit this->statusChanged(antennaStatus_);
    }
}

void Emulator::changeCoords(int azCurrent, int elCurrent, int azTarget, int elTarget)
{
    bool toEmit = false;
    if (antennaState_.azCurrent() != azCurrent)
    {
        //qDebug() << "Antenna azCurrent changed.";
        antennaState_.setAzCurrent(azCurrent);
        toEmit = true;
    }
    if (antennaState_.elCurrent() != elCurrent)
    {
        //qDebug() << "Antenna elCurrent changed.";
        antennaState_.setElCurrent(elCurrent);
        toEmit = true;
    }
    if (antennaState_.azTarget() != azTarget)
    {
        //qDebug() << "Antenna azTarget changed.";
        antennaState_.setAzTarget(azTarget);
        toEmit = true;
    }
    if (antennaState_.elTarget() != elTarget)
    {
        //qDebug() << "Antenna elTarget changed.";
        antennaState_.setElTarget(elTarget);
        toEmit = true;
    }
    if (toEmit)
    {
        emit this->coordsChanged(antennaState_);
    }
}

void Emulator::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == testStateTimerId_)
    {
        changeCoords(antennaState_.azCurrent() + 1, antennaState_.elCurrent() + 1,
                     antennaState_.azTarget() + 1, antennaState_.elTarget() + 1);
        this->changeStatus((AntennaStatus::Status)(((int)antennaStatus_ + 1) % 4));
    }
}
