#ifndef LMSPLAYERCONTROLLER_H
#define LMSPLAYERCONTROLLER_H

#include <QObject>
#include "lmsconnector.h"

class LmsPlayerController : public QObject
{
    Q_OBJECT
public:
    explicit LmsPlayerController(LmsConnector* connector, QObject *parent = 0);

signals:

public slots:
    void play();
    void togglePause();
    void stop();
    void next();
    void previous();

    void setVolume(int volume);

private:
    LmsConnector* connector;
};

#endif // LMSPLAYERCONTROLLER_H
