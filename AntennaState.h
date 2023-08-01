#ifndef ANTENNASTATE_H
#define ANTENNASTATE_H

class AntennaState
{
public:
    AntennaState();
    ~AntennaState() = default;
    AntennaState(const AntennaState&);
    bool operator==(const AntennaState&);
    bool operator!=(const AntennaState&);

    int azCurrent() const;
    void setAzCurrent(int azCurrent);

    int elCurrent() const;
    void setElCurrent(int elCurrent);

private:
    int azCurrent_;
    int elCurrent_;

    int azTarget_;
    int elTarget_;

    int speedAz_;
    int speedEl_;
};

#endif
