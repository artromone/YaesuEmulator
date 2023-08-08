#include "CommandParser.h"

#include "Logger.h"

#include <QObject>

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

}

void CommandParser::createDictOfCommands(Emulator* emulator)
{
    emulator_ = emulator;

    using namespace std::placeholders;
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
}

void CommandParser::setPos(QTcpSocket* socket, QByteArray input)
{
    Logger::instance()->addLog(QObject::tr("Получена команда: \"Выход в точку\"."), 3);
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

    emulator_->moveTo(azTarget, elTarget);
    emulator_->updateCoords();

    sendAnswer(socket);
}

void CommandParser::setAzSpeed(QTcpSocket* socket, QByteArray input)
{
    Logger::instance()->addLog(QObject::tr("Получена команда: \"Установить азимутальную скорость\"."), 3);

    int azSpeed = parseNumber(input, 1);
    checkNumber(azSpeed);

    emulator_->setSpeed(azSpeed, emulator_->anState().speedEl());
}

void CommandParser::stop(QTcpSocket* socket, QByteArray input)
{
    Logger::instance()->addLog(QObject::tr("Получена команда: \"Стоп\"."), 3);

    emulator_->stop();
}

void CommandParser::stopAz(QTcpSocket* socket, QByteArray input)
{
    Logger::instance()->addLog(QObject::tr("Получена команда: \"Стоп по азимуту\"."), 3);

    emulator_->stop();
}

void CommandParser::stopEl(QTcpSocket* socket, QByteArray input)
{
    Logger::instance()->addLog(QObject::tr("Получена команда: \"Стоп по углу места\"."), 3);

    emulator_->stop();
}

void CommandParser::moveRight(QTcpSocket* socket, QByteArray input)
{
    Logger::instance()->addLog(QObject::tr("Получена команда: \"Двигаться вправо\"."), 3);

    emulator_->move(Diraction::D_Right);
}

void CommandParser::moveLeft(QTcpSocket* socket, QByteArray input)
{
    Logger::instance()->addLog(QObject::tr("Получена команда: \"Двигаться влево\"."), 3);

    emulator_->move(Diraction::D_Left);
}

void CommandParser::moveUp(QTcpSocket* socket, QByteArray input)
{
    Logger::instance()->addLog(QObject::tr("Получена команда: \"Двигаться вверх\"."), 3);

    emulator_->move(Diraction::D_UP);
}

void CommandParser::moveDown(QTcpSocket* socket, QByteArray input)
{
    Logger::instance()->addLog(QObject::tr("Получена команда: \"Двигаться вниз\"."), 3);

    emulator_->move(Diraction::D_Down);
}
