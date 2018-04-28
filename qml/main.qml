import "./components" as Components
import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Window 2.3
import QtMultimedia 5.5
import backend.VideoOutput 1.0
import backend.MediaPlayer 1.0
import backend.SubtitlesOutput 1.0


ApplicationWindow {
    id: mainWindow
    visible: true
    minimumWidth: 640
    minimumHeight: 480
    title: mediaPlayerHandler.mediaTitle
    color: "black"
    onWindowStateChanged: {

    }

    Components.ErrorMessage {
        id: errorMessage
    }

    Components.FileDialog {
        id: fileDialog
    }

    Components.SubtitlesFileDialog {
        id: subtitlesDialog
    }

    menuBar: Components.MenuBar {
        id: menuBar
    }

    toolBar: Components.ToolBar {
        id: toolBar
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

        Components.MediaPlayer {
            id: mediaplayer
        }

        Components.VideoOutput {
            id: videoOutput
            anchors.fill: parent
            source: mediaplayer
        }

        MouseArea {
            id: playArea
            anchors.fill: videoOutput
            onPressed: {
                mediaplayer.pause()
            }
        }
    }

    Components.ControlsToolBar {
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
        mediaPlayer: mediaPlayerHandler
        onSnapshotError: {
            errorMessage.message = message
            errorMessage.visible = true
        }
    }

    MediaPlayerHandler {
        id: mediaPlayerHandler
        player: mediaplayer
        subtitlesOutput: subtitlesHandler
    }

    SubtitlesHandler {
        id: subtitlesHandler
        onSubtitlesCleared: {
            menuBar.subtitlesModel.clearSubs()
            toolBar.subtitlesModel.clearSubs()
        }
        onSubtitlesAdded: {
            menuBar.subtitlesModel.appendSubtitles(name)
            toolBar.subtitlesModel.appendSubtitles(name)
        }
        onSubtitlesNotFoundError: {
            errorMessage.message = "Subtitles not found!"
            errorMessage.visible = true
        }
    }

    statusBar: Components.StatusBar {
        id: statusBar
        status: videoOutputHandler.status
    }
}



