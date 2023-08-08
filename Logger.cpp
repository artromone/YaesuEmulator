#include "Logger.h"

#include <QDateTime>
#include <QDebug>

namespace
{
    QString getCurrTime()
    {
        return QDateTime::currentDateTime().toString("[hh:mm:ss] ");
    }
}

Logger *Logger::instance()
{
    static Logger* ptrLogger = nullptr;
    if (!ptrLogger)
    {
        qDebug() << "Creating new Logger instance.";
        ptrLogger = new Logger();
    }
    return ptrLogger;
}

void Logger::addLog(const QString &msg)
{
    emit this->logMessage(getCurrTime() + msg);
}
