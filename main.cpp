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
#include <QDir>
#include "monitor.h"
#include "applicationsettings.h"

int main(int argc, char *argv[])
{
    /*
     *player_name:SoftSqueeze player_connected:1 player_ip:192.168.0.2:62698
     *      power:1 signalstrength:0 mode:play remote:1 current_title: - Lazy Bones
     *      time:2209.14036511421 rate:1 mixer volume:73 playlist repeat:0 playlist
     *      shuffle:0 playlist mode:off seq_no:0 playlist_cur_index:0 playlist_timestamp:1387747708.53505
     *      playlist_tracks:1 remoteMeta:HASH(0x47838c0) playlist index:0 id:-73516576 title:Lazy Bones
     *      coverid:-73516576
     **/
/*
    QString response = " player_name:SoftSqueeze player_connected:1 player_ip:192.168.0.2:62698 power:1 signalstrength:0 mode:play remote:1 current_title: - Lazy Bones time:2209.14036511421 rate:1 mixer volume:73 playlist repeat:0 playlist shuffle:0 playlist mode:off seq_no:0 playlist_cur_index:0 playlist_timestamp:1387747708.53505  playlist_tracks:1 remoteMeta:HASH(0x47838c0) playlist index:0 id:-73516576 title:Lazy Bones coverid:-73516576";
    QList<QString> knownKeys;
    knownKeys.append("player_name");
    knownKeys.append("player_connected");
    knownKeys.append("mode");
    knownKeys.append("playlist index");
    knownKeys.append("title");
    knownKeys.append("azertyuiop");


    QString currentKey;
    QMap<QString, QString> values;
    foreach(currentKey, knownKeys)
    {
        int keyIndex = response.indexOf(" " + currentKey, 0, Qt::CaseSensitive);
        if(keyIndex == -1)
            continue;

        keyIndex+=currentKey.count()+2;

        int nextIndex = response.indexOf(":", keyIndex);
        nextIndex = response.lastIndexOf(" ", nextIndex);

        QString token = response.mid(keyIndex, nextIndex- keyIndex);
        values[currentKey] = token;
    }

    qDebug() << values;

*/


    QGuiApplication app(argc, argv);
    ApplicationSettings settings;
    QQuickView viewer;
    LMSConnector connector;
    LMSConnector statusConnector;
    LmsStatus status;
    bool connected;

    connected = connector.connect(settings.GetLmsAddress(), settings.GetLmsPort());
    if(!connected)
    {
        qDebug() << "Cannot connector to " << settings.GetLmsAddress() << ":" << QString::number(settings.GetLmsPort());
        return -1;
    }
    connected = statusConnector.connect(settings.GetLmsAddress(), settings.GetLmsPort());
    if(!connected)
    {
        qDebug() << "Cannot connector to " << settings.GetLmsAddress() << ":" << QString::number(settings.GetLmsPort());
        return -1;
    }

    connector.BindToPlayer(0);
    statusConnector.BindToPlayer(0);


    LMSStatusThread statusManager(&statusConnector, &status);
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

    QDir directory(QCoreApplication::applicationDirPath());
    QString path = directory.absoluteFilePath("qml/main.qml");

    viewer.setSource(QUrl::fromLocalFile(path));
    QObject::connect((QObject*)viewer.engine(), SIGNAL(quit()), &app, SLOT(quit()));

    QObject *item = (QObject*)viewer.rootObject();

    Monitor monitor(&app);
    QObject::connect(item, SIGNAL(exitRequest()),&monitor, SLOT(exit()));
    QObject::connect(item, SIGNAL(shutdownRequest()),&monitor, SLOT(shutdown()));

    viewer.show();
    return app.exec();

}


