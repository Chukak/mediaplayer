import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2 as Controls2
import QtQml 2.2

MenuBar {
    property QtObject subtitlesModel: menuListSubtitlesModel
    signal loadedMedia
    signal invalidMedia

    onLoadedMedia: {
        playMenu.enabled = true
        pauseMenu.enabled = true
        stopMenu.enabled = true
        playbackRateMenu.enabled = true
        rewindMenu.enabled = true
    }
    onInvalidMedia: {
        playMenu.enabled = false
        pauseMenu.enabled = false
        stopMenu.enabled = false
        playbackRateMenu.enabled = false
        rewindMenu.enabled = false
    }

    Menu {
        title: qsTr("Open")

        MenuItem {
            iconSource: "qrc:/icons/resources/icons/openFile.png"
            text: qsTr("&File")
            shortcut: "Ctrl+F"
            onTriggered: {
                fileDialog.selectExisting = true
                fileDialog.open()
            }
        }
    }

    Menu {
        title: qsTr("Play")

        MenuItem {
            id: playMenu
            iconSource: "qrc:/icons/resources/icons/play.png"
            text: qsTr("&Play")
            onTriggered: {
                mediaplayer.play()
            }
        }

        MenuItem {
            id: pauseMenu
            iconSource: "qrc:/icons/resources/icons/pause.png"
            text: qsTr("&Pause")
            shortcut: "Space"
            onTriggered: {
                mediaplayer.pause()
            }
        }

        MenuItem {
            id: stopMenu
            iconSource: "qrc:/icons/resources/icons/stop.png"
            text: qsTr("&Stop")
            onTriggered: {
                mediaplayer.stop()
            }
        }

        MenuSeparator {}

        Menu {
            id: playbackRateMenu
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
            id: rewindMenu
            iconSource: "qrc:/icons/resources/icons/rewind.png"
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
                shortcut: "Left"
                onTriggered: {
                    mediaPlayerHandler.seek(mediaPlayerHandler.position - 30)
                }
            }

            MenuItem {
                text: qsTr("+30 seconds")
                shortcut: "Right"
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
            shortcut: "F"
            iconSource: "qrc:/icons/resources/icons/fullScreen.png"
            onTriggered: {
                setFullscreen("fullscreen")
            }
        }

    }

    Menu {
        title: qsTr("Audio")

        MenuItem {
            property real soundValue: 0.0
            iconSource: "qrc:/icons/resources/icons/mutedSound.png"
            text: qsTr("&Mute sound")
            shortcut: "M"
            onTriggered: {
                if (mediaplayer.volume > 0.0) {
                    soundValue = mediaplayer.volume
                    mediaplayer.volume = 0.0
                } else {
                    mediaplayer.volume = soundValue
                    soundValue = 0.0
                }
            }
        }

        MenuSeparator {}

        MenuItem {
            text: qsTr("Volume +")
            shortcut: "Up"
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
            shortcut: "Down"
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

        ListModel {
            id: menuListSubtitlesModel
            signal appendSubtitles(string name)
            signal clearSubs

            ListElement {
                text: qsTr("Nothing")
            }
            onAppendSubtitles: {
                menuListSubtitlesModel.append({"text": name})
            }
            onClearSubs: {
                menuListSubtitlesModel.clear()
                menuListSubtitlesModel.append({"text": qsTr("Nothing")})
            }
        }

        Menu {
            title: qsTr("&Main track")
            id: allSubtitles

            Instantiator {
                id:menuListSubtitles
                model: menuListSubtitlesModel
                delegate: MenuItem {
                    text: modelData
                    onTriggered: {
                        subtitlesHandler.setSubtitles(index)
                    }
                }
                onObjectAdded: {
                    allSubtitles.insertItem(index, object)
                }
                onObjectRemoved: {
                    allSubtitles.removeItem(object)
                }
            }
        }

        MenuSeparator {}

        MenuItem {
            text: qsTr("&Clear all subtitles")
            onTriggered: {
                subtitlesHandler.clearLoadedSubtitles()
            }
        }

        MenuSeparator {}

        MenuItem {
            iconSource: "qrc:/icons/resources/icons/subtitles.png"
            text: qsTr("&Load from file")
            onTriggered: {
                subtitlesDialog.selectExisting = true
                subtitlesDialog.open()
            }
        }

        MenuItem {
            text: qsTr("&Display subtitles")
            shortcut: "V"
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
            enabled: false
            text: qsTr("Settings")
        }

        MenuSeparator {}

        MenuItem {
            text: qsTr("Exit")
            onTriggered: Qt.quit();
        }
    }
}
