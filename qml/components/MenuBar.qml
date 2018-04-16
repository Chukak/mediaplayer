import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2 as Controls2
import QtQml 2.2

MenuBar {
    Menu {
        title: qsTr("Open")

        MenuItem {
            text: qsTr("&File")
            onTriggered: {
                fileDialog.selectExisting = true
                fileDialog.open()
            }
        }
    }

    Menu {
        title: qsTr("Play")

        MenuItem {
            text: qsTr("&Play")
            onTriggered: {
                mediaplayer.play()
            }
        }

        MenuItem {
            text: qsTr("&Pause")
            onTriggered: {
                mediaplayer.pause()
            }
        }

        MenuItem {
            text: qsTr("&Stop")
            onTriggered: {
                mediaplayer.stop()
            }
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
            text: qsTr("&Main track")
        }

        MenuSeparator {}

        MenuItem {
            text: qsTr("&Load from file")
        }

        MenuItem {
            text: qsTr("&Mute sound")
        }

        MenuSeparator {}

        MenuItem {
            text: qsTr("Volume +")
            onTriggered: {
                if (mediaplayer.volume < 1.0) {
                    if (mediaplayer.volume <= 0.95) {
                        mediaplayer.volume = mediaplayer.volume + 0.05
                    } else {
                        mediaplayer.volume = 1.0
                    }
                }
            }
        }

        MenuItem {
            text: qsTr("Volume -")
            onTriggered: {
                if (mediaplayer.volume > 0) {
                    if (mediaplayer.volume >= 0.05) {
                        mediaplayer.volume = mediaplayer.volume - 0.05
                    } else {
                        mediaplayer.volume = 0
                    }
                }
            }
        }

    }



    Menu {
        title: qsTr("Subtitles")

        Menu {
            title: qsTr("&Main track")
            id: allSubtitles

            MenuItem {
                text: qsTr("Nothing")
            }

            Instantiator {
                model: subtitlesHandler.listSubtitles
                delegate: MenuItem {
                    text: modelData
                    onTriggered: {
                        subtitlesHandler.setSubtitles(index + 1)
                    }
                }
                onObjectAdded: allSubtitles.insertItem(index, object)
                onObjectRemoved: allSubtitles.removeItem(object)
            }
        }

        MenuSeparator {}

        MenuItem {
            text: qsTr("&Load from file")
            onTriggered: {
                subtitlesDialog.selectExisting = true
                subtitlesDialog.open()
            }
        }

        MenuItem {
            text: qsTr("&Display subtitles")
            checkable: true
            checked: true
            onCheckedChanged: {
                console.log(checked)
                mediaPlayerHandler.showSubtitles(checked)
            }
        }
    }

    Menu {
        title: qsTr("Window")

        MenuItem {
            text: qsTr("Settings")
        }

        MenuSeparator {}

        MenuItem {
            text: qsTr("Exit")
            onTriggered: Qt.quit();
        }
    }
}
