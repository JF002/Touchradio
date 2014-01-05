#ifndef LMSSTATUSTHREAD_H
#define LMSSTATUSTHREAD_H

#include <QObject>
#include <QThread>
#include <QHostAddress>
#include "lmsconnector.h"
#include "lmsstatus.h"

class LmsConnector;
class LmsStatusThread : public QObject
{
    Q_OBJECT
public:
    LmsStatusThread(LmsConnector* connector, LmsStatus* status);
    void Start();

private slots:
    void run();

private:
    bool isRunning;
    LmsConnector* connector;
    LmsStatus* status;
    QThread thread;
};

#endif // LMSSTATUSTHREAD_H
