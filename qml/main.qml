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
        id: mediaArea
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: playerButtonsParent.top
        width: parent.width
    }

    Window {
        id: fullScreenWindow
        y: 0
        x: 0
        width: Screen.width
        height: Screen.height
        visible: false
        flags: Qt.Window | Qt.FramelessWindowHint
        color: "black"

        Item {
            id: fullScreenMediaArea
            anchors.fill: parent
            parent: parent

            MouseArea {
                id: fullScreenMouseArea
                anchors.fill: parent
                parent: parent
                hoverEnabled: true
                onDoubleClicked: {
                    setFullscreen(false)
                }
                onPositionChanged: {
                    fullScreenTimer.stop()
                    playerButtons.opacity = 1.0
                    fullScreenTimer.start()
                }
            }

            Timer {
                id: fullScreenTimer
                interval: 3000
                onTriggered: {
                    playerButtons.opacity = 0
                    stop()
                }
            }
        }
    }

    Components.MediaPlayer {
        id: mediaplayer
    }

    Components.VideoOutput {
        id: videoOutput
        anchors.fill: parent
        source: mediaplayer
        parent: mediaArea
    }

    MouseArea {
        id: playArea
        anchors.fill: videoOutput
        parent: mediaArea
        onDoubleClicked: {
            setFullscreen(true)
        }
    }

    Item {
        id: playerButtonsParent
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        height: 50
        width: parent.width

        Components.ControlsToolBar {
            id: playerButtons
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: parent.width
            height: parent.height > 50 ? 50 : parent.height
        }
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

    function setFullscreen(fullscreen) {
        if (!fullscreen) {
            videoOutput.parent = mediaArea
            fullScreenWindow.visible = false
            setAnchorsPlayerButtons("windowed")
        } else {
            videoOutput.parent = fullScreenMediaArea
            fullScreenWindow.visible = Window.FullScreen
            setAnchorsPlayerButtons("fullscreen")
        }
    }

    function setAnchorsPlayerButtons(name) {
        if (name === "fullscreen") {
            playerButtons.parent = fullScreenMediaArea
            playerButtons.fullScreen()
            fullScreenTimer.start()
       } else if (name === "windowed") {
            playerButtons.parent = playerButtonsParent
            playerButtons.fullScreen()
            fullScreenTimer.stop()
            playerButtons.opacity = 1.0
        } else {
            console.log("Unknown option.")
        }
    }
}



