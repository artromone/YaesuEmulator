#include "Client.h"

#include <QDebug>
#include <QDateTime>

#include "CommandParser.h"
#include "Settings.h"
#include "Logger.h"

static int COUNTER = 0;

Client::Client(QTcpSocket* socket, Emulator* emulator, QObject* parent)
    : QObject(parent), socket_(socket), emulator_(emulator), id_(COUNTER++)
{
    qDebug() << "Constructing Client:" << id_;
    QObject::connect(socket_, &QTcpSocket::connected, this, &Client::onConnected);

    QObject::connect(socket_, &QTcpSocket::disconnected, this, &Client::onDisconnected);
    QObject::connect(socket_, &QTcpSocket::readyRead, this, &Client::onReadyRead);
}

Client::~Client()
{
}

void Client::onConnected()
{
    qDebug() << "Client" << id_ << "connected";
}

void Client::onDisconnected()
{
    qDebug() << "Client" << id_ << "emitted disconnected";
    emit this->disconnected();
}

void Client::onReadyRead()
{
    QByteArray input = socket_->readAll();

    CommandParser parser;
    parser.createDictOfCommands(emulator_);

    if (!emulator_->isLockedTunnel())
    {
        try
        {
            if (parser.dict.count(input[0]) > 0)
            {
                parser.dict[input[0]](socket_, input);
            }
            else
            {
                Logger::instance()->addLog(QString("Команда не распознана"), 2);
            }
        }
        catch (std::invalid_argument const& e)
        {
            qDebug() << e.what() << '\n';
        }
    }
}
