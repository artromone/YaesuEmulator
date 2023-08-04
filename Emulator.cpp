#include "Emulator.h"

#include <QDebug>
#include <QThread>
#include <QTimerEvent>
#include <QtConcurrent/QtConcurrentRun>

namespace {
bool canMoveRight(Emulator* emulator, int targetAz, int speed)
{
    int az = emulator->antennaState().azCurrent();
    return (az >= 0 && az <= targetAz - speed);
}
bool canMoveLeft(Emulator* emulator, int targetAz, int speed)
{
    int az = emulator->antennaState().azCurrent();
    return (az >= 0 + speed && az <= targetAz);
}

bool canMoveDown(Emulator* emulator, int targetEl, int speed)
{
    int el = emulator->antennaState().elCurrent();
    return (el >= 0 + speed && el <= targetEl);
}
bool canMoveUp(Emulator* emulator, int targetEl, int speed)
{
    int el = emulator->antennaState().elCurrent();
    return (el >= 0 && el <= targetEl - speed);
}
void changeAzImpl(Emulator* emulator, int targetAz)
{
    int speedAz = emulator->antennaState().speedAz();
    int currAz = emulator->antennaState().azCurrent();

    int delay = 200;
    int speed = speedAz * delay / 1000;

    while (emulator->moveAzPossible_ && (targetAz != currAz) &&
           (targetAz > currAz ? canMoveRight(emulator, targetAz, speed) :
            canMoveLeft(emulator, targetAz, speed)))
    {
        int currAz = emulator->antennaState().azCurrent();
        emulator->antennaState().setAzCurrent(targetAz > currAz ? currAz + speed :
                                                                  currAz - speed);

        qDebug() << "az:" << emulator->antennaState().azCurrent();
        qDebug() << "speed:" << speed;

        QThread::currentThread()->msleep(delay);
    }
}
} // namespace

Emulator::Emulator()
{
    // testStateTimerId_ = this->startTimer(2000);
}

const AntennaState& Emulator::antennaState() const
{
    return antennaState_;
}

AntennaState& Emulator::antennaState()
{
    return antennaState_;
}

void Emulator::changeAz(int targetAz)
{
    qDebug() << "Emulator change az" << antennaState_.azCurrent() << "->" << targetAz;

    QtConcurrent::run([=] {
        int speedAz = antennaState_.speedAz();
        int currAz = antennaState_.azCurrent();

        int delay = 200;
        int speed = speedAz * delay / 1000;

        auto check = [=]() {
            int az = antennaState_.azCurrent();
            return (az >= 0 && az <= targetAz - speed);
        };

        auto check2 = [=]() {
            int az = antennaState_.azCurrent();
            return (az >= 0 + speed && az <= targetAz);
        };

        qDebug() << "c1" << check() << "c2" << check2();

        while (moveAzPossible_ && (targetAz != currAz) && (targetAz > currAz ? check() : check2()))
        {
            int currAz = antennaState_.azCurrent();
            antennaState_.setAzCurrent(targetAz > currAz ? currAz + speed : currAz - speed);

            qDebug() << "az:" << antennaState().azCurrent();
            qDebug() << "speed:" << speed;

            QThread::msleep(delay);
        }
    });
}

void Emulator::changeEl(int targetEl)
{
    //    int speedEl = antennaState_.speedEl();
    //    int currEl = antennaState_.elCurrent();

    //    int delay = 500;
    //    int speed = speedEl * delay / 1000;

    //    while (moveElPossible_ && (targetEl != currEl) &&
    //           (targetEl > currEl ? canMoveUp(this, targetEl, speed) : canMoveDown(this, targetEl, speed)))
    //    {
    //        int currEl = antennaState_.elCurrent();
    //        antennaState_.setElCurrent(targetEl > currEl ? currEl + speed : currEl - speed);

    //        qDebug() << antennaState_.azCurrent();

    //        QThread::currentThread()->msleep(delay);
    //    }
}

void Emulator::changeStatus(AntennaStatus::Status status)
{
    antennaState_.setStatus(status);
}

void Emulator::changeCoords(int azCurrent, int elCurrent, int azTarget, int elTarget)
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
