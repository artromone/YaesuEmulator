#ifndef YAESUEMULATOR_SETTINGS_H
#define YAESUEMULATOR_SETTINGS_H
#include <QHostAddress>

struct Settings
{
    QHostAddress address;
    int port {9999};
    Settings();
    ~Settings();
};
#endif
