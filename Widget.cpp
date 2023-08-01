#include "Widget.h"

#include <QDateTime>
#include <QQmlContext>
#include <QQmlEngine>

namespace {
QString getCurrTime()
{
    return QDateTime::currentDateTime().toString("[hh:mm:ss] ");
}
} // namespace

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

// bool Widget::serverState() const
//{
//     return server_->isStarted();
// }

// bool Widget::serverOK() const
//{
//     qDebug() << "server_->isOk()" << (server_->state() == Server::S_CONNECTED);
//     return server_->state() == Server::S_CONNECTED;
// }

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

void Widget::init()
{
    emit this->portChanged();

    QObject::connect(server_, &Server::stateChanged, this, [this](ServerState::State state) {
        if (ServerState::S_CONNECTED == state)
            this->sendLogMessage(
                tr("Сервер запущен! Порт <%1>.").arg(Settings::instance()->getPort()));
        if (ServerState::S_DISCONNECTED == state)
            this->sendLogMessage(tr("Сервер остановлен."));
        if (ServerState::S_PORT_BUSY == state)
            this->sendLogMessage(tr("Не удалось запустить сервер. Порт <%1> занят.")
                                     .arg(Settings::instance()->getPort()));

        emit this->serverStateChanged();
    });
}

void Widget::sendLogMessage(const QString& message)
{
    emit this->logMessage(getCurrTime() + message);
}
