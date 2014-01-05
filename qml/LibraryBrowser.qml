import QtQuick 2.0

Item {
    id: root
    property alias model: listview.model

    signal closeRequest()

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

        Rectangle {
            id: toolBar

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: {
                if(parent.height > 50)
                {
                    backButton.visible = true
                    topRectangleText.visible = true
                    return 50
                }
                else
                {
                    backButton.visible = false
                    topRectangleText.visible = false
                    return 0
                }
            }



            Rectangle {
                id: backButton
                width: opacity ? 60 : 0
                anchors.left: parent.left
                anchors.margins: 10
                anchors.verticalCenter: parent.verticalCenter
                antialiasing: true
                height: 40
                radius: 4
                color: backmouse.pressed ? "#222" : "transparent"
                Behavior on opacity { NumberAnimation{} }
                Image
                {
                    id: backImage

                    fillMode: Image.PreserveAspectFit
                    source: "../Ressources/arrow_left_64.png"
                    anchors.fill: parent
                }
                MouseArea {
                    id: backmouse
                    anchors.fill: parent
                    anchors.margins: -10
                    onClicked: listview.model.back();
                }
            }

            Text
            {
                id: topRectangleText
                anchors.verticalCenter: parent.verticalCenter
                text: ressourceModel.currentItemName
                color: "#B9B9B9"
                font.pixelSize: 32
                Behavior on x { NumberAnimation{ easing.type: Easing.OutCubic} }
                x: backButton.x + backButton.width + 20
            }

            ImageButton {
                source: "../Ressources/close.png"
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                width: height
                onClicked: root.closeRequest();
            }
        }


        ListView {
            id: listview
            anchors.top: toolBar.bottom
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            width: parent.width/2

            clip: true
            delegate: LibraryItemDelegate {
                text: object.title
                cover: (object.coverUrl)?object.coverUrl:"../Ressources/disk_48.png"
                onClicked:
                {
                    if(object.type == 3)
                    {
                        infoRectangle.track = object
                    }
                    else if(object.type == 2)
                    {
                        infoRectangle.album = object
                        listview.model.goToSubItems(object.id);
                        listview.positionViewAtBeginning();
                    }
                    else if(object.type == 4)
                    {
                        infoRectangle.favorite = object
                    }
                    else
                    {
                        listview.model.goToSubItems(object.id);
                        listview.positionViewAtBeginning();
                    }
                }
            }
            opacity:0.9
        }

        LibraryBrowserInfo{
            id: infoRectangle
            anchors.top: toolBar.bottom
            anchors.left: listview.right
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            onTrackSelected: {
                infoRectangle.track.Play();
                root.closeRequest();
            }
            onFavoriteSelected: {
                infoRectangle.favorite.Play();
                root.closeRequest();
            }
            onAlbumSelected: {
                infoRectangle.album.Play()
                root.closeRequest();
            }
        }
    }
}
