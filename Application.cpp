#include "Application.h"

#include "Client.h"
#include "Settings.h"

Application::Application(QQmlContext& context, QObject* parent)
    : QObject(parent),
      emulator_(std::make_unique<Emulator>()),
      server_(std::make_unique<Server>()),
      widget_(context, emulator_.get())
{
    QObject::connect(server_.get(), &Server::newClient, this, &Application::onNewClient);
    QObject::connect(&widget_, &Widget::serverStart, this, &Application::onStartServer);
}

void Application::onNewClient(QTcpSocket* socket)
{
    auto ptr = std::make_shared<Client>(socket, emulator_.get());
    clientMap_.emplace(ptr->id(), ptr);

    QObject::connect(ptr.get(), &Client::disconnected, this,
                     [wptr = std::weak_ptr<Client>(ptr), this] {
                         if (!wptr.expired())
                             this->onPopClient(wptr.lock()->id());
                     });
    /*or*/
    //QObject::connect(ptr.get(), &Client::disconnectedWithId, this,
    //                 this](int id) { this->onPopClient(id); });


    qDebug() << "Clients number:" << clientMap_.size();
}

void Application::onPopClient(int clientId)
{
    qDebug() << "Removed clients:" << clientMap_.erase(clientId)
             << "Clients number:" << clientMap_.size();
}

void Application::onStartServer()
{
    server_.get()->start(Settings::instance()->getPort());
}
