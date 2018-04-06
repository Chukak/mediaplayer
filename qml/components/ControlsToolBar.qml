import QtQuick 2.9
import QtQuick.Controls 1.4 as Controls1
import QtQuick.Controls 2.2 as Controls2
import QtQuick.Templates 2.0 as Templates2

Item {
    property QtObject player
    property QtObject mediaPlayerHandler
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
        Controls1.Action {
            id: playVideo
            iconSource: "qrc:/icons/icons/playVideo.png"
            iconName: qsTr("Play")
            onTriggered: {
                player.play()
            }
        }

        Controls1.Action {
            id: pauseVideo
            iconSource: "qrc:/icons/icons/pauseVideo.png"
            iconName: qsTr("Pause")
            onTriggered: {
                player.pause()
            }
        }

        Controls1.Action {
            id: rewindLeft
            iconSource: "qrc:/icons/icons/rewindLeft.png"
            iconName: qsTr("Left")
        }

        Controls1.Action {
            id: rewindRight
            iconSource: "qrc:/icons/icons/rewindRight.png"
            iconName: qsTr("Right")
        }

        Controls1.Action {
            id: stopVideo
            iconSource: "qrc:/icons/icons/stopVideo.png"
            iconName: qsTr("Stop")
            onTriggered: {
                player.stop()
            }
        }

        Controls1.Action {
            id: fullScreen
            iconSource: "qrc:/icons/icons/fullScreen.png"
            iconName: qsTr("Full screen")
        }

        Controls1.Action {
            id: sound
            iconSource: "qrc:/icons/icons/sound.png"
            iconName: qsTr("Muted sound")
            onTriggered: {
                valueSound = sliderSound.value
                sliderSound.value = 0.0
                soundButton.action = mutedSound
            }
        }

        Controls1.Action {
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

        Controls1.ToolButton {
            anchors.left: parent.left
            id: playButton
            action: playVideo
        }

        Controls1.ToolButton {
            anchors.left: playButton.right
            id: stopButton
            action: stopVideo
        }

        Controls1.ToolButton {
            anchors.left: stopButton.right
            id: rewindLeftButton
            action: rewindLeft
       }

        Controls1.ToolButton {
            anchors.left: rewindLeftButton.right
            id: rewindRightButton
            action: rewindRight
        }
    }

    Item {
        id: durationItem
        anchors.left: controlsItem.right
        anchors.right: durationLabelItem.left
        anchors.bottom: parent.bottom
        height: parent.height

        Controls2.Slider {
            id: sliderDurationVideo
            orientation: Qt.Horizontal
            anchors.left: parent.left
            anchors.right: parent.right
            handle: Rectangle {
                x: sliderDurationVideo.visualPosition * (sliderDurationVideo.width - width)
                y: (sliderDurationVideo.height - height) / 2
                color: "#fff"
                width: 16
                height: 24
                radius: 2
                border.color: "#c1c1c1"
            }
            background: Rectangle {
                y: (sliderDurationVideo.height - height) / 2
                height: 18
                color: "#f2f2f2"
                radius: 3
                border.color: "#2997e5"

                Rectangle {
                    width: sliderDurationVideo.visualPosition * parent.width
                    height: parent.height
                    color: "#2997e5"
                    radius: 3
                    border.color: "#c1c1c1"
                }

            }
            height: 30
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            from: 0
            to: mediaPlayerHandler.duration
            value: mediaPlayerHandler.position
            onValueChanged: {
                console.log(value)
            }
            onMoved: {
                console.log(value)
            }
        }
    }

    Item {
        id: durationLabelItem
        anchors.right: soundItem.left
        anchors.bottom: parent.bottom
        width: 105
        height: parent.height

        Text {
            id: textCurrentDuration
            text: mediaPlayerHandler.durationInfo // "00:00:00"
            anchors.left: parent.left
            width: 45
        }

        Text {
            id: textSeparatorDuration
            text: " / "
            anchors.left: textCurrentDuration.right
            width: 10
            anchors.right: textFullDuration.left

        }

        Text {
            id: textFullDuration
            text: mediaPlayerHandler.totalDuration
            width: 45
            anchors.right: parent.right
            anchors.rightMargin: 5
        }
    }

    Item {
        id: soundItem
        anchors.right: fullScreenItem.left
        anchors.bottom: parent.bottom
        width: 130
        height: parent.height

        Controls1.ToolButton {
            anchors.left: parent.left
            id: soundButton
            action:sound
        }

        Controls2.Slider {
            id: sliderSound
            anchors.left: soundButton.right
            anchors.right: parent.right
            orientation: Qt.Horizontal
            handle: Rectangle {
                x: sliderSound.visualPosition * (sliderSound.width - width)
                y: (sliderSound.height - height) / 2
                color: "#fff"
                width: 12
                height: 20
                radius: 2
                border.color: "#c1c1c1"
            }
            background: Rectangle {
                y: (sliderSound.height - height) / 2
                height: 12
                color: "#f2f2f2"
                radius: 3
                border.color: "#2997e5"

                Rectangle {
                    width: sliderSound.visualPosition * parent.width
                    height: parent.height
                    color: "#2997e5"
                    radius: 3
                    border.color: "#c1c1c1"
                }

            }
            height: 30
            from: 0.0
            to: 1.0
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

        Controls1.ToolButton {
            id: fullScreenButton
            action: fullScreen
        }
    }

}

