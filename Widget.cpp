#include "Widget.h"

#include <QQmlContext>
#include <QQmlEngine>

Widget::Widget(QQmlContext& context, Emulator* emulator, Settings* settings, QObject* parent)
    : QObject(parent), emulator_(emulator), settings_(settings)
{
    context.setContextProperty("widget", this);
    context.setContextProperty("rectColor", QColor(255, 0, 0));
}

QColor Widget::color() const
{
    qDebug() << "test";

    return QColor(255, 0, 0);
}

int Widget::port() const
{
    return settings_->port;
}

void Widget::setPort(int value)
{
    if (settings_->port != value)
        settings_->port = value;
}
