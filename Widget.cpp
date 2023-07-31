#include "Widget.h"

#include <QQmlContext>
#include <QQmlEngine>
#include <QDateTime>

namespace
{
    QString getCurrTime()
    {
        return QDateTime::currentDateTime().toString("hh:mm");
    }
}

Widget::Widget(QQmlContext& context, Server *server, Emulator* emulator, QObject* parent)
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

bool Widget::serverState() const
{
    return server_->isStarted();
}

bool Widget::serverOK() const
{
    qDebug() << "server_->isOk()" << server_->isOk();
    return server_->isOk();
}

void Widget::setServerState(bool state)
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

    QObject::connect(server_, &Server::stateChanged, this, [this](bool state) {
        emit this->serverStateChanged();
    });
    QObject::connect(server_, &Server::okChanged, this, [this](bool state) {
        emit this->serverOKChanged();
    });
}
