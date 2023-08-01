#ifndef WIDGET_H
#define WIDGET_H

#include "Emulator.h"
#include "Server.h"
#include "Settings.h"

#include <QColor>
#include <QObject>

class QQmlContext;

class Widget : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
    //    Q_PROPERTY(bool serverState READ serverState WRITE setServerState NOTIFY
    //    serverStateChanged) Q_PROPERTY(bool serverOK READ serverOK NOTIFY serverOKChanged)
    Q_PROPERTY(QString logMsg READ logMsg)
    Q_PROPERTY(ServerState::State serverState READ serverState NOTIFY serverStateChanged)

public:
    explicit Widget(QQmlContext& context,
                    Server* server,
                    Emulator* emulator,
                    QObject* parent = Q_NULLPTR);

    Q_INVOKABLE QColor color() const;

    int port() const;
    QString logMsg() const;

    void setPort(int value);

    ServerState::State serverState() const;
    Q_INVOKABLE void changeServerState(bool state);
    //    bool serverOK() const;
    //    void setServerState(bool state);

signals:
    void portChanged();
    void serverStateChanged();
    //    void serverOKChanged();
    void logMessage(const QString& msg);

private:
    void init();
    void sendLogMessage(const QString& message);

private:
    Server* const server_;
    Emulator* emulator_;
};

#endif // WIDGET_H
