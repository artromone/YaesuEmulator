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

    int azCurrent() const;
    void setAzCurrent(int azCurrent);

    int elCurrent() const;
    void setElCurrent(int elCurrent);

private:
    int azCurrent_{0};
    int elCurrent_{0};

    int azTarget_{0};
    int elTarget_{0};

    int speedAz_{5};
    int speedEl_{5};
};

#endif
