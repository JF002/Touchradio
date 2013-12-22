#include "lmsstatusthread.h"

LMSStatusThread::LMSStatusThread(LMSConnector* connector, LmsStatus* status) : QObject()
{
    this->connector = connector;
    this->status = status;
    this->moveToThread(&thread);
    connector->moveToThread(&thread);
    this->connect(&thread, SIGNAL(started()), SLOT(run()));
}

void LMSStatusThread::Start()
{
     isRunning = true;
     thread.start();
}

void LMSStatusThread::run()
{
    while(isRunning)
    {
        QString answer = connector->GetStatus();
        status->Update(answer);
        QThread::msleep(500);
    }
}
