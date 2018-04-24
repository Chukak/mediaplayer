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

        MenuSeparator {}

        Menu {
            title: qsTr("&Playback rate")

            MenuItem {
                text: qsTr("Normal")
                onTriggered: {
                    mediaPlayerHandler.setPlaybackRate(1.0)
                }
            }

            MenuSeparator {}

            MenuItem {
                text: qsTr("Half")
                onTriggered: {
                    mediaPlayerHandler.setPlaybackRate(0.5)
                }
            }

            MenuSeparator {}

            MenuItem {
                text: qsTr("Double")
                onTriggered: {
                    mediaPlayerHandler.setPlaybackRate(2.0)
                }
            }

            MenuSeparator {}

            MenuItem {
                text: qsTr("4.0x")
                onTriggered: {
                    mediaPlayerHandler.setPlaybackRate(4.0)
                }
            }

            MenuItem {
                text: qsTr("8.0x")
                onTriggered: {
                    mediaPlayerHandler.setPlaybackRate(8.0)
                }
            }

            MenuItem {
                text: qsTr("10.0x")
                onTriggered: {
                    mediaPlayerHandler.setPlaybackRate(10.0)
                }
            }
        }

        MenuSeparator {}

        Menu {
            title: qsTr("Rewind")

            MenuItem {
                text: qsTr("-10 minutes")
                onTriggered: {
                    mediaPlayerHandler.seek(mediaPlayerHandler.position - 600)
                }
            }

            MenuItem {
                text: qsTr("-5 minutes")
                onTriggered: {
                    mediaPlayerHandler.seek(mediaPlayerHandler.position - 300)
                }
            }

            MenuItem {
                text: qsTr("-2 minutes")
                onTriggered: {
                    mediaPlayerHandler.seek(mediaPlayerHandler.position - 120)
                }
            }

            MenuItem {
                text: qsTr("-1 minute")
                onTriggered: {
                    mediaPlayerHandler.seek(mediaPlayerHandler.position - 60)
                }
            }

            MenuItem {
                text: qsTr("-30 seconds")
                onTriggered: {
                    mediaPlayerHandler.seek(mediaPlayerHandler.position - 30)
                }
            }

            MenuItem {
                text: qsTr("+30 seconds")
                onTriggered: {
                    mediaPlayerHandler.seek(mediaPlayerHandler.position + 30)
                }
            }

            MenuItem {
                text: qsTr("+1 minute")
                onTriggered: {
                    mediaPlayerHandler.seek(mediaPlayerHandler.position + 60)
                }
            }

            MenuItem {
                text: qsTr("+2 minutes")
                onTriggered: {
                    mediaPlayerHandler.seek(mediaPlayerHandler.position + 120)
                }
            }

            MenuItem {
                text: qsTr("+5 minutes")
                onTriggered: {
                    mediaPlayerHandler.seek(mediaPlayerHandler.position + 300)
                }
            }

            MenuItem {
                text: qsTr("+10 minutes")
                onTriggered: {
                    mediaPlayerHandler.seek(mediaPlayerHandler.position + 600)
                }
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
                onTriggered: {
                    subtitlesHandler.setSubtitles(0)
                }
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
