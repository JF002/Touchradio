import QtQuick 2.0

Rectangle {
    id: root
    property int currentVolume
    signal volumeChanged(int volume)

    color: "transparent"

    Rectangle{
        id: progressLine
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        width: 2
        color: "white"
    }

    Rectangle {
        id: progressBall
        anchors.horizontalCenter: progressLine.horizontalCenter
        height: 16
        width: height
        radius: width / 2


        y: progressLine.y + (progressLine.height * ((100-currentVolume)/100))
    }

    MouseArea
    {
        id: mouse
        anchors.fill: progressLine
        anchors.leftMargin: -20
        anchors.rightMargin: -20
        onClicked: {
            root.volumeChanged((((progressLine.height - mouse.y)/progressLine.height)*100 ))
        }
    }
}
