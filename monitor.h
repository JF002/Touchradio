#ifndef MONITOR_H
#define MONITOR_H
#include <QObject>
#include <QGuiApplication>

class Monitor: public QObject
{
    Q_OBJECT
public:
    Monitor(const QGuiApplication* app_) : QObject(0)
    {
        this->app = app_;
    }
public slots:
    void exit() {
        app->exit(0);
    }

    void shutdown() {
        app->exit(1);
    }
private:
    const QGuiApplication* app;
};

#endif // MONITOR_H
