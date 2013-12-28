#include "applicationsettings.h"
#include <QCoreApplication>
#include <QDir>

ApplicationSettings::ApplicationSettings()
{
    QDir directory(QCoreApplication::applicationDirPath());
    QString path = directory.absoluteFilePath("conf/touchradio.conf");
    settings = new QSettings(path, QSettings::IniFormat);
}

ApplicationSettings::~ApplicationSettings()
{
    free(settings);
}


QHostAddress ApplicationSettings::GetLmsAddress()
{
    return QHostAddress(settings->value("LMS/Address", "127.0.0.1").toString());
}

int ApplicationSettings::GetLmsPort()
{
     return  settings->value("LMS/Port", 9090).toInt();
}
