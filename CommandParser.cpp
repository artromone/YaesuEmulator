#include "CommandParser.h"

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
}

void CommandParser::createDictOfCommands(Emulator* emulator)
{
    emulator_ = emulator;

    dict['C'] = std::bind(&CommandParser::sendState, this, _1);
    dict['W'] = std::bind(&CommandParser::setPos, this, _1, _2);
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

void CommandParser::setPos(QTcpSocket *socket_, QByteArray input)
{
    int az = parseNumber(input, 1);
    int el = parseNumber(input, 5);

    qDebug() << "az:" << unsafeFormatNumber(az);
    qDebug() << "el:" << unsafeFormatNumber(el);
    // Не удалять дебаг вывод, numberToFormatQByte в случае невалидных данных
    // выбрасывает исключение, которое обрабатывается в Client::onReadyRead()

    emulator_->getModifiableAntennaState().setAzTarget(az);
    emulator_->getModifiableAntennaState().setElTarget(el);
}

void CommandParser::setAzSpeed(QTcpSocket *socket_, QByteArray input)
{

}

//    dict['S'] = 30;
//    dict['A'] = 30;
//    dict['E'] = 30;
//    dict['R'] = 30;
//    dict['L'] = 30;
//    dict['U'] = 30;
//    dict['D'] = 30;
