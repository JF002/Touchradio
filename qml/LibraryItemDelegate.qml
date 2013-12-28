import QtQuick 2.1

Item {
    id: root
    width: parent.width
    height: 60

    property alias text: textitem.text
    property alias cover: icon.source
    signal clicked

    Rectangle {
        anchors.fill: parent
        color: "#CCffffff"
        visible: mouse.pressed
    }


    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 15
        height: 1
        color: "#424246"
    }

    Image
    {
        id: icon
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 30

        source: "../Ressources/disk_48.png"
        fillMode: Image.PreserveAspectFit
        width: 30
        height: parent.height - 15
    }

    Text {
        id: textitem
        color: "black"
        font.pixelSize: 20
        text: modelData
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: icon.right
        anchors.right: parent.right
        anchors.leftMargin: 10
        wrapMode: Text.Wrap
    }

    MouseArea {
        id: mouse
        anchors.fill: parent
        onClicked: root.clicked()

    }
}
