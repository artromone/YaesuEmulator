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

void Emulator::changeCoords(int az, int el)
{
    if (antennaState_.azCurrent() != az)
    {
        qDebug() << "Antenna azCurrent changed.";

        antennaState_.setAzCurrent(az);
        emit this->coordsChanged(antennaState_);
    }
    //emit this->coordsChanged(antennaState_);
}

void Emulator::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == testStateTimerId_)
    {
        // qDebug() << "1 Antenna AZ." << antennaState_.azCurrent();
        AntennaState newAntennaState(antennaState_);
        newAntennaState.setAzCurrent(newAntennaState.azCurrent() + 1);
        //changeCoords(newAntennaState);
        this->changeStatus((AntennaStatus::Status)(((int)antennaStatus_ + 1) % 4));
    }
}
