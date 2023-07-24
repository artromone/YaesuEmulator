#include "Settings.h"

Settings::Settings() : address(QHostAddress("127.0.0.1")), port(9999)
{
}

Settings::~Settings()
{
    // QHostAddress::clear();
}
