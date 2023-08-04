#ifndef ANTENNASTATE_H
#define ANTENNASTATE_H

#include <QObject>
#include <QQmlEngine>

class AntennaState
{
public:
    AntennaState();
    AntennaState(const AntennaState&);

    bool operator==(const AntennaState&);
    bool operator!=(const AntennaState&);

    int azCurrent() const { return azCurrent_; }
    void setAzCurrent(int azCurrent);

    int elCurrent() const { return elCurrent_; }
    void setElCurrent(int elCurrent);

    int azTarget() const { return azTarget_; }
    void setAzTarget(int azTarget);

    int elTarget() const { return elTarget_; }
    void setElTarget(int elTarget);

    int speedAz() const { return speedAz_; }
    void setSpeedAz(int speedAz);

    int speedEl() const { return speedEl_; }
    void setSpeedEl(int speedEl);

private:
    int azCurrent_ {0};
    int elCurrent_ {0};

    int azTarget_ {0};
    int elTarget_ {0};

    int speedAz_ {5};
    int speedEl_ {5};
};

#endif
