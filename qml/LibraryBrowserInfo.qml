import QtQuick 2.0

Rectangle {
    id: infoRectangle
    property var track
    property var album
    property var favorite

    signal trackSelected(int trackId)
    signal albumSelected(int albumId)
    signal favoriteSelected(int favoriteId)

    state: "NONE"

    states: [
        State {
            name: "NONE"
            PropertyChanges {target: infoNone; visible: true}
            PropertyChanges { target: infoTrack; visible: false }
            PropertyChanges { target: infoAlbum; visible: false }
            PropertyChanges { target: infoFavorite; visible: false }

        },
        State {
            name: "TRACK"
            PropertyChanges {target: infoNone; visible: false}
            PropertyChanges { target: infoTrack; visible: true}
            PropertyChanges { target: infoAlbum; visible: false }
            PropertyChanges { target: infoFavorite; visible: false }
        },
        State {
            name: "ALBUM"
            PropertyChanges {target: infoNone; visible: false}
            PropertyChanges { target: infoTrack; visible: false}
            PropertyChanges { target: infoAlbum; visible: true }
            PropertyChanges { target: infoFavorite; visible: false }
        },
        State {
            name: "FAVORITE"
            PropertyChanges {target: infoNone; visible: false}
            PropertyChanges { target: infoTrack; visible: false}
            PropertyChanges { target: infoAlbum; visible: false }
            PropertyChanges { target: infoFavorite; visible: true }
        }

    ]

    color: "transparent"
    onVisibleChanged: {
        infoText.visible = infoRectangle.visible
    }

    onTrackChanged: {
        state = "TRACK"
    }

    onAlbumChanged: {
        state = "ALBUM"
    }

    onFavoriteChanged: {
        state = "FAVORITE"
    }


    Item {
        id: infoNone
        anchors.fill: parent
        Text {
            anchors.centerIn: parent
            text: "Select an item to display its information"
        }
    }

    Item {
        id: infoFavorite
        anchors.fill: parent
        visible: false

        Image {
            id: favoriteCoverImage
            source: favorite!=null?favorite.coverUrl:""
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 20

            height: parent.height/4
            width: height
            fillMode: Image.PreserveAspectFit
        }

        Rectangle
        {
            id: favoriteTitleTextRectangle
            anchors.horizontalCenter: infoFavorite.horizontalCenter
            anchors.top: favoriteCoverImage.bottom
            width: infoFavorite.width
            height: 50
            color:"transparent"
            Text {
                id: favoriteTitleText
                text: favorite!=null?favorite.title:""
                font.pixelSize: 40
                anchors.horizontalCenter: favoriteTitleTextRectangle.horizontalCenter
                anchors.verticalCenter: favoriteTitleTextRectangle.verticalCenter
            }
        }

        Text
        {
            id: favorriteInfoText
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: favoriteTitleTextRectangle.bottom
            anchors.leftMargin: 100
            width: parent.width - 100
            clip: true
            text: "URL: " + (favorite!=null?favorite.url:"")
            font.pixelSize: 20
        }

        Rectangle {
            anchors.top: favorriteInfoText.bottom
            anchors.leftMargin: 100
            anchors.topMargin: 100
            width: parent.width - 100
            anchors.horizontalCenter: parent.horizontalCenter

            color: "transparent"

            TextButton {
                id: favoritePlayButton
                text: "Play"
                width: parent.width
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                onClicked: infoRectangle.favoriteSelected(favorite.id)
            }
        }
    }

    Item {
        id: infoAlbum
        anchors.fill: parent
        visible: false

        Image {
            id: albumCoverImage
            source: album!=null?album.coverUrl:""
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 20

            height: parent.height/4
            width: height
            fillMode: Image.PreserveAspectFit
        }

        Rectangle
        {
            id: titleTextRectangle
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: albumCoverImage.bottom
            width: infoRectangle.width
            height: 50
            color:"transparent"
            Text {
                id: titleText
                text: album!=null?album.albumTitle:""
                font.pixelSize: 40
                anchors.horizontalCenter: titleTextRectangle.horizontalCenter
                anchors.verticalCenter: titleTextRectangle.verticalCenter
            }
        }

        Text
        {
            id: infoText
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: titleTextRectangle.bottom
            anchors.leftMargin: 100
            width: parent.width - 100

            text: album!=null?("Artist: " + album.artist + "\nYear: " + album.year):""
            font.pixelSize: 20
        }

        Rectangle {
            anchors.top: infoText.bottom
            anchors.leftMargin: 100
            anchors.topMargin: 100
            width: parent.width - 100
            anchors.horizontalCenter: parent.horizontalCenter

            color: "transparent"

            TextButton {
                id: playButton
                text: "Play album"
                width: parent.width
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                onClicked: infoRectangle.albumSelected(album.id)
            }
        }
    }

    Item {
        id: infoTrack
        anchors.fill: parent
        visible: false

        Image {
            id: coverImage
            source: track!=null?track.coverUrl:""
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 20

            height: parent.height/4
            width: height
            fillMode: Image.PreserveAspectFit
        }

        Rectangle
        {
            id: trackTitleTextRectangle
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: coverImage.bottom
            width: infoRectangle.width
            height: 50
            color:"transparent"
            Text {
                id: trackTtitleText
                text: track!=null?track.trackTitle:""
                font.pixelSize: 40
                anchors.horizontalCenter: trackTitleTextRectangle.horizontalCenter
                anchors.verticalCenter: trackTitleTextRectangle.verticalCenter
            }
        }

        Text
        {
            id: trackInfoText
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: trackTitleTextRectangle.bottom
            anchors.leftMargin: 100
            width: parent.width - 100

            text: track!=null?("Artist: " + track.artistName + "\nAlbum: " + track.albumName + "\nYear: " + track.year + "\nDuration: " + getTime(track.duration)):""
            font.pixelSize: 20
        }

        Rectangle {
            anchors.top: trackInfoText.bottom
            anchors.leftMargin: 100
            anchors.topMargin: 100
            width: parent.width - 100
            anchors.horizontalCenter: parent.horizontalCenter

            color: "transparent"

            TextButton {
                id: trackPlayButton
                text: "Play album"
                width: (parent.width/2) - 10
                anchors.left: parent.left
                onClicked: infoRectangle.albumSelected(album.id)
            }

            TextButton {
                id: trackPlayTrackButton
                text: "Play track"
                width: (parent.width/2) - 10
                anchors.right: parent.right
                anchors.leftMargin: 20
                onClicked: infoRectangle.trackSelected(track.id)
            }
        }
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
