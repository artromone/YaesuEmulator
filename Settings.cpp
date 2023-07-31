#include "Settings.h"
#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonValue>
#include <QDebug>

void Settings::createDefault()
{
    port_ = 9999;

//    QJsonObject connection;
//    connection.insert("port_number", 9999);

//    currJsonObject_ = QJsonObject();
//    currJsonObject_.insert("connection", connection);
}

Settings *Settings::instance()
{
    static Settings * ptrSettings_ = nullptr;
    if (!ptrSettings_)
    {
        qDebug() << "Creating new Settings instance.";
        ptrSettings_ = new Settings();
        ptrSettings_->load();
    }
    return ptrSettings_;
}

int Settings::getPort()
{
    return port_;
}

void Settings::setPort(int otherPort)
{
    qDebug() << "port:" << port_ << "other port:" << otherPort;
    if (otherPort != port_)
    {
        port_ = otherPort;
        save();
    }
}

void Settings::save() // При отсутствии файла config ошибка в логах, приложение работает правильно
{
    auto fileDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    auto filename = fileDir + "/config.json";

    if (!QDir(fileDir).exists())
    {
        QDir().mkdir(fileDir);
    }

    QFile jsonFile(filename);

    if (!jsonFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "Cannot save settings.";
        jsonFile.close();
        return;
    }

    QJsonObject connection;
    connection.insert("port_number", port_);

    auto currJsonObject = QJsonObject();
    currJsonObject.insert("connection", connection);

    jsonFile.write(QJsonDocument(currJsonObject).toJson(QJsonDocument::Indented));
    jsonFile.close();

    qDebug() << "Successfully saved settings.";
    qDebug() << "Current settings:" << currJsonObject;
}

void Settings::load()
{

    auto filename = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/config.json";

    qDebug() << "Loading settings from file" << filename;

    QFile jsonFile;
    jsonFile.setFileName(filename);

    if (!jsonFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Creating default settings config.";
        createDefault();
        save();
    }

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(jsonFile.readAll(), &error);
    if (error.error != QJsonParseError::NoError)
    {
        qDebug() << "Error read invalid JSON file.";
        jsonFile.close();
        return;
    }

    auto currJsonObject = doc.object();

    port_ = currJsonObject.value("connection")["port_number"].toInt();

    jsonFile.close();

    qDebug() << "Current settings:" << currJsonObject;
}
