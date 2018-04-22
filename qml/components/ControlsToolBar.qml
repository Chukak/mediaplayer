import QtQuick 2.9
import QtQuick.Controls 1.4 as Controls1
import QtQuick.Controls 2.2 as Controls2
import QtQuick.Templates 2.0 as Templates2
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

Rectangle {
    property real valueSound
    property int sizeButton: height - 10
    signal playVideo
    signal pauseVideo
    signal stopVideo

    id: controls
    anchors.leftMargin: 20
    anchors.rightMargin: 20
    gradient: Gradient {
        GradientStop {
            position: 0.0
            color: "#f3f3f3"
        }
        GradientStop {
            position: 1.0
            color: "#c2c2c2"
        }
    }

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
                mediaplayer.play()
            }
        }

        Controls1.Action {
            id: pauseVideo
            iconSource: "qrc:/icons/icons/pauseVideo.png"
            iconName: qsTr("Pause")
            onTriggered: {
                mediaplayer.pause()
            }
        }

        Controls1.Action {
            id: stopVideo
            iconSource: "qrc:/icons/icons/stopVideo.png"
            iconName: qsTr("Stop")
            onTriggered: {
                mediaplayer.stop()
            }
        }

        Controls1.Action {
            id: playbackRate
            iconSource: "qrc:/icons/icons/playbackRate.png"
            iconName: qsTr("Playback")
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
        width: 170
        anchors.bottom: parent.bottom
        height: parent.height

        Controls1.ToolButton {
            anchors.left: parent.left
            id: playButton
            action: playVideo
            width: sizeButton
            height: sizeButton
        }

        Controls1.ToolButton {
            anchors.left: playButton.right
            id: stopButton
            action: stopVideo
            width: sizeButton
            height: sizeButton
        }

        Controls1.ComboBox {
            anchors.left: stopButton.right
            id: cbRewind
            width: sizeButton
            height: sizeButton
            //hovered: false
            currentIndex: 1
            model: ListModel {
                id: comboPositions
                ListElement {
                    text: qsTr("-10 minute");
                    value: 600
                }
                ListElement {
                    text: qsTr("-5 minute");
                    value: 300
                }
                ListElement {
                    text: qsTr("-2 minute");
                    value: 120
                }
                ListElement {
                    text: qsTr("-1 second");
                    value: 60
                }
                ListElement {
                    text: qsTr("-30 second");
                    value: 30
                }
                ListElement {
                    text: qsTr("+30 second");
                    value: 30
                }
                ListElement {
                    text: qsTr("+1 minute");
                    value: 60
                }
                ListElement {
                    text: qsTr("+2 minute");
                    value: 120
                }
                ListElement {
                    text: qsTr("+5 minute");
                    value: 300
                }
                ListElement {
                    text: qsTr("+10 minute");
                    value: 600
                }
            }
            onCurrentIndexChanged: {
                mediaPlayerHandler.seek(mediaPlayerHandler.position + comboPositions.get(currentIndex).value)
            }
            style: ComboBoxStyle {
                id: comboItemsStyle
                label: Item {
                    Image {
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectFit
                        source: "qrc:/icons/icons/playbackRate.png"
                        mipmap: true
                        smooth: true
                    }
                }
            }
        }

        Controls1.ComboBox {
            anchors.left: cbRewind.right
            id: cbPlaybackRate
            width: sizeButton + 10
            height: sizeButton
            //hovered: false
            currentIndex: 1
            model: ListModel {
                id: comboItems
                ListElement {
                    text: "x0.5";
                    value: 0.5
                }
                ListElement {
                    text: "x1";
                    value: 1.0
                }
                ListElement {
                    text: "x2";
                    value: 2.0
                }
                ListElement {
                    text: "x4";
                    value: 4.0
                }
                ListElement {
                    text: "x8";
                    value: 8.0
                }
                ListElement {
                    text: "x10";
                    value: 10.0
                }
            }
            onCurrentIndexChanged: {
                console.log(currentIndex)
                mediaPlayerHandler.setPlaybackRate(comboItems.get(currentIndex).value)
            }
            style: ComboBoxStyle {
                id: comboItemsStyle
                /*label: Item {
                    Image {
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectFit
                        source: "qrc:/icons/icons/playbackRate.png"
                        mipmap: true
                        smooth: true
                    }
                }*/
            }
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
                border.color: "#8f8f8f"
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
                    radius: 3
                    border.color: "#8f8f8f"
                    gradient: Gradient {
                        GradientStop {
                            position: 0.0
                            color: "#6DC3FF"
                        }
                        GradientStop {
                            position: 1.0
                            color: "#2997e5"
                        }
                    }
                }

            }
            height: parent.height - 10
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            from: 0
            to: mediaPlayerHandler.duration
            value: mediaPlayerHandler.position
            onMoved: {
                mediaPlayerHandler.seek(value)
            }
        }
    }

    Item {
        id: durationLabelItem
        anchors.right: soundItem.left
        anchors.bottom: parent.bottom
        width: 130
        height: parent.height

        Item {
            id: labelsDuration
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            anchors.topMargin: parent.height - (parent.height - 10)

            Controls2.Label {
                id: textCurrentDuration
                text: mediaPlayerHandler.durationInfo // "00:00:00"
                anchors.left: parent.left
                anchors.leftMargin: 6
                width: 50
                font.bold: true
                font.pointSize: 10
                height: parent.height - 10
                onTextChanged: {
                    width = text.length * 6 + 2
                }
            }

            Controls2.Label {
                id: textSeparatorDuration
                text: " / "
                anchors.left: textCurrentDuration.right
                anchors.leftMargin: 4
                width: 10
                font.bold: true
                font.pointSize: 10
                height: parent.height - 10
            }

            Controls2.Label {
                id: textFullDuration
                text: mediaPlayerHandler.totalDuration
                width: 50
                anchors.left: textSeparatorDuration.right
                anchors.leftMargin: 4
                font.bold: true
                font.pointSize: 10
                height: parent.height - 10
                onTextChanged: {
                    width = text.length * 6 + 2
                }
            }
        }
    }

    Item {
        id: soundItem
        anchors.right: fullScreenItem.left
        anchors.bottom: parent.bottom
        width: 160
        height: parent.height

        Controls1.ToolButton {
            anchors.left: parent.left
            id: soundButton
            action:sound
            width: sizeButton
            height: sizeButton
        }

        Controls2.Slider {
            id: sliderSound
            anchors.left: soundButton.right
            anchors.right: parent.right
            anchors.margins: 2
            orientation: Qt.Horizontal
            handle: Rectangle {
                x: sliderSound.visualPosition * (sliderSound.width - width)
                y: (sliderSound.height - height) / 2
                color: "#fff"
                width: 12
                height: 20
                radius: 2
                border.color: "#8f8f8f"
            }
            background: Rectangle {
                y: (sliderSound.height - height) / 2
                height: 12
                color: "#f1f1f1"
                radius: 3
                border.color: "#2997e5"

                Rectangle {
                    width: sliderSound.visualPosition * parent.width
                    height: parent.height
                    radius: 3
                    border.color: "#8f8f8f"
                    gradient: Gradient {
                        GradientStop {
                            position: 0.0
                            color: "#6DC3FF"
                        }
                        GradientStop {
                            position: 1.0
                            color: "#2997e5"
                        }
                    }
                }
            }
            height: parent.height - 10
            from: 0.0
            to: 1.0
            value: mediaplayer.volume
            onMoved: {
                mediaplayer.volume = value
            }
            onValueChanged: {
                if (value == 0 && soundButton.action == sound) {
                    soundButton.action = mutedSound
                } else {
                    soundButton.action = sound
                }
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
            width: sizeButton
            height: sizeButton
        }
    }

}

