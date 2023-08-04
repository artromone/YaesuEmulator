#include "Emulator.h"

#include <QDebug>
#include <QThread>
#include <QTimerEvent>
#include <QtConcurrent/QtConcurrentRun>

namespace {
bool canMoveRight(int az, int targetAz, int speed)
{
    return (az <= 450 - speed && az <= targetAz - speed);
}
bool canMoveLeft(int az, int targetAz, int speed)
{
    return (az >= speed && az >= targetAz + speed);
}

bool canMoveDown(int el, int targetEl, int speed)
{
    return (el >= 0 + speed && el <= targetEl);
}
bool canMoveUp(int el, int targetEl, int speed)
{
    return (el >= 0 && el <= targetEl - speed);
}
void changeAzImpl(Emulator* emulator, int targetAz)
{
    //    int speedAz = emulator->antennaState().speedAz();
    //    int currAz = emulator->antennaState().azCurrent();

    //    int delay = 200;
    //    int speed = speedAz * delay / 1000;

    //    while (emulator->moveAzPossible_ && (targetAz != currAz) &&
    //           (targetAz > currAz ? canMoveRight(emulator, targetAz, speed) :
    //            canMoveLeft(emulator, targetAz, speed)))
    //    {
    //        int currAz = emulator->antennaState().azCurrent();
    //        emulator->antennaState().setAzCurrent(targetAz > currAz ? currAz + speed :
    //                                                                  currAz - speed);

    //        qDebug() << "az:" << emulator->antennaState().azCurrent();
    //        qDebug() << "speed:" << speed;

    //        QThread::currentThread()->msleep(delay);
    //    }
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
    if (targetAz != antennaState_.azCurrent())
    {
        qDebug() << "Emulator change az" << antennaState_.azCurrent() << "->" << targetAz;

        QtConcurrent::run([=] {
            int speedAz = antennaState_.speedAz();

            int delay = 200;
            if (delay > 1000 / speedAz)
            {
                delay = 1000 / speedAz;
            }

            int speed = speedAz * delay / 1000;

            auto check = [=]() {
                int az = antennaState_.azCurrent();
                //return (currAz >= 0 && currAz <= targetAz - speed);
                qDebug() << "az >= 0" << (az >= 0);
                qDebug() << "az <= targetAz - speed" << (az <= targetAz - speed);
                return (az >= 0 && az <= targetAz - speed);
            };

            auto check2 = [=]() {
                int az = antennaState_.azCurrent();
                //return (currAz >= 0 + speed && currAz <= targetAz);
                qDebug() << "az >= 0 + speed" << (az >= 0 + speed);
                qDebug() << "az <= targetAz" << (az <= targetAz);
                return (az >= 0 + speed && targetAz < az);
            };


            while (moveAzPossible_ && (targetAz != antennaState().azCurrent()))
            {
                qDebug() << "c1" << check() << "c2" << check2();
                int currAz = antennaState_.azCurrent();
                if (!(targetAz > currAz ? canMoveRight(currAz, targetAz, speed) : canMoveLeft(currAz, targetAz, speed)))
                {
                    break;
                }
                antennaState_.setAzCurrent(targetAz > currAz ? currAz + speed : currAz - speed);

                qDebug() << "az:" << antennaState().azCurrent();
                qDebug() << "speed:" << speed;

                qDebug() << targetAz;
                qDebug() << currAz;
                qDebug() << speed;
                qDebug() << moveAzPossible_ << speed;
                qDebug() << canMoveRight(currAz, targetAz, speed) << speed;
                qDebug() << canMoveLeft(currAz, targetAz, speed) << speed;

                QThread::msleep(delay);
            }
        });
    }
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
