#include "AntennaState.h"

#include <QDebug>

AntennaState::AntennaState()
{
}

AntennaState::AntennaState(const AntennaState& other)
{
    azCurrent_ = other.azCurrent_;
    elCurrent_ = other.elCurrent_;
    azTarget_ = other.azTarget_;
    elTarget_ = other.elTarget_;
    speedAz_ = other.speedAz_;
    speedEl_ = other.speedEl_;
}

bool AntennaState::operator==(const AntennaState& other)
{
    return azCurrent_ == other.azCurrent_ && elCurrent_ == other.elCurrent_ &&
           azTarget_ == other.azTarget_ && elTarget_ == other.elTarget_ &&
           speedAz_ == other.speedAz_ && speedEl_ == other.speedEl_;
}

bool AntennaState::operator!=(const AntennaState& other)
{
    return !(*this == other); /*azCurrent_ != other.azCurrent_ ||
             elCurrent_ != other.elCurrent_ ||
             azTarget_ != other.azTarget_ ||
             elTarget_ != other.elTarget_ ||
             speedAz_ != other.speedAz_ ||
             speedEl_ != other.speedEl_;*/
}

void AntennaState::setAzCurrent(int azCurrent)
{
    qDebug() << "Antenna azCurrent changed." << azCurrent_ << "->" << azCurrent;
    azCurrent_ = azCurrent;
}


void AntennaState::setElCurrent(int elCurrent)
{
    elCurrent_ = elCurrent;
    qDebug() << "Antenna elCurrent changed.";
}


void AntennaState::setAzTarget(int azTarget)
{
    azTarget_ = azTarget;
    qDebug() << "Antenna azTarget changed.";
}

void AntennaState::setElTarget(int elTarget)
{
    elTarget_ = elTarget;
    qDebug() << "Antenna elTarget changed.";
}

void AntennaState::setSpeedAz(int speedAz)
{
    speedAz_ = speedAz;
}

void AntennaState::setSpeedEl(int speedEl)
{
    speedEl_ = speedEl;
}
