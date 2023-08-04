#ifndef ANTENNASTATE_H
#define ANTENNASTATE_H

#include "Types.h"

#include <QObject>
#include <QQmlEngine>

class AntennaState : public QObject
{
    Q_OBJECT

public:
    AntennaState(QObject* parent = nullptr);

    AntennaStatus::Status status() const;
    void setStatus(const AntennaStatus::Status &status);

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

signals:
    void changed();

private:
    AntennaStatus::Status status_{AntennaStatus::S_READY};

    int azCurrent_ {0};
    int elCurrent_ {0};

    int azTarget_ {0};
    int elTarget_ {0};

    int speedAz_ {5};
    int speedEl_ {5};
};

#endif
