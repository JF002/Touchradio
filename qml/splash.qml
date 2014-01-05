import QtQuick 2.0

/*Splash screen. This QML file is displayed as soon as possible when the application is
  starting in order to guve feedback to the user. Then, the method Touchradio::Init() is
  called, and the main QML file is loaded and will be displayed when the init is done.
  Thanks to http://qt-project.org/forums/viewthread/36745/
  */

Item {
    width: 1280
    height: 800

    // This item is the item that will be dislplayed as the splash screen
    Rectangle {
        id: backgroundRectangle
        anchors.fill: parent
        color: "black"
    }

    Rectangle {
        id: foregroundRectangle
        anchors.centerIn: parent
        color: "black"
        width: parent.width/2
        height: parent.height/4

        Text {
            text: "Connecting to LMS server (" +lmsServerAddress+")..."
            font.pixelSize: 30
            color: "white"
            anchors.centerIn: foregroundRectangle
        }

    }

    // This is the Loader that will load the main.qml file
    Loader {
        id: main
        anchors.fill: parent
        asynchronous: true
        visible: status == Loader.Ready
    }

    // This is a fake delay needed to give to QML the necessary time
    // to load and setup the splash item above
    PauseAnimation {
        id: fakeLoadingDelay
        duration: 50
        onRunningChanged: {
            if ( !running ) {
                touchradio.init();
                main.source = "main.qml"
            }
        }
    }

    // This start the animation and loading of mail.qml when the component is ready
    Component.onCompleted: fakeLoadingDelay.start()
}
