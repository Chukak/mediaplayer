import QtQuick 2.9
import QtQuick.Dialogs 1.2


FileDialog {
    id:fileDialog
    title: qsTr("Select file")
    nameFilters: [
        "All formats (*.mkv *.mp4 *.avi *.wmv *.webm *.mp3)", "Matroska (*.mkv)",
        "Mp4 (*.mp4 *.m4p)", "Avi (*.avi)", "WebM (*.webm)", "Mp3 (*.mp3)",
        "QuickTime file format (*.mov *.qt)", "Window Media Video (*.wmv)",
    ]
    onAccepted: {
        if (fileDialog.selectExisting)
            mediaPlayerHandler.mediaUrl = fileUrl
    }
}

