#include <QtGui/QGuiApplication>
#include <QQmlEngine>
#include <QQmlContext>
#include "qtquick2applicationviewer.h"
#include "RessourceItem.h"
#include "lmsplayercontroller.h"
#include "RessourceCenterModel.h"
#include "lmsconnector.h"
#include "lmsstatusthread.h"
#include "artistitem.h"
#include "favoriteitem.h"
#include <QHostAddress>
#include <QDebug>
#include "monitor.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickView viewer;

    LMSConnector connector;
    connector.connect(QHostAddress("192.168.0.7"), 9090);
    connector.BindToPlayer(0);

    LmsStatus status;
    LMSStatusThread statusManager(QHostAddress("192.168.0.7"), 0, &status);
    statusManager.Start();

    LmsPlayerController playerController(&connector);

    QList<ArtistItem*> artistCollection = connector.GetArtistCollection();
    QList<FavoriteItem*> favoriteCollection = connector.GetFavoriteCollection();

    RessourceItem rootItem("Home");
    RessourceItem libraryItem("Library");
    RessourceItem favoritesItem("Favorites");
    RessourceItem playlistsItem("PlayLists");

    for(int i = 0; i < artistCollection.count(); i++)
    {
        libraryItem.AddItem(artistCollection[i]);
    }

    for(int i = 0; i < favoriteCollection.count(); i++)
    {
        favoritesItem.AddItem(favoriteCollection[i]);
    }
    rootItem.AddItem(&libraryItem);
    rootItem.AddItem(&favoritesItem);
    rootItem.AddItem(&playlistsItem);


    QObjectListModel rootModel;
    rootModel.append(&libraryItem);
    rootModel.append(&favoritesItem);
    rootModel.append(&playlistsItem);

    viewer.engine()->rootContext()->setContextProperty("ressourceModel", &rootModel);
    viewer.engine()->rootContext()->setContextProperty("statusManager", &status);
    viewer.engine()->rootContext()->setContextProperty("playerController", &playerController);

    viewer.setSource(QUrl("qml/qml/main.qml"));
    QObject::connect((QObject*)viewer.engine(), SIGNAL(quit()), &app, SLOT(quit()));

    QObject *item = (QObject*)viewer.rootObject();

    Monitor monitor(&app);
    QObject::connect(item, SIGNAL(exitRequest()),&monitor, SLOT(exit()));
    QObject::connect(item, SIGNAL(shutdownRequest()),&monitor, SLOT(shutdown()));

    viewer.show();
    return app.exec();
}


