#include "Application.h"

#include "Client.h"
#include "Settings.h"

Application::Application(QQmlContext& context, QObject* parent)
    : QObject(parent),
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
    auto ptr = std::make_shared<Client>(socket, emulator_.get());
    clientMap_.emplace(ptr->id(), ptr);
    qDebug() << "!" << ptr->id();

    QObject::connect(ptr.get(), &Client::disconnected, this,
                     [wptr = std::weak_ptr<Client>(ptr), this] {
                         if (!wptr.expired())
                             this->onPopClient(wptr.lock()->id());
                     });
    /*or*/
    //    QObject::connect(ptr.get(), &Client::disconnectedWithId, this,
    //                     [this](int id) { this->onPopClient(id); });


    qDebug() << "Clients number:" << clientMap_.size();
}

void Application::onPopClient(int clientId)
{
    qDebug() << "!" << clientId;
    qDebug() << "Removed clients:" << clientMap_.erase(clientId);
    qDebug() << "Clients number:" << clientMap_.size();
}
