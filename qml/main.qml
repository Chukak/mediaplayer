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
    id: mainWindow
    visible: true
    width: 1270
    height: 720
    minimumWidth: 640
    minimumHeight: 480
    title: videoOutputHandler.videoTitle

    onWindowStateChanged: {

    }

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
        parent: null
        id: fullScreenMediaArea
        y: mainWindow.y
        x: mainWindow.x
        width: Screen.width
        height: Screen.height
    }



    Item {
        id: mediaArea
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: playerButtons.top
        width: parent.width

        MediaPlayer {
            id: mediaplayer
            source: videoOutputHandler.videoUrl
            volume: 1.0
            onPlaying: {
                //mediaArea.parent = fullScreenMediaArea
                //mediaArea.height = Screen.height
                //mediaArea.x = 0
                //mediaArea.height = Screen.width
                //mediaArea.parent = null
                playerButtons.playVideo()
            }
            onPaused: {
                //videoOutput.anchors.top = parent.top
                //videoOutput.parent = mediaArea
                playerButtons.pauseVideo()
            }
            onStopped: {
                playerButtons.stopVideo()
            }
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
                mediaplayer.pause()
                console.log("da")
            }
        }
    }

    Components.ControlsToolBar {
        id: playerButtons
        player: mediaplayer
        videoOutputHandler: videoOutputHandler
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



