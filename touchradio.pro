# Add more folders to ship with the application, here
folder_01.source = qml
folder_02.source = Ressources
folder_03.source = conf


CONFIG(debug, debug|release) {
    folder_01.target = $$DESTDIR/debug
    folder_02.target = $$DESTDIR/debug
    folder_03.target = $$DESTDIR/debug
} else {
    folder_01.target = $$DESTDIR/release
    folder_02.target = $$DESTDIR/release
    folder_03.target = $$DESTDIR/release
}


DEPLOYMENTFOLDERS = folder_01
DEPLOYMENTFOLDERS += folder_02
DEPLOYMENTFOLDERS += folder_03

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    RessourceItem.cpp \
    RessourceCenterModel.cpp \
    lmsconnector.cpp \
    artistitem.cpp \
    albumitem.cpp \
    trackitem.cpp \
    lmsstatus.cpp \
    lmsstatusthread.cpp \
    favoriteitem.cpp \
    lmsplayercontroller.cpp \
    monitor.cpp \
    applicationsettings.cpp \
    Exceptions/exception.cpp \
    Exceptions/timeoutexception.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    RessourceItem.h \
    RessourceCenterModel.h \
    lmsconnector.h \
    artistitem.h \
    albumitem.h \
    trackitem.h \
    lmsstatus.h \
    lmsstatusthread.h \
    favoriteitem.h \
    lmsplayercontroller.h \
    monitor.h \
    applicationsettings.h \
    Exceptions/exception.h \
    Exceptions/timeoutexception.h

RESOURCES += \
    ressources.qrc

OTHER_FILES += \
    qml/VolumeBar.qml \
    qml/TrackProgressBar.qml \
    qml/TextButton.qml \
    qml/PowerOffDialog.qml \
    qml/main.qml \
    qml/LibraryItemDelegate.qml \
    qml/LibraryBrowserInfo.qml \
    qml/LibraryBrowser.qml \
    qml/ImageButton.qml
