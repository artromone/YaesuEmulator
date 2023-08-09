#include "AntennaState.h"

#include "Settings.h"

#include <QDebug>

AntennaState::AntennaState(QObject* parent) : QObject(parent)
{
    azCurrent_ = Settings::instance()->getAz();
    elCurrent_ = Settings::instance()->getEl();
}

void AntennaState::setAzCurrent(int azCurrent)
{
    if (azCurrent == azCurrent_)
    {
        return;
    }
    qDebug() << "Antenna azCurrent changed." << azCurrent_ << "->" << azCurrent;
    azCurrent_ = azCurrent;
    emit this->changed();
}

void AntennaState::setElCurrent(int elCurrent)
{
    if (elCurrent == elCurrent_)
    {
        return;
    }
    qDebug() << "Antenna elCurrent changed." << elCurrent_ << "->" << elCurrent;
    elCurrent_ = elCurrent;
    emit this->changed();
}

void AntennaState::setAzTarget(int azTarget)
{
    if (azTarget == azTarget_)
    {
        return;
    }
    qDebug() << "Antenna azTarget changed." << azTarget_ << "->" << azTarget;
    azTarget_ = azTarget;
    emit this->changed();
}

void AntennaState::setElTarget(int elTarget)
{
    if (elTarget == elTarget_)
    {
        return;
    }
    qDebug() << "Antenna elTarget changed." << elTarget_ << "->" << elTarget;
    elTarget_ = elTarget;
    emit this->changed();
}

void AntennaState::setSpeedAz(int speedAz)
{
    speedAz_ = speedAz;
}

void AntennaState::setSpeedEl(int speedEl)
{
    speedEl_ = speedEl;
}

void AntennaState::setTarget(int azTarget, int elTarget)
{
    setAzTarget(azTarget);
    setElTarget(elTarget);
}

void AntennaState::setCurrent(int azCurrent, int elCurrent)
{
    setAzCurrent(azCurrent);
    setElCurrent(elCurrent);
}

void AntennaState::setSpeed(int azSpeed, int elSpeed)
{
    setSpeedAz(azSpeed);
    setSpeedEl(elSpeed);
}

AntennaStatus::Status AntennaState::status() const
{
    return status_;
}

void AntennaState::setStatus(const AntennaStatus::Status& status)
{
    if (status == status_)
    {
        return;
    }
    qDebug() << "Antenna status changed." << status_ << "->" << status;
    status_ = status;
    emit this->changed();
}
