#include "Settings.h"
#include <QFile>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonValue>
#include <QDebug>

void Settings::createDefault()
{
    QJsonObject connection;
    connection.insert("port_number", 9999);

    currJsonObject_ = QJsonObject();
    currJsonObject_.insert("connection", connection);
}

void Settings::changePort(int otherPort)
{
    QJsonObject connection;
    connection.insert("port_number", otherPort);

    currJsonObject_ = QJsonObject();
    currJsonObject_.insert("connection", connection);
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
        changePort(port_);
        save();
    }
}

void Settings::save()
{
    auto filename = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/config.json";

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
    qDebug() << "Current settings:" << currJsonObject_;
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

    port_ = currJsonObject_.value("connection")["port_number"].toInt();

    jsonFile.close();

    qDebug() << "Current settings:" << currJsonObject_;
}
