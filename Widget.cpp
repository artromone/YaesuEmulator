#include "Widget.h"

#include <QDateTime>
#include <QQmlContext>
#include <QQmlEngine>

namespace
{
    QString getCurrTime()
    {
        return QDateTime::currentDateTime().toString("[hh:mm:ss] ");
    }
}

Widget::Widget(QQmlContext& context, Server* server, Emulator* emulator, QObject* parent)
    : QObject(parent), server_(server), emulator_(emulator)
{
    context.setContextProperty("widget", this);

    // context.setContextProperty("rectColor", QColor(255, 0, 0));

    init();
}

QColor Widget::color() const
{
    return QColor(255, 0, 0);
}

int Widget::port() const
{
    return Settings::instance()->getPort();
}

QPair<QPair<int, int>, QPair<int, int> > Widget::antennaCoords() const
{
    return qMakePair(qMakePair(0,0), qMakePair(0,0));
}

QString Widget::logMsg() const
{
    return getCurrTime();
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

ServerState::State Widget::serverState() const
{
    return server_->state();
}

AntennaState::State Widget::antennaState() const
{
    return emulator_->state();
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

const QString Widget::antennaStateString(AntennaState::State state) const
{
    return AntennaState::text(state);
}

void Widget::init()
{
    emit this->portChanged();

    QObject::connect(server_, &Server::stateChanged, this, [this](ServerState::State state) {
        // if (ServerState::S_CONNECTED == state)
        if (server_->state() == ServerState::State::S_CONNECTED)
        {
            this->sendLogMessage(
                tr("Сервер запущен! Порт <%1>.").arg(Settings::instance()->getPort()));
        }
        if (ServerState::State::S_DISCONNECTED == state)
        {
            this->sendLogMessage(tr("Сервер остановлен."));
        }
        if (ServerState::State::S_PORT_BUSY == state)
        {
            //QString redPart = QString("<span style=\" color:#ff0000;\">Не удалось запустить сервер...
            //...Порт <%1> занят.</span>").arg(Settings::instance()->getPort());
            this->sendLogMessage(tr("Не удалось запустить сервер. Порт <%1> занят.")
                                    .arg(Settings::instance()->getPort()));
        }

        emit this->serverStateChanged();
    });
    QObject::connect(emulator_, &Emulator::stateChanged, this, [this](AntennaState::State state) {
        if (emulator_->state() == AntennaState::State::S_READY)
        {
            this->sendLogMessage(tr("Антенна готова."));
        }
        if (emulator_->state() == AntennaState::State::S_MOVETO)
        {
            this->sendLogMessage(tr("Антенна отправляется в точку."));
        }
        if (emulator_->state() == AntennaState::State::S_MANUAL)
        {
            this->sendLogMessage(tr("Ручное управление антенной."));
        }

        emit this->antennaStateChanged();
    });
    QObject::connect(emulator_, &Emulator::stateChanged, this, [this](AntennaState::State state) {
        if (emulator_->state() == AntennaState::State::S_READY)
        {
            this->sendLogMessage(tr("Антенна готова."));
        }
        if (emulator_->state() == AntennaState::State::S_MOVETO)
        {
            this->sendLogMessage(tr("Антенна отправляется в точку."));
        }
        if (emulator_->state() == AntennaState::State::S_MANUAL)
        {
            this->sendLogMessage(tr("Ручное управление антенной."));
        }

        emit this->antennaCoordsChanged();
    });
}

void Widget::sendLogMessage(const QString& message)
{
    emit this->logMessage(getCurrTime() + message);
}
