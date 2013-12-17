#ifndef LMSSTATUSTHREAD_H
#define LMSSTATUSTHREAD_H

#include <QObject>
#include <QThread>
#include <QHostAddress>
#include "lmsconnector.h"
#include "lmsstatus.h"

class LMSConnector;
class LMSStatusThread : public QObject
{
    Q_OBJECT
public:
    LMSStatusThread(QHostAddress address, int playerId, LmsStatus* status);
    void Start();

private slots:
    void run();

private:
    QHostAddress address;

    bool isRunning;

    LMSConnector connector;
    LmsStatus* status;

    QThread thread;
};

#endif // LMSSTATUSTHREAD_H
