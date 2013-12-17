import QtQuick 2.0
import QtQuick.Layouts 1.0

Item {
    id: root
    signal exitClicked
    signal shutdownClicked
    signal cancelClicked
    state: "DISABLED"

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

    Rectangle {
        id: backgroundRectangle
        anchors.fill: parent
        color: "white"
        opacity: 0.8
    }

    Rectangle {
        id: foregroundRectangle
        anchors.fill: parent
        color: "transparent"
        opacity: 1

        ColumnLayout{
            spacing:0
            anchors.fill: parent
            TextButton {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "Exit"
                border.color:  "transparent"
                onClicked: root.exitClicked()
            }
            Rectangle {
                color: "white"
                height: 2
                Layout.fillWidth: true
            }

            TextButton {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "Shutdown"
                border.color:  "transparent"
                onClicked: root.shutdownClicked()
            }
            Rectangle {
                color: "white"
                height: 2
                Layout.fillWidth: true
            }
            TextButton {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "Cancel"
                border.color: "transparent"
                onClicked: root.cancelClicked()

            }

        }

    }



}
