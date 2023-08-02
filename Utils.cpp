#include "Utils.h"

#include <QDateTime>

QString getCurrtime()
{
    return QDateTime::currentDateTime().toString("hh:mm");
}
