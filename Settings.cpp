#include "Settings.h"
#include <QFile>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QDebug>

void Settings::createDefault()
{
    QJsonObject connection;
    connection.insert("port_number", 9999);

    currJsonObject_ = QJsonObject();
    currJsonObject_.insert("connection", connection);
}

Settings *Settings::instance()
{
    static Settings * ptrSettings_ = nullptr;
    if (!ptrSettings_)
    {
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
    if (otherPort != port_)
    {
        port_ = otherPort;
        save();
    }
}

void Settings::save()
{
    auto filename = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/Config.json";

    QFile jsonFile(filename);

    if (!jsonFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "Cannot save settings.";
        jsonFile.close();
        return;
    }

    jsonFile.write(QJsonDocument(currJsonObject_).toJson(QJsonDocument::Indented));
    jsonFile.close();

    qDebug() << "Successfully saved settings.";
}

void Settings::load()
{
    auto filename = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/Config.json";

    QFile jsonFile;
    jsonFile.setFileName(filename);

    if (!jsonFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Creating default settings config.";
        createDefault();
        save();
        return;
    }

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(jsonFile.readAll(), &error);
    if (error.error != QJsonParseError::NoError)
    {
        qDebug() << "Error read invalid JSON file.";
        jsonFile.close();
        return;
    }

    currJsonObject_ = doc.object();
    jsonFile.close();
}
