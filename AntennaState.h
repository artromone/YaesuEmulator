#ifndef ANTENNASTATE_H
#define ANTENNASTATE_H

class AntennaState
{
public:
    AntennaState();
    ~AntennaState() = default;
    AntennaState(const AntennaState&);

private:
    int azCurrent_;
    int elCurrent_;

    int azTarget_;
    int elTarget_;

    int speedAz_;
    int speedEl_;
};

#endif
