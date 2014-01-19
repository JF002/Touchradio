#include <QtGui/QGuiApplication>
#include <QQmlEngine>
#include <QQmlContext>
#include "qtquick2applicationviewer.h"
#include "ressourceItem.h"
#include "lmsplayercontroller.h"
#include "RessourceCenterModel.h"
#include "lmsconnector.h"
#include "lmsstatusthread.h"
#include "artistitem.h"
#include "favoriteitem.h"
#include "trackitem.h"
#include <QHostAddress>
#include <QDebug>
#include <QDir>
#include "applicationsettings.h"
#include "touchradio.h"
#include <QQmlComponent>
#include <QQuickItem>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    Touchradio touchradio;

    touchradio.Start(&app);
    return app.exec();
}

