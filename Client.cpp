#include "Client.h"

#include "Settings.h"
#include "CommandParser.h"

#include <QDebug>

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
    qDebug() << "Client" << id_ << "reading data";
    QByteArray input = socket_->readAll();
    qDebug() << "Read data:" << input;

    CommandParser parser;
    parser.createDictOfCommands(emulator_);

    try
    {
        parser.dict[input[0]](socket_, input);
    }
    catch (std::invalid_argument const& e)
    {
        qDebug() << e.what() << '\n';
    }
}
