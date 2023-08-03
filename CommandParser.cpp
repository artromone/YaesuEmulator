#include "CommandParser.h"

#include <QThread>

using namespace std::placeholders;

namespace
{
QByteArray unsafeFormatNumber(int n)
{
    if (n >= 10 && n <= 99)
    {
        return QByteArray("0") + QByteArray::number(n);
    }
    if (n >= 100 && n <= 180)
    {
        return QByteArray::number(n);
    }
    if (n >= 0 && n <= 9)
    {
        return QByteArray("00") + QByteArray::number(n);
    }
    throw std::invalid_argument("Некорректный угол:" + std::to_string(n));
}
int parseNumber(QByteArray input, int i)
{
    return (input.at(i) - '0') * 100 + (input.at(i+1) - '0') * 10 + (input.at(i+2) - '0');
}
void checkNumber(int n)
{
    unsafeFormatNumber(n);
}
void sendAnswer(QTcpSocket *socket)
{
    socket->write(QByteArray("?\r\n"));
}

bool canMoveRight(Emulator* emulator, int targetAz)
{
    int az = emulator->antennaState().azCurrent();
    int speed = emulator->antennaState().speedAz();
    return (az >= 0 && az < targetAz - speed);
}
bool canMoveLeft(Emulator* emulator, int targetAz)
{
    int az = emulator->antennaState().azCurrent();
    int speed = emulator->antennaState().speedAz();
    return (az > 0 + speed && az <= targetAz);
}

bool canMoveDown(Emulator* emulator, int targetEl)
{
    int el = emulator->antennaState().elCurrent();
    int speed = emulator->antennaState().speedEl();
    return (el > 0 + speed && el <= targetEl);
}
bool canMoveUp(Emulator* emulator, int targetEl)
{
    int el = emulator->antennaState().elCurrent();
    int speed = emulator->antennaState().speedEl();
    return (el >= 0 && el < targetEl - speed);
}
}

void CommandParser::moveAzImpl(QTcpSocket *socket, QByteArray input, int targetAz)
{
    int speedAz = emulator_->antennaState().speedAz();
    int currAz = emulator_->antennaState().azCurrent();
    while (moveAzPossible_ && (targetAz > currAz ?
                               canMoveRight(emulator_, targetAz) : canMoveLeft(emulator_, targetAz)))
    {
        int delay = 500;
        int speed = speedAz / 1000 * delay;

        int currAz = emulator_->antennaState().azCurrent();
        emulator_->getModifiableAntennaState().setAzCurrent(targetAz > currAz ? currAz + speed : currAz - speed);

        QThread::msleep(delay);
    }
}
void CommandParser::moveElImpl(QTcpSocket *socket, QByteArray input, int targetEl)
{
    int speedEl = emulator_->antennaState().speedEl();
    int currEl = emulator_->antennaState().elCurrent();
    while (moveElPossible_ && (targetEl > currEl ?
                               canMoveUp(emulator_, targetEl) : canMoveDown(emulator_, targetEl)))
    {
        int delay = 500;
        int speed = speedEl / 1000 * delay;

        int currEl = emulator_->antennaState().elCurrent();
        emulator_->getModifiableAntennaState().setElCurrent(targetEl > currEl ? currEl + speed : currEl - speed);

        QThread::msleep(delay);
    }
}

void CommandParser::createDictOfCommands(Emulator* emulator)
{
    emulator_ = emulator;

    dict['S'] = std::bind(&CommandParser::stop, this, _1, _2);
    dict['A'] = std::bind(&CommandParser::stopAz, this, _1, _2);
    dict['E'] = std::bind(&CommandParser::stopEl, this, _1, _2);
    dict['W'] = std::bind(&CommandParser::setPos, this, _1, _2);
    dict['U'] = std::bind(&CommandParser::moveUp, this, _1, _2);
    dict['D'] = std::bind(&CommandParser::moveDown, this, _1, _2);
    dict['L'] = std::bind(&CommandParser::moveLeft, this, _1, _2);
    dict['R'] = std::bind(&CommandParser::moveRight, this, _1, _2);
    dict['X'] = std::bind(&CommandParser::setAzSpeed, this, _1, _2);
    dict['C'] = std::bind(&CommandParser::sendState, this, _1);
}

void CommandParser::sendState(QTcpSocket *socket)
{
    auto state = emulator_->antennaState();

    QByteArray newData =
            QByteArray("AZ=") + unsafeFormatNumber(state.azCurrent()) +
            QByteArray("  EL=") + unsafeFormatNumber(state.elCurrent()) +
            QByteArray("\r\n");

    socket->write(newData);
    qDebug() << QByteArray("Sent state:") << newData;
}

void CommandParser::setPos(QTcpSocket *socket, QByteArray input)
{
    int azTarget = parseNumber(input, 1);
    int elTarget = parseNumber(input, 5);
    checkNumber(azTarget);
    checkNumber(elTarget);

    emulator_->getModifiableAntennaState().setAzTarget(azTarget);
    emulator_->getModifiableAntennaState().setElTarget(elTarget);

    if (azTarget != emulator_->antennaState().azCurrent())
    {
        moveAzImpl(socket, input, azTarget);
    }
    if (elTarget != emulator_->antennaState().elCurrent())
    {
        moveElImpl(socket, input, elTarget);
    }

    sendAnswer(socket);
}

void CommandParser::setAzSpeed(QTcpSocket *socket, QByteArray input)
{
    int azSpeed = parseNumber(input, 1);
    checkNumber(azSpeed);

    emulator_->getModifiableAntennaState().setSpeedAz(azSpeed);

    sendAnswer(socket);
}

void CommandParser::stop(QTcpSocket *socket, QByteArray input)
{
    moveAzPossible_ = false;
    moveElPossible_ = false;
}

void CommandParser::stopAz(QTcpSocket *socket, QByteArray input)
{
    moveAzPossible_ = false;
}

void CommandParser::stopEl(QTcpSocket *socket, QByteArray input)
{
    moveElPossible_ = false;
}

void CommandParser::moveRight(QTcpSocket *socket, QByteArray input)
{
    moveAzImpl(socket, input, 450);
}

void CommandParser::moveLeft(QTcpSocket *socket, QByteArray input)
{
    moveAzImpl(socket, input, 0);
}

void CommandParser::moveUp(QTcpSocket *socket, QByteArray input)
{
    moveElImpl(socket, input, 180);
}

void CommandParser::moveDown(QTcpSocket *socket, QByteArray input)
{
    moveElImpl(socket, input, 0);
}
