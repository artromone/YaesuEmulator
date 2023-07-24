#ifndef WIDGET_H
#define WIDGET_H

#include "Emulator.h"
#include "Settings.h"

#include <QColor>
#include <QObject>

class QQmlContext;

class Widget : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)

public:
    explicit Widget(QQmlContext& context,
                    Emulator* emulator,
                    Settings* settings,
                    QObject* parent = Q_NULLPTR);

    Q_INVOKABLE QColor color() const;

    int port() const;
    void setPort(int value);

signals:
    void portChanged();

private:
    Emulator* emulator_;
    Settings* settings_;
};

#endif // WIDGET_H
