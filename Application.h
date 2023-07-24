#ifndef APPLICATION_H
#define APPLICATION_H

#include "Client.h"
#include "Emulator.h"
#include "Server.h"
#include "Widget.h"

#include <QObject>

#include <memory>
#include <stack>

class Application : public QObject
{
public:
    explicit Application(QQmlContext& context, QObject* parent = Q_NULLPTR);

public slots:
    void onNewClient(QTcpSocket* socket);

private:
    Settings settings_;
    std::unique_ptr<Emulator> emulator_;
    std::unique_ptr<Server> server_;
    std::stack<std::shared_ptr<Client>> stackClient_;

    Widget widget_;
};

#endif // APPLICATION_H
