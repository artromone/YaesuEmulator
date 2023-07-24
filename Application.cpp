#include "Application.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>

Application::Application():
   emulator_(),
   server_(),
   stackClient_(Emulator()),
   widget_(Emulator())
{
   //widget_(emulator_);
}

int Application::start(int argc, char *argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  if (engine.rootObjects().isEmpty())
  {
      return -1;
  }

  Server server;
  Client client;

  return app.exec();
}
