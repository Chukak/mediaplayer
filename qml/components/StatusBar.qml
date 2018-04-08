import QtQuick 2.9
import QtQuick.Controls 1.4 as Controls1
import QtQuick.Controls 2.2 as Controls2
import QtQuick.Layouts 1.1

Controls1.StatusBar {
    property string status

    RowLayout {
        anchors.fill: parent
        Controls2.Label {
            text: status
        }
    }
}

