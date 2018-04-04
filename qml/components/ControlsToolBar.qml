import QtQuick 2.5
import QtQuick.Controls 1.4

Row {
    id: rowToolBar

    Action {
        id: playVideo
        iconSource: "qrc:/icons/icons/playVideo.png"
        iconName: qsTr("Play")
    }

    Action {
        id: stopVideo
        iconSource: "qrc:/icons/icons/stopVideo.png"
        iconName: qsTr("Stop")
    }
    Action {
        id: fullScreen
        iconSource: "qrc:/icons/icons/fullScreen.png"
        iconName: qsTr("Full screen")
    }

    Action {
        id: mutedSound
        iconSource: "qrc:/icons/icons/mutedSound.png"
        iconName: qsTr("Muted sound")
    }
}

