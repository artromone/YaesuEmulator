#ifndef APPLICATION_H
#define APPLICATION_H

#include <stack>
#include <QGuiApplication>
#include <memory>
#include "Client.h"
#include "Emulator.h"
#include "Server.h"
#include "Widget.h"

class Application : public QGuiApplication
{
public:
    Application(int argc, char *argv[]);
    void start();

public slots:
    void onNewClient(QTcpSocket * socket);

private:
    std::unique_ptr<Emulator> emulator_;
    std::unique_ptr<Server> server_;
    std::stack<std::shared_ptr<Client>> stackClient_;
    Widget widget_;
};

#endif // APPLICATION_H
