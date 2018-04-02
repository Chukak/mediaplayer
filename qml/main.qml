import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Window 2.3
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.3
import QtMultimedia 5.5
import QtGraphicalEffects.private 1.0
import backend.VideoOutput 1.0
import "./components" as Components

ApplicationWindow {
    visible: true
    width: 1280
    height: 720
    title: ""

    Components.FileDialog {
        id: fileDialog
        videoOutputHandler: videoOutputHandler
    }

    menuBar: Components.MenuBar {
        id: menuBar
        idFileDialog: fileDialog
        idVideoOutputHandler: videoOutputHandler
    }


    toolBar: Components.ToolBar {
        id: toolBar
        idFileDialog: fileDialog
    }

    Item {
        id: mediaArea
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: playerButtons.top

        MediaPlayer {
            id: mediaplayer
            source: videoOutputHandler.videoUrl
            volume: 1.0
        }

        VideoOutput {
            id: videoOutput
            anchors.fill: parent
            source: mediaplayer
        }

        MouseArea {
            id: playArea
            anchors.fill: videoOutput
            onPressed: {
                mediaplayer.play()
                console.log("da")
            }
        }
    }

    Components.Buttons {
        id: playerButtons
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        width: parent.width
        height: 50

    }

    VideoOutputHandler {
        id: videoOutputHandler
        targetOutput: videoOutput
        targetPlayer: mediaplayer
    }
}

