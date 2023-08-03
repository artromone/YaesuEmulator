#include "Emulator.h"

#include <QDebug>
#include <QTimerEvent>
#include <QThread>

namespace
{
bool canMoveRight(Emulator* emulator, int targetAz)
{
    int az = emulator->antennaState().azCurrent();
    int speed = emulator->antennaState().speedAz();
    return (az >= 0 && az < targetAz - speed);
}
bool canMoveLeft(Emulator* emulator, int targetAz)
{
    int az = emulator->antennaState().azCurrent();
    int speed = emulator->antennaState().speedAz();
    return (az > 0 + speed && az <= targetAz);
}

bool canMoveDown(Emulator* emulator, int targetEl)
{
    int el = emulator->antennaState().elCurrent();
    int speed = emulator->antennaState().speedEl();
    return (el > 0 + speed && el <= targetEl);
}
bool canMoveUp(Emulator* emulator, int targetEl)
{
    int el = emulator->antennaState().elCurrent();
    int speed = emulator->antennaState().speedEl();
    return (el >= 0 && el < targetEl - speed);
}
}

Emulator::Emulator():
    antennaState_(AntennaState())
{
    // testStateTimerId_ = this->startTimer(2000);
}

AntennaStatus::Status Emulator::status() const
{
    return antennaStatus_;
}

const AntennaState &Emulator::antennaState() const
{
    return antennaState_;
}

AntennaState &Emulator::getModifiableAntennaState()
{
    return antennaState_;
}

void Emulator::changeAz(QTcpSocket *socket, QByteArray input, int targetAz)
{
    int speedAz = antennaState_.speedAz();
    int currAz = antennaState_.azCurrent();
    while (moveAzPossible_ &&
           (targetAz > currAz ? canMoveRight(this, targetAz) : canMoveLeft(this, targetAz)))
    {
        int delay = 500;
        int speed = speedAz / 1000 * delay;

        int currAz = antennaState_.azCurrent();
        antennaState_.setAzCurrent(targetAz > currAz ? currAz + speed : currAz - speed);

        QThread::msleep(delay);
    }
}

void Emulator::changeEl(QTcpSocket *socket, QByteArray input, int targetAz)
{
    int speedEl = antennaState_.speedEl();
    int currEl = antennaState_.elCurrent();
    while (moveElPossible_ &&
           (targetEl > currEl ? canMoveUp(this, targetEl) : canMoveDown(this, targetEl)))
    {
        int delay = 500;
        int speed = speedEl / 1000 * delay;

        int currEl = antennaState_.elCurrent();
        antennaState_.setElCurrent(targetEl > currEl ? currEl + speed : currEl - speed);

        QThread::msleep(delay);
    }
}

void Emulator::changeStatus(AntennaStatus::Status status)
{
    if (antennaStatus_ != status)
    {
        // qDebug() << "Antenna status changed" << antennaStatus_ << "->" << status;

        antennaStatus_ = status;
        emit this->statusChanged(antennaStatus_);
    }
}

void Emulator::changeCoords(int azCurrent, int elCurrent, int azTarget, int elTarget)
{
    bool toEmit = false;
    if (antennaState_.azCurrent() != azCurrent)
    {
        antennaState_.setAzCurrent(azCurrent);
        toEmit = true;
    }
    if (antennaState_.elCurrent() != elCurrent)
    {
        antennaState_.setElCurrent(elCurrent);
        toEmit = true;
    }
    if (antennaState_.azTarget() != azTarget)
    {
        antennaState_.setAzTarget(azTarget);
        toEmit = true;
    }
    if (antennaState_.elTarget() != elTarget)
    {
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
    //    if (event->timerId() == testStateTimerId_)
    //    {
    //        //        changeCoords(antennaState_.azCurrent() + 1, antennaState_.elCurrent() + 1,
    //        //                     antennaState_.azTarget() + 1, antennaState_.elTarget() + 1);
    //        this->changeStatus((AntennaStatus::Status)(((int)antennaStatus_ + 1) % 4));
    //    }
}
