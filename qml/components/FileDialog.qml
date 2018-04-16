import QtQuick 2.9
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4


FileDialog {
    id:fileDialog
    title: qsTr("Select file")
    nameFilters: [
        "All formats (*.mkv *.mp4 *.avi *.wmv *.webm)", "Matroska (*.mkv)",
        "Mp4 (*.mp4 *.m4p)", "Avi (*.avi)", "WebM (*.webm)",
        "QuickTime file format (*.mov *.qt)", "Window Media Video (*.wmv)",
    ]
    onAccepted: {
        if (fileDialog.selectExisting)
            mediaPlayerHandler.mediaUrl = fileUrl
    }
}

