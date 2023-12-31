#include "Application.h"
#include "Types.h"
#include "AntennaState.h"
#include "Logger.h"

#include <QQmlContext>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

void registerQmlTypes()
{
    ServerStatus::registerType();
    AntennaStatus::registerType();
}

int main(int argc, char* argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    registerQmlTypes();

    QGuiApplication::setApplicationName("YaesuEmulator");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
            {
                QCoreApplication::exit(-1);
            }
        },
        Qt::QueuedConnection);

    Application application(*engine.rootContext());

    engine.rootContext()->setContextProperty("logger", Logger::instance());
    engine.load(url);
    Logger::instance()->addLog("Старт приложения.");

    application.init();

    return app.exec();
}
