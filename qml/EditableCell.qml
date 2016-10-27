import QtQuick 2.0
import QtQuick.Controls 1.3

Item {
    id: cell
    property bool editing: false
    anchors.fill: parent
    function formatArg(arg) {
        return arg;
    }

    Item {
        id: read
        visible: !cell.editing
        anchors.fill: parent
        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("clicked")
                cell.editing = true
            }
        }
        Label {
            id: label
            text: formatArg(styleData.value)
            verticalAlignment: Text.AlignVCenter
            anchors.fill: parent
        }
    }
    TextField {
        id: write
        visible: cell.editing
        text: formatArg(styleData.value)
        anchors.fill: parent
        onEditingFinished: {
            cell.editing = false
        }
    }
}
