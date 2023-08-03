#include "AntennaState.h"

AntennaState::AntennaState()
{}

AntennaState::AntennaState(const AntennaState &other)
{
    azCurrent_ = other.azCurrent_;
    elCurrent_ = other.elCurrent_;
    azTarget_ = other.azTarget_;
    elTarget_ = other.elTarget_;
    speedAz_ = other.speedAz_;
    speedEl_ = other.speedEl_;
}

bool AntennaState::operator==(const AntennaState &other)
{
    return azCurrent_ == other.azCurrent_ &&
            elCurrent_ == other.elCurrent_ &&
            azTarget_ == other.azTarget_ &&
            elTarget_ == other.elTarget_ &&
            speedAz_ == other.speedAz_ &&
            speedEl_ == other.speedEl_;
}

bool AntennaState::operator!=(const AntennaState &other)
{
    return azCurrent_ != other.azCurrent_ ||
            elCurrent_ != other.elCurrent_ ||
            azTarget_ != other.azTarget_ ||
            elTarget_ != other.elTarget_ ||
            speedAz_ != other.speedAz_ ||
            speedEl_ != other.speedEl_;
}

int AntennaState::azCurrent() const
{
    return azCurrent_;
}
void AntennaState::setAzCurrent(int azCurrent)
{
    azCurrent_ = azCurrent;
}

int AntennaState::elCurrent() const
{
    return elCurrent_;
}
void AntennaState::setElCurrent(int elCurrent)
{
    elCurrent_ = elCurrent;
}

int AntennaState::azTarget() const
{
    return azTarget_;
}

void AntennaState::setAzTarget(int azTarget)
{
    azTarget_ = azTarget;
}

int AntennaState::elTarget() const
{
    return elTarget_;
}

void AntennaState::setElTarget(int elTarget)
{
    elTarget_ = elTarget;
}

int AntennaState::speedAz() const
{
    return speedAz_;
}

void AntennaState::setSpeedAz(int speedAz)
{
    speedAz_ = speedAz;
}
