import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Window 2.3
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.3
import QtMultimedia 5.5
import QtGraphicalEffects.private 1.0

ApplicationWindow {
    visible: true
    width: 1280
    height: 720
    title: qsTr("Hello World")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Item {
        anchors.fill: parent

        MediaPlayer {
            id: mediaplayer
            source: "file:///home/chukak17/Загрузки/Astral.4.Posledniy.Kluch.2018.DUAL.BDRip.720p.-HELLYWOOD.mkv"
        }

        VideoOutput {
            anchors.fill: parent
            source: mediaplayer
        }

        MouseArea {
            id: playArea
            anchors.fill: parent
            onPressed: {
                mediaplayer.play()
                console.log("da")
            }
        }
    }


}

