#ifndef EMULATOR_H
#define EMULATOR_H

class Emulator
{
public:
    Emulator();

private:
    enum class AntennaState {
        ready,
        moveto,
        manual
    };

    int azCurrent_;
    int elCurrent_;
    int azTarget_;
    int elTarget_;
    int speedAz_;
    int speedEl_;
};

#endif
