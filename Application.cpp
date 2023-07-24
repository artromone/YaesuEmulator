#include "Application.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Client.h"

Application::Application(int argc, char *argv[]):
   QGuiApplication{argc, argv},
   emulator_(std::make_unique<Emulator>()),
   server_(std::make_unique<Server>())
{
   QObject::connect(server_.get(), &Server::newClient, this, &Application::onNewClient);
   //widget_(Widget(emulator_));
}

void Application::onNewClient(QTcpSocket * socket)
{
    stackClient_.push(std::make_shared<Client>(socket, emulator_.get()));
}

void Application::start()
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app();

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  //if (engine.rootObjects().isEmpty())
  //{
  //    return -1;
  //}

//  Server server;
//  Client client;
}
