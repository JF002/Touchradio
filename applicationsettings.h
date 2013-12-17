#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H
#include <QSettings>
#include <QHostAddress>

class ApplicationSettings
{
public:
    ApplicationSettings();
    ~ApplicationSettings();

    QHostAddress GetLmsAddress();
    int GetLmsPort();

private:
    QSettings* settings;
};

#endif // APPLICATIONSETTINGS_H
