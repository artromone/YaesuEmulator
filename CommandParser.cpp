#include "CommandParser.h"

using namespace std::placeholders;

namespace {

QByteArray unsafeFormatNumber(int n)
{
    if (n >= 10 && n <= 99)
    {
        return QByteArray("0") + QByteArray::number(n);
    }
    if (n >= 100 && n <= 450)
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
    return (input.at(i) - '0') * 100 + (input.at(i + 1) - '0') * 10 + (input.at(i + 2) - '0');
}

void checkNumber(int n)
{
    unsafeFormatNumber(n);
}

void sendAnswer(QTcpSocket* socket)
{
    socket->write(QByteArray("?\r\n"));
}

} // namespace

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

void CommandParser::sendState(QTcpSocket* socket)
{
    auto &state = emulator_->anState();

    QByteArray newData = QByteArray("AZ=") + unsafeFormatNumber(state.azCurrent()) +
                         QByteArray("  EL=") + unsafeFormatNumber(state.elCurrent()) +
                         QByteArray("\r\n");

    socket->write(newData);
    //    qDebug() << QByteArray("Sent state:") << newData;
}

void CommandParser::setPos(QTcpSocket* socket, QByteArray input)
{
    qDebug() << "CommandParser setPos";

    int azTarget = parseNumber(input, 1);
    int elTarget = parseNumber(input, 5);
    checkNumber(azTarget);
    checkNumber(elTarget);

    if (emulator_->anState().azTarget() == azTarget ||
        emulator_->anState().elTarget() == elTarget)
    {
        return;
    }

    emulator_->anState().setAzTarget(azTarget);
    emulator_->anState().setElTarget(elTarget);

    emulator_->updateCoords();
}

void CommandParser::setAzSpeed(QTcpSocket* socket, QByteArray input)
{
    int azSpeed = parseNumber(input, 1);
    checkNumber(azSpeed);

    emulator_->anState().setSpeedAz(azSpeed);

    sendAnswer(socket);
}

void CommandParser::stop(QTcpSocket* socket, QByteArray input)
{
    emulator_->moveAzPossible_ = false;
    emulator_->moveElPossible_ = false;
}

void CommandParser::stopAz(QTcpSocket* socket, QByteArray input)
{
    emulator_->moveAzPossible_ = false;
}

void CommandParser::stopEl(QTcpSocket* socket, QByteArray input)
{
    emulator_->moveElPossible_ = false;
}

void CommandParser::moveRight(QTcpSocket* socket, QByteArray input)
{
    emulator_->anState().setTarget(450, emulator_->anState().elCurrent());
    emulator_->updateCoords();
}

void CommandParser::moveLeft(QTcpSocket* socket, QByteArray input)
{
    emulator_->anState().setTarget(0, emulator_->anState().elCurrent());
    emulator_->updateCoords();
}

void CommandParser::moveUp(QTcpSocket* socket, QByteArray input)
{
    emulator_->anState().setTarget(emulator_->anState().azCurrent(), 180);
    emulator_->updateCoords();
}

void CommandParser::moveDown(QTcpSocket* socket, QByteArray input)
{
    emulator_->anState().setTarget(emulator_->anState().azCurrent(), 0);
    emulator_->updateCoords();
}
