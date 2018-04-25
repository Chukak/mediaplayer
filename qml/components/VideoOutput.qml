import QtQuick 2.9
import QtQuick.Controls 1.4
import QtMultimedia 5.9

VideoOutput {
    id: videoOutput
    anchors.fill: parent
    Rectangle {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        Label {
            anchors.centerIn: parent
            text: subtitlesHandler.text
            color: "yellow"
            font.pointSize: 15
        }
    }
}
