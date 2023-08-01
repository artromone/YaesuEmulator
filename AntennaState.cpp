#include "AntennaState.h"

AntennaState::AntennaState():
    azCurrent_(0),
    elCurrent_(0),
    azTarget_(0),
    elTarget_(0),
    speedAz_(5),
    speedEl_(5)
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
