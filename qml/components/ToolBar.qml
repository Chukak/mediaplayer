import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

ToolBar {
    property QtObject idFileDialog
    id: toolBar
    width: parent.width
    height: 40
    style: ToolBarStyle {
        background: Rectangle {
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
        }
    }

    Row {
        id: rowToolBar
        anchors.fill:parent

        Action {
            id: openVideo
            iconSource: "qrc:/icons/icons/openVideo.png"
            iconName: qsTr("Open")

            onTriggered: {
                idFileDialog.open()
            }
        }

        Action {
            id: printScreen
            iconSource: "qrc:/icons/icons/printScreen.png"
            iconName: qsTr("Print screen")
        }

        Action {
            id: setAudioTrack
            iconSource: "qrc:/icons/icons/audioTrack.png"
            iconName: qsTr("Select audio track")
        }

        Action {
            id: setSubtitles
            iconSource: "qrc:/icons/icons/subtitles.png"
            iconName: qsTr("Set subtitles")
        }


        ToolButton {
            action: openVideo
        }

        ToolButton {
            action: printScreen
        }

        ToolButton {
            action: setAudioTrack
        }

        ToolButton {
            action: setSubtitles
        }
    }
}

