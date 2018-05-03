import QtQuick 2.5
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4

ToolBar {
    id: toolBar
    property int sizeButton: height
    property QtObject subtitlesModel: listSubtitles
    width: parent.width
    height: 40
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

    ListModel {
        id: listSubtitles
        signal appendSubtitles(string name)
        signal clearSubs

        ListElement {
            text: qsTr("Nothing")
        }
        onAppendSubtitles: {
            listSubtitles.append({"text": name})
        }
        onClearSubs: {
            listSubtitles.clear()
            listSubtitles.append({"text": qsTr("Nothing")})
        }
    }

    Row {
        id: rowToolBar
        anchors.fill:parent

        ToolButton {
            id: openMedia
            width: sizeButton
            height: sizeButton
            background: Item {
                Rectangle {
                    id: openMediaBckg
                    anchors.fill: parent
                    color: "transparent"
                    border.color: "transparent"
                }

                MouseArea {
                    anchors.fill: openMediaBckg
                    hoverEnabled: true
                    onEntered: {
                        openMediaBckg.color = "#f2f2f2"
                        openMediaBckg.border.color = "#8f8f8f"
                        openMediaBckg.radius = 3
                    }
                    onExited: {
                        openMediaBckg.color = "transparent"
                        openMediaBckg.border.color = "transparent"
                        openMediaBckg.radius = 0
                    }
                    onClicked: {
                        fileDialog.open()
                    }
                }
            }

            Image {
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                source: "qrc:/icons/resources/icons/openFile.png"
                mipmap: true
                smooth: true
                anchors.margins: 8
            }
        }

        ToolButton {
            id: printScreen
            width: sizeButton
            height: sizeButton
            background: Item {
                Rectangle {
                    id: printScreenBckg
                    anchors.fill: parent
                    color: "transparent"
                    border.color: "transparent"
                }

                MouseArea {
                    anchors.fill: printScreenBckg
                    hoverEnabled: true
                    onEntered: {
                        printScreenBckg.color = "#f2f2f2"
                        printScreenBckg.border.color = "#8f8f8f"
                        printScreenBckg.radius = 3
                    }
                    onExited: {
                        printScreenBckg.color = "transparent"
                        printScreenBckg.border.color = "transparent"
                        printScreenBckg.radius = 0
                    }
                    onClicked: {
                        videoOutputHandler.snapshot()
                    }
                }
            }

            Image {
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                source: "qrc:/icons/resources/icons/snapshot.png"
                mipmap: true
                smooth: true
                anchors.margins: 8
            }
        }

        ComboBox {
            property int modelWidth: 0
            id: cbSubtitlesList
            width: sizeButton
            height: sizeButton
            currentIndex: 0
            model: listSubtitles
            textRole: "text"
            onCurrentIndexChanged: {
                if (cbSubtitlesList.popup.visible) {
                    subtitlesHandler.setSubtitles(currentIndex)
                }
            }
            contentItem: Item {}
            indicator: Rectangle {}
            background: Item {
                Rectangle {
                    id: cbSubsBackground
                    anchors.fill: parent
                    color: "transparent"
                    radius: 5

                    Image {
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectFit
                        source: "qrc:/icons/resources/icons/subtitles.png"
                        mipmap: true
                        smooth: true
                        anchors.margins: 8
                    }
                }

                MouseArea {
                    anchors.fill: cbSubsBackground
                    hoverEnabled: true
                    onEntered: {
                        cbSubsBackground.color = "#f2f2f2"
                        cbSubsBackground.border.color = "#8f8f8f"
                        cbSubsBackground.radius = 5
                    }
                    onExited: {
                        cbSubsBackground.color = "transparent"
                        cbSubsBackground.border.color = "transparent"
                        cbSubsBackground.radius = 0
                    }
                    onPressed: {
                        if (cbSubtitlesList.popup.visible) {
                            cbSubtitlesList.popup.close()
                        } else {
                            cbSubtitlesList.popup.open()
                        }
                    }
                }
            }
            delegate: ItemDelegate {
                id: cbSubsDlg
                height: 25

                contentItem: Text {
                    id:cbSubsDlgTextItem
                    text: listSubtitles.get(index).text
                    color: hovered ? "white" : "black"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    elide: Text.ElideRight
                }

                background: Rectangle{
                    width: cbSubtitlesList.modelWidth
                    color: cbSubsDlg.hovered ? "#2997e5" : "white"
                }
                Component.onCompleted: {
                    cbSubtitlesList.modelWidth = Math.max(width, cbSubtitlesList.modelWidth)
                }
            }
            popup: Popup {
                id: cbSubsPopup
                y: parent.width + 1
                width: cbSubtitlesList.modelWidth
                height: contentHeight
                contentItem: ListView {
                    implicitHeight: contentHeight
                    anchors.fill: parent
                    model: cbSubtitlesList.popup.visible ? cbSubtitlesList.delegateModel : null
                }
            }
        }
    }
}

