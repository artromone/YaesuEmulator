#include "Widget.h"

#include <QQmlEngine>

#include "Logger.h"

Widget::Widget(QQmlContext& context, Server* server, Emulator* emulator, QObject* parent)
    : QObject(parent), server_(server), emulator_(emulator)
{
    context.setContextProperty("widget", this);

    init();
}

int Widget::port() const
{
    return Settings::instance()->getPort();
}

void Widget::setPort(int otherPort)
{
    if (otherPort == Settings::instance()->getPort())
    {
        return;
    }

    Settings::instance()->setPort(otherPort);

    emit this->portChanged();
}

ServerStatus::Status Widget::serverState() const
{
    return server_->state();
}

AntennaStatus::Status Widget::antennaStatus() const
{
    return emulator_->anState().status();
}

int Widget::az() const
{
    return emulator_->anState().azCurrent();
}

int Widget::el() const
{
    return emulator_->anState().elCurrent();
}

int Widget::targetAz() const
{
    return emulator_->anState().azTarget();
}

int Widget::targetEl() const
{
    return emulator_->anState().elTarget();
}

int Widget::autoConnect() const
{
    return Settings::instance()->getAutoConncet();
}

void Widget::setTunnelLocked(bool value)
{
    return emulator_->setTunnelLocked(value);
}

void Widget::changeServerState(bool state)
{
    qDebug() << "Current server state (started):" << serverState()
             << "Set to state (started):" << state;

    if (state == server_->isStarted())
    {
        return;
    }

    if (state)
    {
        server_->start(Settings::instance()->getPort());
    }
    else
    {
        server_->stop();
    }
}

const QString Widget::antennaStatusString(AntennaStatus::Status status) const
{
    return AntennaStatus::text(status);
}

void Widget::changeAutoconectOption(bool autoconnect)
{
    Settings::instance()->setAutoConncet(autoconnect);
}

void Widget::init()
{
    emit this->portChanged();

    QObject::connect(server_, &Server::stateChanged, this, [this](ServerStatus::Status state) {
        if (server_->state() == ServerStatus::Status::S_CONNECTED)
        {
            this->sendLogMessage(tr("Сервер запущен! Порт [%1].")
                                 .arg(Settings::instance()->getPort()), 1);
        }
        if (ServerStatus::Status::S_DISCONNECTED == state)
        {
            this->sendLogMessage(tr("Сервер остановлен."), 1);
        }
        if (ServerStatus::Status::S_PORT_BUSY == state)
        {
            this->sendLogMessage(tr("Не удалось запустить сервер. Порт [%1] занят.")
                                 .arg(Settings::instance()->getPort()), 2);
        }

        emit this->serverStateChanged();
    });
}

void Widget::sendLogMessage(const QString& message, int logType)
{
    Logger::instance()->addLog(message, logType);
}
