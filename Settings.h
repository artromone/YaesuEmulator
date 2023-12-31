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

    int getAz() const;
    void setAz(int az);

    int getEl() const;
    void setEl(int el);

    bool getAutoConncet() const;
    void setAutoConncet(bool otherConnect);

private:
    void save();
    void load();
    void createDefault();

private:
    int port_{0};
    int az_{0};
    int el_{0};
    bool autoconncet_{false};
};

#endif
