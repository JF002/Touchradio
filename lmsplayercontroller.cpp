#include "lmsplayercontroller.h"
#include <QDebug>

LmsPlayerController::LmsPlayerController(LmsConnector* connector, QObject *parent) :
    QObject(parent)
{
    this->connector = connector;
}

void LmsPlayerController::play()
{
    connector->Play();
}

void LmsPlayerController::togglePause()
{
    connector->TogglePause();
}

void LmsPlayerController::stop()
{
    connector->Stop();
}

void LmsPlayerController::next()
{
    connector->Next();
}

void LmsPlayerController::previous()
{
    connector->Previous();
}

void LmsPlayerController::setVolume(int volume)
{
    connector->SetVolume(volume);
}

