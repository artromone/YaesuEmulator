#ifndef YAESUEMULATOR_SETTINGS_H
#define YAESUEMULATOR_SETTINGS_H
#include <QHostAddress>

class Settings
{
public:
    Settings& operator=(Settings &&) = delete;

    static Settings* instance();

    int getPort() const;
    void setPort(int otherPort);

private:
    int port_ {9999};
    //QHostAddress address;
};
#endif
