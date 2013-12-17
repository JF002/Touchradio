import QtQuick 2.0

Rectangle {
    id: root
    property alias source: imageButton.source
    signal clicked
    color:"transparent"

    Rectangle {
        id: animRectangle
        anchors.fill: root
        color: "white"
        opacity: 0.5
        visible: mousearea.pressed
    }

    Image {
        id: imageButton
        fillMode: Image.PreserveAspectFit
        anchors.fill: root
    }
    MouseArea {
        id: mousearea
        anchors.fill: root
        onClicked: root.clicked()

    }
}
