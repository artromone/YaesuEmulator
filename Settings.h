#ifndef YAESUEMULATOR_SETTINGS_H
#define YAESUEMULATOR_SETTINGS_H
#include <QHostAddress>
#include <QJsonObject>

class Settings
{
public:
    Settings& operator=(Settings &&) = delete;

    static Settings* instance();

    int getPort();
    void setPort(int otherPort);

private:
    void save();
    void load();
    void createDefault();

private:
    int port_{0};
    //QHostAddress address;
};
#endif
