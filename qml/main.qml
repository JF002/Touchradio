import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

Rectangle {
    id: rootRectangle
    width: 1280
    height: 800

    signal shutdownRequest
    signal exitRequest

    state: "PLAYBACK"

    states: [
        State {
            name: "CONNECTING"
            PropertyChanges { target: browserRectangle; state: "DISABLED" }
            PropertyChanges { target: powerOffDialog; state: "DISABLED"}
            PropertyChanges { target: opacifierRectangle; opacity: 0.8}
            PropertyChanges { target: opacifierRectangle; enabled: true }
            //PropertyChanges { target: connectingDialog; state: "ENABLED" }
        },
        State {
            name: "PLAYBACK"
            PropertyChanges { target: browserRectangle; state: "DISABLED" }
            PropertyChanges { target: powerOffDialog; state: "DISABLED"}
            PropertyChanges { target: opacifierRectangle; opacity: 0}
            PropertyChanges { target: opacifierRectangle; enabled: false }
            //PropertyChanges { target: connectingDialog; state: "DISABLED" }

        },
        State {
            name: "BROWSER"

            PropertyChanges { target: browserRectangle; state: "ENABLED"}
            PropertyChanges { target: powerOffDialog; state: "DISABLED"}
            PropertyChanges { target: opacifierRectangle; opacity: 0.8 }
            PropertyChanges { target: opacifierRectangle; enabled: true }
            //PropertyChanges { target: connectingDialog; state: "DISABLED" }
        },
        State {
            name: "POWEROFFDIALOG"
            PropertyChanges { target: powerOffDialog; state: "ENABLED"}
            PropertyChanges { target: browserRectangle; state: "DISABLED" }
            PropertyChanges { target: opacifierRectangle; opacity: 0.8 }
            PropertyChanges { target: opacifierRectangle; enabled: true }
            //PropertyChanges { target: connectingDialog; state: "DISABLED" }
        }
    ]

    transitions: [
        Transition {
            from: "*"
            to: "CONNECTING"
            NumberAnimation { target: opacifierRectangle; property: "opacity"; duration: 500; easing.type: Easing.InOutQuad }
        },
        Transition {
            from: "CONNECTING"
            to: "*"
            NumberAnimation { target: opacifierRectangle; property: "opacity"; duration: 500; easing.type: Easing.InOutQuad }
        },
        Transition {
            from: "PLAYBACK"
            to: "BROWSER"
            NumberAnimation { target: opacifierRectangle; property: "opacity"; duration: 500; easing.type: Easing.InOutQuad }
        },
        Transition {
            from: "BROWSER"
            to: "PLAYBACK"
            NumberAnimation { target: opacifierRectangle; property: "opacity"; duration: 500; easing.type: Easing.InOutQuad }
        },
        Transition {
            from: "PLAYBACK"
            to: "POWEROFFDIALOG"
            NumberAnimation { target: opacifierRectangle; property: "opacity"; duration: 500; easing.type: Easing.InOutQuad }
        },
        Transition {
            from: "POWEROFFDIALOG"
            to: "PLAYBACK"
            NumberAnimation { target: opacifierRectangle; property: "opacity"; duration: 500; easing.type: Easing.InOutQuad }
        }

    ]

    Image {
        id: backgroundImage
        anchors.fill: parent
        source: "../Ressources/background1.jpg"
        fillMode: Image.PreserveAspectCrop
    }

    ImageButton {
        id: volumeButton
        anchors.bottom: rootRectangle.bottom
        anchors.right: rootRectangle.right

        source: "../Ressources/volume3.png"
        height: 128
        width: 128
        anchors.margins: 0

        onClicked: {
            if(volumeRectangle.opacity > 0)
            {
                volumeRectangle.opacity = 0
                volumeRectangle.enabled = false
            }
            else
            {
                volumeRectangle.opacity = 0.8
                volumeRectangle.enabled = true
            }
        }
    }



    ImageButton {
        id: menuButton
        anchors.bottom: rootRectangle.bottom
        anchors.left: rootRectangle.left

        source: "../Ressources/menu3.png"
        height: 128
        width: 128
        anchors.margins: 0
        onClicked: {
            if(rootRectangle.state == "PLAYBACK")
                rootRectangle.state = "BROWSER"
            else
                rootRectangle.state = "PLAYBACK"
        }
    }

    Item
    {
        id: toolbar
        height: 50
        anchors.top: rootRectangle.top
        anchors.left: rootRectangle.left
        anchors.right: rootRectangle.right

        Rectangle {
            anchors.fill: parent
            color: "transparent"
            opacity: 0.2
        }

        Timer {
            interval: 1000
            running: true
            repeat: true
            onTriggered: {
                clock.update()
            }
        }

        Text{
            id: clock
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: powerButton.left
            anchors.rightMargin: 20
            text : (Qt.formatDateTime(new Date(), "h:mm - dd/MM"))
            font.pixelSize: 40
            color: "white"

            function getCurrentTime()
            {
                return (Qt.formatDateTime(new Date(), "h:mm - dd/MM"));
            }

            function update()
            {
                clock.text = clock.getCurrentTime();
            }
        }

        ImageButton {
            id: powerButton
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right

            source: "../Ressources/on_off.png"
            height: parent.height
            width: height
            onClicked: {
                if(rootRectangle.state != "POWEROFFDIALOG")
                    rootRectangle.state = "POWEROFFDIALOG"
                else
                    rootRectangle.state = "PLAYBACK"
            }
        }
    }

    Rectangle
    {
        id: coverRectangle
        anchors.horizontalCenter: rootRectangle.horizontalCenter
        y: (rootRectangle.height/3) - 200
        height: 400
        width: 400
        border.width: 4
        border.color: "white"
        radius: 6


        Image {
            id: coverImage
            source: statusManager.currentTrackCoverUrl
            anchors.fill: parent
            anchors.margins: 4
            fillMode: Image.PreserveAspectFit
        }
    }


    ColumnLayout{
        id: infoColumn

        anchors.top: coverRectangle.bottom
        anchors.topMargin: 30
        anchors.left: coverRectangle.left
        anchors.right: coverRectangle.right


        Text{
            Layout.fillWidth: true
            text: statusManager.currentTrackArtist.toLocaleUpperCase()
            color: "white"
            font.pixelSize: 40
            horizontalAlignment: Text.AlignHCenter
        }

        Text{
            Layout.fillWidth: true
            text: statusManager.currentTrackAlbum
            color: "white"
            font.pixelSize: 30
            horizontalAlignment: Text.AlignHCenter
        }

        Text{
            Layout.fillWidth: true
            text: "\"" + statusManager.currentTrackTitle + "\""
            color: "white"
            font.pixelSize: 25
            horizontalAlignment: Text.AlignHCenter
        }
    }



    Item
    {
        id: controlRectangle
        anchors.horizontalCenter: rootRectangle.horizontalCenter
        width: rootRectangle.width * 0.75
        anchors.top: infoColumn.bottom
        anchors.bottom: rootRectangle.bottom
        anchors.topMargin: 30

        TrackProgressBar
        {
            id: trackprogressBar
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top

            currentTrackDuration: statusManager.currentTrackDuration
            currentTrackTime: statusManager.currentTrackTime
        }

        RowLayout
        {
            id: controlButtonsRectangle
            anchors.top : trackprogressBar.bottom
            anchors.topMargin: 30
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 50
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width / 3

            ImageButton {
                Layout.fillHeight: true
                Layout.fillWidth: true
                source: "../Ressources/video_previous_64.png"
                height: 64
                onClicked: {
                    playerController.previous()
                }
            }

            ImageButton {
                Layout.fillHeight: true
                Layout.fillWidth: true
                source: {
                    if(statusManager.mode == "pause")
                        return "../Ressources/video_pause_64.png"
                    else
                        return "../Ressources/video_play_64.png"
                }

                height: 64
                onClicked: {
                    console.log("play")
                    playerController.togglePause()
                }
            }

            ImageButton {
                Layout.fillHeight: true
                Layout.fillWidth: true
                source: "../Ressources/video_next_64.png"
                height: 64
                onClicked: {
                    console.log("next")
                    playerController.next()
                }
            }
        }
    }

    Rectangle {
        id: opacifierRectangle
        anchors.fill: rootRectangle
        color: "black"
        opacity: 0
        enabled: false
    }

    LibraryBrowser {
        id: browserRectangle
        anchors.centerIn: rootRectangle
        width: rootRectangle.width*0.85
        height: rootRectangle.height*0.85
        model: ressourceModel
        onCloseRequest: rootRectangle.state = "PLAYBACK"
    }

    PowerOffDialog {
        id: powerOffDialog
        height: rootRectangle.height / 4
        width: rootRectangle.width / 4
        anchors.centerIn: rootRectangle
        state: "DISABLED"
        onExitClicked: {
            touchradio.exit()
        }
        onShutdownClicked:{
            touchradio.shutdown()
        }
        onCancelClicked: {
            rootRectangle.state = "PLAYBACK"
        }
    }

    Rectangle {
        id: volumeRectangle
        color: "transparent"
        opacity: 0

        anchors.right: volumeButton.right
        anchors.bottom: volumeButton.bottom
        width: volumeButton.width
        height: volumeButton.height + volumeBar.height

        Behavior on opacity {
            NumberAnimation { target: volumeRectangle; property: "opacity"; duration: 500; easing.type: Easing.InOutQuad; }
        }

        Rectangle {
            id: volumeBgRectangle
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            height: volumeButton.height
            color: "white"
            opacity: 0.8
        }

        Rectangle {
            id: volumeFgRectangle
            anchors.right: volumeBgRectangle.right
            anchors.bottom: volumeBgRectangle.top
            anchors.left: volumeBgRectangle.left
            width: 170
            height: 250
            color: "white"
            opacity: 0.8
        }

        VolumeBar {
            id: volumeBar
            anchors.top: volumeFgRectangle.top
            anchors.bottom: volumeFgRectangle.bottom
            anchors.horizontalCenter: volumeFgRectangle.horizontalCenter
            currentVolume: statusManager.mixer_volume
            onVolumeChanged: playerController.setVolume(volume)
        }
    }




}
