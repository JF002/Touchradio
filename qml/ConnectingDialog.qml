import QtQuick 2.0
import QtQuick.Layouts 1.0

Rectangle {
    id: root
    state: "ENABLED"

    height: 800
    width: 1280

    //property string lmsServerAddress: "0.0.0.0"
/*
    states: [
        State {
            name: "DISABLED"
            PropertyChanges { target: backgroundRectangle; opacity: 0 }
            PropertyChanges { target: foregroundRectangle; opacity: 0}
            PropertyChanges { target: foregroundRectangle; enabled: false}

        },
        State {
            name: "ENABLED"
            PropertyChanges { target: backgroundRectangle; opacity: 0.8}
            PropertyChanges { target: foregroundRectangle; opacity: 1 }
            PropertyChanges { target: foregroundRectangle; enabled: true}
        }
    ]

    transitions: [
        Transition {
            from: "DISABLED"
            to: "ENABLED"
            NumberAnimation { target: backgroundRectangle; property: "opacity"; duration: 500; easing.type: Easing.InOutQuad }
            NumberAnimation { target: foregroundRectangle; property: "opacity"; duration: 500; easing.type: Easing.InOutQuad }

        },
        Transition {
            from: "ENABLED"
            to: "DISABLED"
            NumberAnimation { target: foregroundRectangle; property: "opacity"; duration: 500; easing.type: Easing.InOutQuad }
            NumberAnimation { target: backgroundRectangle; property: "opacity"; duration: 500; easing.type: Easing.InOutQuad }
        }
    ]
    */
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
            text: "Connecting to LMS server ("//+lmsServerAddress+")..."
            font.pixelSize: 30
            color: "white"
            anchors.centerIn: foregroundRectangle
        }

    }
    Loader { // this component performs deferred loading.
            id: mainLoader
    }


    Component.onCompleted:  {
            console.debug("oncompleted")
            //touchradio.Init()
            //mainLoader.source = "main.qml"
        }


}

