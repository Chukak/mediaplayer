import QtQuick 2.9
import QtQuick.Controls 2.2

Rectangle {
    property real valueSound: 0.0
    property int sizeButton: height - 10
    signal playVideo
    signal pauseVideo
    signal stopVideo
    signal fullScreen

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
        playButton.playing = true
    }
    onPauseVideo: {
        playButton.playing = false
    }
    onStopVideo: {
        playButton.playing = false
        playButton.stoped()
    }
    onFullScreen: {
        fullScreenButton.signalEmmited = true
        fullScreenButtonArea.clicked(Qt.LeftButton)
        fullScreenButton.signalEmmited = false
    }

    Item {
        id: controlsItem
        anchors.left: parent.left
        anchors.right: durationItem.left
        width: 170
        anchors.bottom: parent.bottom
        height: parent.height

        ToolButton {
            property bool playing: false
            signal stoped
            anchors.left: parent.left
            id: playButton
            width: sizeButton
            height: sizeButton
            onStoped: {
                playButtonImage.source = "qrc:/icons/resources/icons/play.png"
            }
            background: Item {
                Rectangle {
                    id: playButtonBckg
                    anchors.fill: parent
                    color: "transparent"
                    border.color: "transparent"
                }

                MouseArea {
                    id: playButtonArea
                    anchors.fill: playButtonBckg
                    hoverEnabled: true
                    onEntered: {
                        playButtonBckg.color = "#f2f2f2"
                        playButtonBckg.border.color = "#8f8f8f"
                        playButtonBckg.radius = 5
                    }
                    onExited: {
                        playButtonBckg.color = "transparent"
                        playButtonBckg.border.color = "transparent"
                        playButtonBckg.radius = 0
                    }
                    onClicked: {
                        if (mediaplayer.hasAudio || mediaplayer.hasVideo) {
                            if (playButton.playing) {
                                 mediaplayer.pause()
                                playButtonImage.source = "qrc:/icons/resources/icons/play.png"
                            } else {
                                 mediaplayer.play()
                                playButtonImage.source = "qrc:/icons/resources/icons/pause.png"
                            }
                        }
                    }
                }
            }

            Image {
                id: playButtonImage
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                source: "qrc:/icons/resources/icons/play.png"
                mipmap: true
                smooth: true
                anchors.margins: 8
            }
        }

        ToolButton {
            anchors.left: playButton.right
            id: stopButton
            width: sizeButton
            height: sizeButton
            background: Item {
                Rectangle {
                    id: stopButtonBckg
                    anchors.fill: parent
                    color: "transparent"
                    border.color: "transparent"
                }

                MouseArea {
                    anchors.fill: stopButtonBckg
                    hoverEnabled: true
                    onEntered: {
                        stopButtonBckg.color = "#f2f2f2"
                        stopButtonBckg.border.color = "#8f8f8f"
                        stopButtonBckg.radius = 5
                    }
                    onExited: {
                        stopButtonBckg.color = "transparent"
                        stopButtonBckg.border.color = "transparent"
                        stopButtonBckg.radius = 0
                    }
                    onClicked: {
                        if (mediaplayer.hasAudio || mediaplayer.hasVideo) {
                            mediaplayer.stop()
                        }
                    }
                }
            }

            Image {
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                source: "qrc:/icons/resources/icons/stop.png"
                mipmap: true
                smooth: true
                anchors.margins: 8
            }
        }

        ComboBox {
            property real currentValue: 0
            property int modelWidth: 0
            anchors.left: stopButton.right
            id: cbRewind
            width: sizeButton
            height: sizeButton
            currentIndex: 3
            model: ListModel {
                id: comboPositions
                ListElement {
                    text: qsTr("-10 minutes");
                    value: -600
                }
                ListElement {
                    text: qsTr("-5 minutes");
                    value: -300
                }
                ListElement {
                    text: qsTr("-2 minutes");
                    value: -120
                }
                ListElement {
                    text: qsTr("-1 minute");
                    value: -60
                }
                ListElement {
                    text: qsTr("-30 seconds");
                    value: -30
                }
                ListElement {
                    text: qsTr("+30 seconds");
                    value: 30
                }
                ListElement {
                    text: qsTr("+1 minute");
                    value: 60
                }
                ListElement {
                    text: qsTr("+2 minutes");
                    value: 120
                }
                ListElement {
                    text: qsTr("+5 minutes");
                    value: 300
                }
                ListElement {
                    text: qsTr("+10 minutes");
                    value: 600
                }
            }
            textRole: "text"
            onCurrentIndexChanged: {
                if (currentIndex > -1) {
                    currentValue = comboPositions.get(currentIndex).value
                    mediaPlayerHandler.seek(mediaPlayerHandler.position + currentValue)
                    currentIndex = -1
                }
            }

            contentItem: Item {}
            indicator: Canvas {}
            background: Item {
                Rectangle {
                    id: cbBackground
                    anchors.fill: parent
                    color: "transparent"
                    radius: 5

                    Image {
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectFit
                        source: "qrc:/icons/resources/icons/rewind.png"
                        mipmap: true
                        smooth: true
                        anchors.margins: 8
                    }
                }

                MouseArea {
                    anchors.fill: cbBackground
                    hoverEnabled: true
                    onEntered: {
                        cbBackground.color = "#f2f2f2"
                        cbBackground.border.color = "#8f8f8f"
                        cbBackground.radius = 5
                    }
                    onExited: {
                        cbBackground.color = "transparent"
                        cbBackground.border.color = "transparent"
                        cbBackground.radius = 0
                    }
                    onPressed: {
                        if (mediaplayer.hasAudio || mediaplayer.hasVideo) {
                            if (cbRewind.popup.visible) {
                                cbRewind.popup.close()
                            } else {
                                cbRewind.popup.open()
                            }
                        }
                    }
                }
            }
            delegate: ItemDelegate {
                id:cbRewindDlg
                height:25

                contentItem: Text {
                    id:cbRewindDlgTextItem
                    text: comboPositions.get(index).text
                    color: hovered ? "white" : "black"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                }

                background: Rectangle{
                    width:cbRewind.modelWidth //parent.width
                    color:cbRewindDlg.hovered ? "#2997e5" : "white"
                }
                Component.onCompleted: {
                    cbRewind.modelWidth = Math.max(width, cbRewind.modelWidth)
                }
            }
            popup: Popup {
                id: cbRewindPopup
                y: parent.width + 1
                width: cbRewind.modelWidth
                height: contentHeight
                contentItem: ListView {
                    implicitHeight: contentHeight
                    anchors.fill: parent
                    model: cbRewind.popup.visible ? cbRewind.delegateModel : null
                }
                background: Rectangle {
                    color: "white"
                }
            }
        }

        ComboBox {
            property int modelWidth: 0
            anchors.left: cbRewind.right
            id: cbPlaybackRate
            width: sizeButton
            height: sizeButton
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
            textRole: "text"
            onCurrentIndexChanged: {
                mediaPlayerHandler.setPlaybackRate(comboItems.get(currentIndex).value)
            }
            contentItem: Item {
                Text {
                    anchors.fill: parent
                    font.italic: true
                    text: comboItems.get(cbPlaybackRate.currentIndex).text
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
            }
            indicator: Rectangle {}
            background: Item {
                Rectangle {
                    id: cbPRBackground
                    anchors.fill: parent
                    color: "#f7f7f7"
                    border.color: "#8f8f8f"
                    radius: 5
                }

                MouseArea {
                    anchors.fill: cbPRBackground
                    hoverEnabled: true
                    onEntered: {
                        cbPRBackground.color = "#ffffff"
                        cbPRBackground.border.color = "#2997e5"
                    }
                    onExited: {
                        cbPRBackground.color = "#f7f7f7"
                        cbPRBackground.border.color = "#8f8f8f"
                    }
                    onPressed: {
                        if (mediaplayer.hasAudio || mediaplayer.hasVideo) {
                            if (cbPlaybackRate.popup.visible) {
                                cbPlaybackRate.popup.close()
                            } else {
                                cbPlaybackRate.popup.open()
                            }
                        }
                    }
                }
            }
            delegate: ItemDelegate {
                id:cbPRDlg
                height:25

                contentItem: Text {
                    id:cbPRDlgTextItem
                    text: comboItems.get(index).text
                    color: hovered ? "white" : "black"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                }

                background: Rectangle{
                    width: cbPlaybackRate.modelWidth
                    color: cbPRDlg.hovered ? "#2997e5" : "white"
                }
                Component.onCompleted: {
                    cbPlaybackRate.modelWidth = Math.max(width, cbPlaybackRate.modelWidth)
                }
            }
            popup: Popup {
                id: cbPRPopup
                y: parent.width + 1
                width: cbPlaybackRate.modelWidth
                height: contentHeight
                contentItem: ListView {
                    anchors.fill: parent
                    implicitHeight: contentHeight
                    model: cbPlaybackRate.popup.visible ? cbPlaybackRate.delegateModel : null
                }
                background: Rectangle {
                    border.color: "#8f8f8f"
                }
            }
        }

        Shortcut {
            id: playShortcut
            sequence: "Space"
            onActivated: {
                playButtonArea.clicked(Qt.LeftButton)
            }
        }

        Shortcut {
            id: rewindShortcutLeft
            sequence: "Left"
            onActivated: {
                cbRewind.currentIndex = 4
            }
        }

        Shortcut {
            id: rewindShortcutRight
            sequence: "Right"
            onActivated: {
                cbRewind.currentIndex = 5
            }
        }
    }

    Item {
        id: durationItem
        anchors.left: controlsItem.right
        anchors.right: durationLabelItem.left
        anchors.bottom: parent.bottom
        height: parent.height

        Slider {
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
        width: 140
        height: parent.height

        Item {
            id: labelsDuration
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            anchors.topMargin: sizeButton / 2 - 7

            Label {
                id: textCurrentDuration
                text: mediaPlayerHandler.durationInfo // "00:00:00"
                anchors.left: parent.left
                anchors.leftMargin: 10
                width: 50
                font.bold: true
                font.pointSize: 10
                horizontalAlignment: Text.AlignRight
                height: 10 //parent.height - 10
                onTextChanged: {
                    width = text.length * 6 + 2
                }
            }

            Label {
                id: textSeparatorDuration
                text: " / "
                anchors.left: textCurrentDuration.right
                anchors.leftMargin: 6
                width: 10
                font.bold: true
                font.pointSize: 10
                horizontalAlignment: Text.AlignRight
                height: 10 //parent.height - 10
            }

            Label {
                id: textFullDuration
                text: mediaPlayerHandler.totalDuration
                width: 50
                anchors.left: textSeparatorDuration.right
                anchors.leftMargin: 13
                font.bold: true
                font.pointSize: 10
                height: 10 //parent.height - 10
                horizontalAlignment: Text.AlignRight
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

        ToolButton {
            property real soundValue: 0.0
            signal mutedSound
            signal unmutedSound
            anchors.left: parent.left
            id: soundButton
            width: sizeButton
            height: sizeButton
            onMutedSound: {
                soundButtonImage.source = "qrc:/icons/resources/icons/mutedSound.png"
            }
            onUnmutedSound: {
                soundButtonImage.source = "qrc:/icons/resources/icons/sound.png"
            }
            background: Item {
                Rectangle {
                    id: soundButtonBckg
                    anchors.fill: parent
                    color: "transparent"
                    border.color: "transparent"
                }

                MouseArea {
                    id: soundButtonArea
                    anchors.fill: soundButtonBckg
                    hoverEnabled: true
                    onEntered: {
                        soundButtonBckg.color = "#f2f2f2"
                        soundButtonBckg.border.color = "#8f8f8f"
                        soundButtonBckg.radius = 5
                    }
                    onExited: {
                        soundButtonBckg.color = "transparent"
                        soundButtonBckg.border.color = "transparent"
                        soundButtonBckg.radius = 0
                    }
                    onClicked: {
                        if (valueSound === 0.0) {
                            valueSound = sliderSound.value
                            sliderSound.value = 0.0
                            soundButtonImage.source = "qrc:/icons/resources/icons/mutedSound.png"
                        } else {
                            sliderSound.value = valueSound
                            soundButtonImage.source = "qrc:/icons/resources/icons/sound.png"
                            valueSound = 0.0
                        }
                    }
                }
            }

            Image {
                id: soundButtonImage
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                source: "qrc:/icons/resources/icons/sound.png"
                mipmap: true
                smooth: true
                anchors.margins: 8
            }
        }

        Shortcut {
            id: soundShortcut
            sequence: "M"
            onActivated: {
                soundButtonArea.clicked(Qt.LeftButton)
            }
        }

        Slider {
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
                if (value == 0 && soundButton.soundValue > 0.0) {
                    soundButton.mutedSound()
                } else {
                    soundButton.unmutedSound()
                    soundButton.soundValue = value
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

        ToolButton {
            property bool fullScreen: false
            property bool signalEmmited: false
            anchors.left: parent.left
            id: fullScreenButton
            width: sizeButton
            height: sizeButton
            background: Item {
                Rectangle {
                    id: fullScreenButtonBckg
                    anchors.fill: parent
                    color: "transparent"
                    border.color: "transparent"
                }

                MouseArea {
                    id: fullScreenButtonArea
                    anchors.fill: fullScreenButtonBckg
                    hoverEnabled: true
                    onEntered: {
                        fullScreenButtonBckg.color = "#f2f2f2"
                        fullScreenButtonBckg.border.color = "#8f8f8f"
                        fullScreenButtonBckg.radius = 5
                    }
                    onExited: {
                        fullScreenButtonBckg.color = "transparent"
                        fullScreenButtonBckg.border.color = "transparent"
                        fullScreenButtonBckg.radius = 0
                    }
                    onClicked: {
                        if (!fullScreenButton.fullScreen) {
                            if (!fullScreenButton.signalEmmited){
                                setFullscreen(true)
                            }
                            fullScreenButton.fullScreen = true
                            fullScreenButtonImage.source = "qrc:/icons/resources/icons/fullScreenReverse.png"
                        } else {
                            if (!fullScreenButton.signalEmmited){
                                setFullscreen(false)
                            }
                            fullScreenButton.fullScreen = false
                            fullScreenButtonImage.source = "qrc:/icons/resources/icons/fullScreen.png"
                        }
                    }
                }
            }

            Image {
                id: fullScreenButtonImage
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                source: "qrc:/icons/resources/icons/fullScreen.png"
                mipmap: true
                smooth: true
                anchors.margins: 8
            }
        }

        Shortcut {
            id: fullScreenShortcut
            sequence: "F"
            onActivated: {
                fullScreenButtonArea.clicked(Qt.LeftButton)
            }
        }
    }
}
