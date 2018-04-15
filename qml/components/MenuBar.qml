import QtQuick 2.5
import QtQuick.Controls 1.4

MenuBar {
    property QtObject idFileDialog
    property QtObject idVideoOutputHandler
    property QtObject idMediaPlayerHandler
    property QtObject idSubtitlesFileDialog

    Menu {
        title: qsTr("File")

        MenuItem {
            text: qsTr("&Open")
            onTriggered: {
                idFileDialog.selectExisting = true
                idFileDialog.open()
            }
        }
    }

    Menu {
        title: qsTr("Play")

        MenuItem {
            text: qsTr("&Play")
        }

        MenuItem {
            text: qsTr("&Stop")
        }
    }

    Menu {
        title: qsTr("Video")

        MenuItem {
            text: qsTr("&Full screen")
        }

    }

    Menu {
        title: qsTr("Audio")

        MenuItem {
            text: qsTr("&Set Audio track")
        }

        MenuItem {
            text: qsTr("&Load from file")
        }

        MenuItem {
            text: qsTr("&Mute sound")
        }

    }

    Menu {
        title: qsTr("Subtitles")

        MenuItem {
            text: qsTr("&Set subtitles")

        }

        MenuItem {
            text: qsTr("&Load from file")
            onTriggered: {
                idSubtitlesFileDialog.selectExisting = true
                idSubtitlesFileDialog.open()
            }
        }

        MenuItem {
            text: qsTr("&Show subtitles")
        }
    }

    Menu {
        title: qsTr("Window")

        MenuItem {
            text: qsTr("Settings")
        }

        MenuItem {
            text: qsTr("Exit")
            onTriggered: Qt.quit();
        }
    }
}
