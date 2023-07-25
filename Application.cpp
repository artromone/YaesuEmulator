#include "Application.h"

#include "Client.h"
#include "Settings.h"

Application::Application(QQmlContext& context, QObject* parent) : QObject(parent),
    settings_(Settings()),
    emulator_(std::make_unique<Emulator>()),
    server_(std::make_unique<Server>()),
    widget_(context, emulator_.get(), &settings_)
{
    QObject::connect(server_.get(), &Server::newClient, this, &Application::onNewClient);

    server_.get()->start(settings_.port);
}

void Application::onNewClient(QTcpSocket* socket)
{
    stackClient_.push(std::make_shared<Client>(socket, emulator_.get()));
}
