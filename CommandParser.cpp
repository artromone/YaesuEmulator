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
bool canMoveRight(Emulator* emulator)
{
    int az = emulator->antennaState().azCurrent();
    int speed = emulator->antennaState().speedAz();
    return (az >= 0 && az < 450 - speed);
}
bool canMoveLeft(Emulator* emulator)
{
    int az = emulator->antennaState().azCurrent();
    int speed = emulator->antennaState().speedAz();
    return (az > 0 + speed && az <= 450);
}
bool canMoveDown(Emulator* emulator)
{
    int el = emulator->antennaState().elCurrent();
    int speed = emulator->antennaState().speedEl();
    return (el > 0 + speed && el <= 180);
}
bool canMoveUp(Emulator* emulator)
{
    int el = emulator->antennaState().elCurrent();
    int speed = emulator->antennaState().speedEl();
    return (el >= 0 && el < 180 - speed);
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
    int az = parseNumber(input, 1);
    int el = parseNumber(input, 5);
    checkNumber(az);
    checkNumber(el);

    emulator_->getModifiableAntennaState().setAzTarget(az);
    emulator_->getModifiableAntennaState().setElTarget(el);

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
    int speedAz = emulator_->antennaState().speedAz();
    while (moveAzPossible_ && canMoveRight(emulator_))
    {
        int currAz = emulator_->antennaState().azCurrent();
        emulator_->getModifiableAntennaState().setAzCurrent(currAz + speedAz);
        QThread::msleep(1000);
    }
}

void CommandParser::moveLeft(QTcpSocket *socket, QByteArray input)
{
    int speedAz = emulator_->antennaState().speedAz();
    while (moveAzPossible_ && canMoveLeft(emulator_))
    {
        int currAz = emulator_->antennaState().azCurrent();
        emulator_->getModifiableAntennaState().setAzCurrent(currAz - speedAz);
        QThread::msleep(1000);
    }
}

void CommandParser::moveUp(QTcpSocket *socket, QByteArray input)
{
    int speedEl = emulator_->antennaState().speedEl();
    while (moveElPossible_ && canMoveUp(emulator_))
    {
        int currEl = emulator_->antennaState().elCurrent();
        emulator_->getModifiableAntennaState().setElCurrent(currEl + speedEl);
        QThread::msleep(1000);
    }
}

void CommandParser::moveDown(QTcpSocket *socket, QByteArray input)
{
    int speedEl = emulator_->antennaState().speedEl();
    while (moveElPossible_ && canMoveDown(emulator_))
    {
        int currEl = emulator_->antennaState().elCurrent();
        emulator_->getModifiableAntennaState().setElCurrent(currEl - speedEl);
        QThread::msleep(1000);
    }
}
