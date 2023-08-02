#include "CommandParser.h"

using namespace std::placeholders;

namespace
{
QByteArray numberToFormatQByte(int n)
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
    // throw;
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

    QByteArray newData = QByteArray("AZ=") + numberToFormatQByte(state.azCurrent()) +
            QByteArray("  EL=") + numberToFormatQByte(state.elCurrent()) + QByteArray("\r\n");

    socket->write(newData);
    qDebug() << "Sent state:" << newData;
}

void CommandParser::setPos(QTcpSocket *socket_, QByteArray input)
{
    int az = (input.at(1) - '0') * 100 + (input.at(2) - '0') * 10 + (input.at(3) - '0');
    int el = (input.at(4) - '0') * 100 + (input.at(5) - '0') * 10 + (input.at(6) - '0');
    AntennaState& ref = const_cast<AntennaState&>(emulator_->antennaState());
    ref.setAzTarget(az);
    ref.setElTarget(el); // так не обновляется

    emulator_->antennaState().setAzCurrent(0); // так не билдится

    qDebug() << emulator_->antennaState().azCurrent() << " "
             << emulator_->antennaState().elCurrent();
}

//    dict['W'] = 20;
//    dict['X'] = 30;
//    dict['S'] = 30;
//    dict['A'] = 30;
//    dict['E'] = 30;
//    dict['R'] = 30;
//    dict['L'] = 30;
//    dict['U'] = 30;
//    dict['D'] = 30;
