#ifndef TOUCHRADIO_H
#define TOUCHRADIO_H
#include <QObject>
#include <QGuiApplication>
#include <QThread>
#include "applicationsettings.h"
#include <QQuickView>
#include "lmsconnector.h"
#include "lmsstatus.h"
#include "lmsplayercontroller.h"
#include "RessourceCenterModel.h"
#include "monitor.h"

class TouchradioWorkers;
class Touchradio  : public QObject
{
    Q_OBJECT
public:
    Touchradio();
    int Start(QGuiApplication* app);
    ~Touchradio();



public slots:
    int init();

private:
    QGuiApplication* app;
    QThread* startThread;
    ApplicationSettings* settings;
    QQuickView* viewer;
    LmsConnector* connector;
    LmsConnector* statusConnector;
    LmsStatus* status;
    LmsStatusThread* statusManager;
    LmsPlayerController* playerController;
    QObjectListModel* rootModel;
    Monitor* monitor;

    // Todo The creation of RessourceItems should be reviewed...
    RessourceItem* rootItem;
    RessourceItem* libraryItem;
    RessourceItem* favoritesItem;
    RessourceItem* playlistsItem;

};

#endif // TOUCHRADIO_H
