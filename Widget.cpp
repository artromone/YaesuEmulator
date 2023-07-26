#include "Widget.h"

#include <QQmlContext>
#include <QQmlEngine>

Widget::Widget(QQmlContext& context, Emulator* emulator, QObject* parent)
    : QObject(parent), emulator_(emulator)
{
    context.setContextProperty("widget", this);
    context.setContextProperty("rectColor", QColor(255, 0, 0));

    init();
}

void Widget::startServer()
{
    qDebug() << "startServer";
}

QColor Widget::color() const
{
    qDebug() << "test";

    return QColor(255, 0, 0);
}

int Widget::port() const
{
    return Settings::instance()->port;
}

void Widget::setPort(int other)
{
    Settings::instance()->port = other;
}

void Widget::init()
{
    emit this->portChanged();
}
