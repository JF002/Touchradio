import QtQuick 2.0

Item {
    property int currentTrackTime
    property int currentTrackDuration
    Rectangle{
        id: progressLine
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: 2
        color: "white"
    }

    Rectangle {
        id: progressBall
        anchors.verticalCenter: progressLine.verticalCenter
        height: 16
        width: height
        radius: width / 2


        x: progressLine.x + (progressLine.width * (currentTrackTime/currentTrackDuration))
    }

    Text {
        id: currentTime
        text: getTime(currentTrackTime)
        anchors.bottom: progressLine.top
        anchors.bottomMargin: 5
        anchors.horizontalCenter: progressLine.left
        color: "white"
        font.pixelSize: 20
    }

    Text {
        id: totalTime
        text: getTime(currentTrackDuration)
        anchors.bottom: progressLine.top
        anchors.bottomMargin: 5
        anchors.horizontalCenter: progressLine.right
        color: "white"
        font.pixelSize: 20
    }

    function getTime(totalSeconds) {
       var minutes = Math.floor(totalSeconds / 60)
       var seconds = Math.floor((totalSeconds-minutes*60))

       return padDigits(minutes,2) + ":" +padDigits(seconds,2)
    }

    function padDigits(number, digits) {
        return Array(Math.max(digits - String(number).length + 1, 0)).join(0) + number;
    }
}
