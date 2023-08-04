#include "Emulator.h"

#include <QDebug>
#include <QThread>
#include <QTimerEvent>
#include <QtConcurrent/QtConcurrentRun>

namespace {
bool canMoveLeft(int az, int targetAz, int speed)
{
    return (az >= speed && az >= targetAz + speed);
}
bool canMoveRight(int az, int targetAz, int speed)
{
    return (az <= 450 - speed && az <= targetAz - speed);
}

bool canMoveDown(int el, int targetEl, int speed)
{
    return (el >= speed && el >= targetEl + speed);
}
bool canMoveUp(int el, int targetEl, int speed)
{
    return (el <= 180 && el <= targetEl - speed);
}
bool canChangeAz(int currAz, int targetAz, int iterSpeedAz)
{
    return targetAz > currAz ? canMoveRight(currAz, targetAz, iterSpeedAz) : canMoveLeft(currAz, targetAz, iterSpeedAz);
}
bool canChangeEl(int currEl, int targetEl, int iterSpeedEl)
{
    return targetEl > currEl ? canMoveUp(currEl, targetEl, iterSpeedEl) : canMoveDown(currEl, targetEl, iterSpeedEl);
}
}

Emulator::Emulator()
{
    // testStateTimerId_ = this->startTimer(2000);
}

const AntennaState& Emulator::anState() const
{
    return antennaState_;
}

AntennaState& Emulator::anState()
{
    return antennaState_;
}

void Emulator::updateCoords()
{
    qDebug() << "Emulator change az" << antennaState_.azCurrent()
             << "->" << antennaState_.azTarget();
    qDebug() << "Emulator change el" << antennaState_.elCurrent()
             << "->" << antennaState_.elTarget();

    QtConcurrent::run([=] {
        int speedAz = antennaState_.speedAz();
        int speedEl = antennaState_.speedEl();

        int delay = 200;
        if (delay > 1000 / speedAz)
        {
            delay = 1000 / speedAz;
        }

        int iterSpeedAz = speedAz * delay / 1000;
        int iterSpeedEl = speedEl * delay / 1000;

        while (moveAzPossible_ || moveElPossible_)
        {
            int currAz = antennaState_.azCurrent();
            int targetAz = antennaState_.azTarget();
            if (targetAz != currAz && canChangeAz(currAz, targetAz, iterSpeedAz))
            {
                antennaState_.setAzCurrent(currAz + (targetAz > currAz ? iterSpeedAz : -iterSpeedAz));
            }

            int currEl = antennaState_.elCurrent();
            int targetEl = antennaState_.elTarget();
            if (targetEl != currEl && canChangeEl(currEl, targetEl, iterSpeedEl))
            {
                antennaState_.setElCurrent(currEl + (targetEl > currEl ? iterSpeedEl : -iterSpeedEl));
            }

            QThread::msleep(delay);

            if (targetAz == antennaState_.azCurrent() && targetEl == antennaState_.elCurrent())
            {
                return;
            }

            qDebug() << "az:" << anState().azCurrent();
            qDebug() << "iterSpeedAz:" << iterSpeedAz;

            qDebug() << "el:" << anState().elCurrent();
            qDebug() << "iterSpeedEl:" << iterSpeedEl;

            //            qDebug() << targetAz;
            //            qDebug() << currAz;
            //            qDebug() << iterSpeedAz;
            //            qDebug() << moveAzPossible_ << iterSpeedAz;
            //            qDebug() << canMoveRight(currAz, targetAz, iterSpeedAz) << iterSpeedAz;
            //            qDebug() << canMoveLeft(currAz, targetAz, iterSpeedAz) << iterSpeedAz;
        }
    });
}

void Emulator::setStatus(AntennaStatus::Status status)
{
    antennaState_.setStatus(status);
}

void Emulator::setCoords(int azCurrent, int elCurrent, int azTarget, int elTarget)
{
    antennaState_.setAzCurrent(azCurrent);
    antennaState_.setElCurrent(elCurrent);
    antennaState_.setAzTarget(azTarget);
    antennaState_.setElTarget(elTarget);
}

void Emulator::timerEvent(QTimerEvent* event)
{
    //    if (event->timerId() == testStateTimerId_)
    //    {
    //        //        changeCoords(antennaState_.azCurrent() + 1, antennaState_.elCurrent() + 1,
    //        //                     antennaState_.azTarget() + 1, antennaState_.elTarget() + 1);
    //        this->changeStatus((AntennaStatus::Status)(((int)antennaStatus_ + 1) % 4));
    //    }
}
