#include "touchradio.h"
#include <QGuiApplication>
#include <QQuickView>
#include "lmsconnector.h"
#include "lmsstatus.h"
#include "applicationsettings.h"
#include "lmsstatusthread.h"
#include "lmsplayercontroller.h"
#include "ressourceItem.h"
#include "trackitem.h"
#include "albumitem.h"
#include "favoriteitem.h"
#include "artistitem.h"
#include "simpleitem.h"
#include "RessourceCenterModel.h"
#include <QQmlEngine>
#include <QQmlContext>
#include <QDir>

Touchradio::Touchradio() : QObject()
{
    startThread = new QThread();
    settings = new ApplicationSettings();
    connector = new LmsConnector();
    statusConnector = new LmsConnector();
    status = new LmsStatus();
    statusManager = NULL;
    playerController = NULL;
    rootModel = new QObjectListModel();
    viewer = new QQuickView();
}

Touchradio::~Touchradio()
{
    if(statusManager != NULL)
        delete statusManager;
    if(playerController != NULL)
        delete playerController;
    delete viewer;
    delete connector;
    delete statusConnector;
    delete status;
    delete settings;
    delete startThread;
    delete rootModel;
}

int Touchradio::Start(QGuiApplication* app)
{
    qDebug() << "Start " + QString::number((int)QThread::currentThreadId());
    this->app = app;

    QString lmsAddress = settings->GetLmsAddress().toString() + ":" + QString::number(settings->GetLmsPort());
    QDir directory(QCoreApplication::applicationDirPath());
    QString path = directory.absoluteFilePath("qml/splash.qml");
    viewer->engine()->rootContext()->setContextProperty("touchradio", this);
    viewer->engine()->rootContext()->setContextProperty("lmsServerAddress", lmsAddress);

    viewer->setSource(QUrl::fromLocalFile(path));
    viewer->show();

    return 0;
}

int Touchradio::init()
{
    bool connected;
    connected = connector->connect(settings->GetLmsAddress(), settings->GetLmsPort());
    if(!connected)
    {
        qDebug() << "Cannot connector to " << settings->GetLmsAddress() << ":" << QString::number(settings->GetLmsPort());
        return 1;
    }

    // TODO this socket/connector is initialised and connected in the main thread
    // then moved to the status thread. It will be closed in the status thread.
    // This does not seems very good...
    connected = statusConnector->connect(settings->GetLmsAddress(), settings->GetLmsPort());
    if(!connected)
    {
        qDebug() << "Cannot connector to " << settings->GetLmsAddress() << ":" << QString::number(settings->GetLmsPort());
        return 1;
    }

    connector->BindToPlayer(0);
    statusConnector->BindToPlayer(0);

    statusManager = new LmsStatusThread(statusConnector, status);
    statusManager->Start();

    playerController = new LmsPlayerController(connector);

    // TODO free memory from RessourceItems in these list or in the model
    QList<ArtistItem*> artistCollection = connector->GetArtistCollection();
    QList<FavoriteItem*> favoriteCollection = connector->GetFavoriteCollection();

    rootItem = new SimpleItem("Home");
    libraryItem = new SimpleItem("Library");
    favoritesItem = new SimpleItem("Favorites");
    playlistsItem = new SimpleItem("PlayLists");

    for(int i = 0; i < artistCollection.count(); i++)
    {
        libraryItem->AddItem(artistCollection[i]);
    }

    for(int i = 0; i < favoriteCollection.count(); i++)
    {
        favoritesItem->AddItem(favoriteCollection[i]);
    }
    rootItem->AddItem(libraryItem);
    rootItem->AddItem(favoritesItem);
    rootItem->AddItem(playlistsItem);

    rootModel->append(libraryItem);
    rootModel->append(favoritesItem);
    rootModel->append(playlistsItem);

    viewer->engine()->rootContext()->setContextProperty("ressourceModel", rootModel);
    viewer->engine()->rootContext()->setContextProperty("statusManager", status);
    viewer->engine()->rootContext()->setContextProperty("playerController", playerController);

    QObject::connect((QObject*)viewer->engine(), SIGNAL(quit()), this, SLOT(exit()));
    QObject::connect(app, SIGNAL(aboutToQuit()), this, SLOT(exit()));

    return 0;
}

void Touchradio::Stop()
{
    statusManager->Stop();
    connector->Close();
}

void Touchradio::exit() {
    this->Stop();
    this->app->exit(0);
}

void Touchradio::shutdown() {
    this->Stop();
    this->app->exit(1);
}
