import QtQuick 2.0

Rectangle
{
    id: button
    height: buttonText.height + 20
    width: buttonText.width + 20

    signal clicked
    property bool pressed
    property alias text: buttonText.text
    property alias textVAlign: buttonText.verticalAlignment
    property alias textHAlign: buttonText.horizontalAlignment

    border.color: "black"
    color: button.pressed ? "#CCffffff" : "transparent"

    Text {
        id: buttonText
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.centerIn: parent
        anchors.margins: 10
        text: "Play album"

        font.pixelSize: 20
    }

    MouseArea
    {
        anchors.fill: parent
        onPressed: {
            button.pressed = true;
        }
        onReleased: {
            button.pressed = false;
        }
        onClicked: button.clicked();
    }

}
