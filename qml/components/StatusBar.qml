import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 2.2 as Controls2
import QtQuick.Layouts 1.1

StatusBar {
    property string status

    RowLayout {
        anchors.fill: parent
        Controls2.Label {
            font.bold: true
            font.pixelSize: 12
            color: "#2997e5"
            text: status
        }
    }
    style: StatusBarStyle {
        background: Rectangle {
            height: 28
        }
    }
}

