#include "lmsstatusthread.h"

LmsStatusThread::LmsStatusThread(LmsConnector* connector, LmsStatus* status) : QObject()
{
    this->connector = connector;
    this->status = status;
    this->status->SetLmsAddress(connector->GetLmsAddress());
    this->moveToThread(&thread);
    connector->moveToThread(&thread);
    this->connect(&thread, SIGNAL(started()), SLOT(run()));
}

void LmsStatusThread::Start()
{
     isRunning = true;
     thread.start();
}

void LmsStatusThread::run()
{
    while(isRunning)
    {
        QString answer = connector->GetStatus();
        status->Update(answer);
        QThread::msleep(500);
    }
    connector->Close();
    thread.quit();
}

void LmsStatusThread::Stop()
{
    isRunning = false;
    thread.wait();
}
