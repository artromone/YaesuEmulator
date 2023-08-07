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
}

const AntennaState& Emulator::anState() const
{
    return antennaState_;
}

//AntennaState& Emulator::anState()
//{
//    return antennaState_;
//}

void Emulator::updateCoords()
{
    qDebug() << "Emulator change az" << antennaState_.azCurrent()
             << "->" << antennaState_.azTarget();
    qDebug() << "Emulator change el" << antennaState_.elCurrent()
             << "->" << antennaState_.elTarget();

    int speedAz = antennaState_.speedAz();
    int speedEl = antennaState_.speedEl();

    int delay = 200;
    if (delay > 1000 / speedAz)
    {
        delay = 1000 / speedAz;
    }
    if (delay > 1000 / speedEl)
    {
        delay = 1000 / speedEl;
    }

    testStateTimerId_ = this->startTimer(delay);

//    QtConcurrent::run([=] {
//        int speedAz = antennaState_.speedAz();
//        int speedEl = antennaState_.speedEl();

//        int delay = 200;
//        if (delay > 1000 / speedAz)
//        {
//            delay = 1000 / speedAz;
//        }
//        if (delay > 1000 / speedEl)
//        {
//            delay = 1000 / speedEl;
//        }

//        int iterSpeedAz = speedAz * delay / 1000;
//        int iterSpeedEl = speedEl * delay / 1000;

//        while (moveAzPossible_ || moveElPossible_)
//        {
//            int currAz = antennaState_.azCurrent();
//            int targetAz = antennaState_.azTarget();
//            if (targetAz != currAz && canChangeAz(currAz, targetAz, iterSpeedAz))
//            {
//                int newAz = currAz + (targetAz > currAz ? iterSpeedAz : -iterSpeedAz);
//                antennaState_.setAzCurrent(newAz);
//            }

//            int currEl = antennaState_.elCurrent();
//            int targetEl = antennaState_.elTarget();
//            if (targetEl != currEl && canChangeEl(currEl, targetEl, iterSpeedEl))
//            {
//                int newEl = currEl + (targetEl > currEl ? iterSpeedEl : -iterSpeedEl);
//                antennaState_.setElCurrent(newEl);
//            }

//            QThread::msleep(delay);

//            if (targetAz == antennaState_.azCurrent() && targetEl == antennaState_.elCurrent())
//            {
//                Settings::instance()->setAz(targetAz);
//                Settings::instance()->setEl(targetEl);
//                return;
//            }

//            qDebug() << "az:" << anState().azCurrent();
//            qDebug() << "iterSpeedAz:" << iterSpeedAz;

//            qDebug() << "el:" << anState().elCurrent();
//            qDebug() << "iterSpeedEl:" << iterSpeedEl;
//        }
    //    });
}

void Emulator::moveTo(int az, int el)
{
    if (cond)
    {
        antennaState_.setAzTarget();
        antennaState_.setElTarget();
        antennaState_.setStatus("move_to");
    }

}

void Emulator::move(char direction)
{
    antennaState_.setStatus("move");
}

void Emulator::stop()
{

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
    if (event->timerId() == testStateTimerId_)
    {
        int iterSpeedAz = 1;
        int iterSpeedEl = 1;

        int currAz = antennaState_.azCurrent();
        int targetAz = antennaState_.azTarget();
        if (targetAz != currAz && canChangeAz(currAz, targetAz, iterSpeedAz))
        {
            int newAz = currAz + (targetAz > currAz ? iterSpeedAz : -iterSpeedAz);
            antennaState_.setAzCurrent(newAz);
        }

        int currEl = antennaState_.elCurrent();
        int targetEl = antennaState_.elTarget();
        if (targetEl != currEl && canChangeEl(currEl, targetEl, iterSpeedEl))
        {
            int newEl = currEl + (targetEl > currEl ? iterSpeedEl : -iterSpeedEl);
            antennaState_.setElCurrent(newEl);
        }

        if (targetAz == antennaState_.azCurrent() && targetEl == antennaState_.elCurrent())
        {
            Settings::instance()->setAz(targetAz);
            Settings::instance()->setEl(targetEl);
        }

        qDebug() << "az:" << anState().azCurrent();
        qDebug() << "iterSpeedAz:" << iterSpeedAz;

        qDebug() << "el:" << anState().elCurrent();
        qDebug() << "iterSpeedEl:" << iterSpeedEl;

        //this->setStatus((AntennaStatus::Status)(((int)antennaState_.status() + 1) % 4));
    }
}
