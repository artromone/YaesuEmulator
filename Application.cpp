#include "Application.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>

Application::Application(int argc, char *argv[]):
   QGuiApplication{argc, argv},
   emulator_(std::make_unique<Emulator>()),
   server_(std::make_unique<Server>())
{
   //widget_(Widget(emulator_));
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

  Server server;
  Client client;
}
