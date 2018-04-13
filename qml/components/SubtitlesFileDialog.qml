import QtQuick 2.9
import QtQuick.Dialogs 1.2

FileDialog {
    property QtObject subtitlesHandler
    id:fileDialog
    title: qsTr("Select file")
    nameFilters: [
        "SRT (*.srt)"
    ]
    onAccepted: {
        if (fileDialog.selectExisting)
            subtitlesHandler.addSubtitles(fileUrl)
    }
}

