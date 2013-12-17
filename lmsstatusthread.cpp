#include "lmsstatusthread.h"

LMSStatusThread::LMSStatusThread(QHostAddress address, int playerId, LmsStatus* status) : QObject()
{
    isRunning = false;
    this->status = status;
    this->address = address;
    this->moveToThread(&thread);

    this->connect(&thread, SIGNAL(started()), SLOT(run()));
}

void LMSStatusThread::Start()
{
     isRunning = true;
     thread.start();
}

void LMSStatusThread::run()
{
    connector.connect(address, 9090);
    connector.BindToPlayer(0);


    while(isRunning)
    {
        QString answer = connector.GetStatus();
        status->Update(answer);
        QThread::msleep(500);
    }
}
