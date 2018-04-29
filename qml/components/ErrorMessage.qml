import QtQuick 2.9
import QtQuick.Dialogs 1.2


MessageDialog {
    property string message: ""
    id: errorMessage
    icon: StandardIcon.Warning
    text: message
}
