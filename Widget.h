#ifndef WIDGET_H
#define WIDGET_H

#include "Emulator.h"
#include "Settings.h"
#include "Server.h"

#include <QColor>
#include <QObject>

class QQmlContext;

class Widget : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(bool serverState READ serverState WRITE setServerState NOTIFY serverStateChanged)
    Q_PROPERTY(bool serverOK READ serverOK NOTIFY serverOKChanged)

public:
    explicit Widget(QQmlContext& context,
                    Server *server,
                    Emulator* emulator,
                    QObject* parent = Q_NULLPTR);

    Q_INVOKABLE QColor color() const;

    int port() const;
    void setPort(int value);

    bool serverState() const;
    bool serverOK() const;
    void setServerState(bool state);

signals:
    void portChanged();
    void serverStateChanged();
    void serverOKChanged();

private:
    void init();

private:
    Server * const server_;
    Emulator* emulator_;
};

#endif // WIDGET_H
