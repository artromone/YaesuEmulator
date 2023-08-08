#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>

class Logger : public QObject
{
    Q_OBJECT
public:
    Logger& operator=(Logger &&) = delete;

    static Logger* instance();

    void addLog(const QString& msg, int logType);

signals:
    void logMessage(const QString& logMsg, int logType);
};

#endif
