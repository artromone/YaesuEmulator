#include "Widget.h"

#include <QQmlContext>
#include <QQmlEngine>

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

void Widget::setPort(int other)
{
    Settings::instance()->setPort(other);
    emit this->portChanged();
}

bool Widget::serverState() const
{
    return server_->isStarted();
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

//    QObject::connect(this, &Widget::portChanged, this, [this](bool otherPort) {
//        setPort(otherPort);
//    });
}
