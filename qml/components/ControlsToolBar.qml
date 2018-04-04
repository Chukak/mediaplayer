import QtQuick 2.5
import QtQuick.Controls 1.4

Item {
    property QtObject player
    property QtObject videoOutputHandler
    property real valueSound
    signal playVideo
    signal pauseVideo
    signal stopVideo

    id: rowToolBar

    onPlayVideo: {
        playButton.action = pauseVideo
    }
    onPauseVideo: {
        playButton.action = playVideo
    }
    onStopVideo: {
        playButton.action = playVideo
    }

    Item {
        Action {
            id: playVideo
            iconSource: "qrc:/icons/icons/playVideo.png"
            iconName: qsTr("Play")
            onTriggered: {
                player.play()
            }
        }

        Action {
            id: pauseVideo
            iconSource: "qrc:/icons/icons/pauseVideo.png"
            iconName: qsTr("Pause")
            onTriggered: {
                player.pause()
            }
        }

        Action {
            id: rewindLeft
            iconSource: "qrc:/icons/icons/rewindLeft.png"
            iconName: qsTr("Left")
        }

        Action {
            id: rewindRight
            iconSource: "qrc:/icons/icons/rewindRight.png"
            iconName: qsTr("Right")
        }

        Action {
            id: stopVideo
            iconSource: "qrc:/icons/icons/stopVideo.png"
            iconName: qsTr("Stop")
            onTriggered: {
                player.stop()
            }
        }

        Action {
            id: fullScreen
            iconSource: "qrc:/icons/icons/fullScreen.png"
            iconName: qsTr("Full screen")
        }

        Action {
            id: sound
            iconSource: "qrc:/icons/icons/sound.png"
            iconName: qsTr("Muted sound")
            onTriggered: {
                valueSound = sliderSound.value
                sliderSound.value = 0.0
                soundButton.action = mutedSound
            }
        }

        Action {
            id: mutedSound
            iconSource: "qrc:/icons/icons/mutedSound.png"
            iconName: qsTr("Unmuted sound")
            onTriggered: {
                sliderSound.value = valueSound
                soundButton.action = sound
            }
        }
    }

    Item {
        id: controlsItem
        anchors.left: parent.left
        anchors.right: durationItem.left
        width: 160
        anchors.bottom: parent.bottom
        height: parent.height

        ToolButton {
            anchors.left: parent.left
            id: playButton
            action: playVideo
        }

        ToolButton {
            anchors.left: playButton.right
            id: stopButton
            action: stopVideo
        }

        ToolButton {
            anchors.left: stopButton.right
            id: rewindLeftButton
            action: rewindLeft
        }

        ToolButton {
            anchors.left: rewindLeftButton.right
            id: rewindRightButton
            action: rewindRight
        }
    }

    Item {
        id: durationItem
        anchors.left: controlsItem.right
        anchors.right: soundItem.left
        anchors.bottom: parent.bottom
        height: parent.height

        Slider {
            id: sliderDurationVideo
            orientation: Qt.Horizontal
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            minimumValue: 0
            maximumValue: player.duration
        }
    }

    Item {
        id: soundItem
        anchors.right: fullScreenItem.left
        anchors.bottom: parent.bottom
        width: 130
        height: parent.height

        ToolButton {
            anchors.left: parent.left
            id: soundButton
            action:sound
        }

        Slider {
            id: sliderSound
            width: 90
            anchors.left: soundButton.right
            orientation: Qt.Horizontal
            minimumValue: 0.0
            maximumValue: 1.0
            value: player.volume
            onValueChanged: {
                player.volume = value
            }
        }
    }

    Item {
        id: fullScreenItem
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: 40
        height: parent.height

        ToolButton {
            id: fullScreenButton
            action: fullScreen
        }
    }

}

