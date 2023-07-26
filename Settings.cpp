#include "Settings.h"

Settings *Settings::instance()
{
    static Settings * ptrSettings_ = nullptr;
    if (!ptrSettings_)
    {
        ptrSettings_ = new Settings();
    }
    return ptrSettings_;
}

int Settings::getPort() const
{
    return port_;
}

void Settings::setPort(int otherPort)
{
    // if (otherPort != port) save

    port_ = otherPort;
}
