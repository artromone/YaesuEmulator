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
}

void Emulator::moveTo(int az, int el)
{
    if (az == antennaState_.azCurrent() || el == antennaState_.elCurrent())
    {
        return;
    }
    antennaState_.setStatus(AntennaStatus::S_MOVETO);
    antennaState_.setTarget(az, el);
    updateCoords();
}

void Emulator::move(Diraction diraction)
{
    antennaState_.setStatus(AntennaStatus::S_MANUAL);
    if (Diraction::D_Right == diraction)
    {
        antennaState_.setTarget(450, anState().elCurrent());
    }
    else if (Diraction::D_Left == diraction)
    {
        antennaState_.setTarget(0, anState().elCurrent());
    }
    else if (Diraction::D_UP == diraction)
    {
        antennaState_.setTarget(anState().azCurrent(), 180);
    }
    else if (Diraction::D_Down == diraction)
    {
        antennaState_.setTarget(anState().azCurrent(), 0);
    }
    updateCoords();
}

void Emulator::stop()
{
    antennaState_.setTarget(antennaState_.azCurrent(), antennaState_.elCurrent());
    antennaState_.setStatus(AntennaStatus::S_READY);
}

void Emulator::setSpeed(int azSpeed, int elSpeed)
{
    antennaState_.setSpeed(azSpeed, elSpeed);
}

void Emulator::setStatus(AntennaStatus::Status status)
{
    antennaState_.setStatus(status);
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
