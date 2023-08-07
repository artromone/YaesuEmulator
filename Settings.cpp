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
    az_ = 50;
    el_ = 50;
    autoconncet_ = false;
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

bool Settings::getAutoConncet() const
{
    return autoconncet_;
}

void Settings::setAutoConncet(bool otherConnect)
{
    qDebug() << "auto:" << autoconncet_ << "other auto:" << otherConnect;
    if (autoconncet_ != otherConnect)
    {
        autoconncet_ = otherConnect;
        save();
    }
}

int Settings::getEl() const
{
    return el_;
}
void Settings::setEl(int el)
{
    qDebug() << "el:" << el_ << "other el:" << el;
    if (el_ != el)
    {
        el_ = el;
        save();
    }
}

int Settings::getAz() const
{
    return az_;
}
void Settings::setAz(int az)
{
    qDebug() << "az:" << az_ << "other az:" << az;
    if (az_ != az)
    {
        az_ = az;
        save();
    }
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
    connection.insert("az", az_);
    connection.insert("el", el_);
    connection.insert("auto_connect", autoconncet_);

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
    az_ = currJsonObject.value("connection")["az"].toInt();
    el_ = currJsonObject.value("connection")["el"].toInt();
    autoconncet_ = currJsonObject.value("connection")["auto_connect"].toBool();

    jsonFile.close();

    qDebug() << "Current settings:" << currJsonObject;
}
