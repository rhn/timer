import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1

import timer 0.1

ApplicationWindow {
    title: qsTr("Timer")
    visible: true
    id: timer
    property bool running: false
    onRunningChanged: timerProgram.runningChanged(running)

    TimerProgram { // make this a context property?
        id: timerProgram
    }

    ColumnLayout {
        id: columnLayout1
        anchors.fill: parent

        RowLayout {
            id: rowLayout2
            Layout.fillWidth: true
            anchors.right: parent.right
            anchors.left: parent.left

            Button {
                id: startStopBtn
                text: qsTr("Start")
                onClicked: timer.running = true
            }

            Label {
                id: label2
                text: timerProgram.format_time(timerProgram.currentTime, "h:mm:ss")
                Layout.alignment: Qt.AlignRight
                Layout.fillWidth: true
            }

            TextField {
                id: elapsedEdit
                text: (timerProgram.currentTime / 1000 / 60 / 60).toFixed(3)
            }

            Button {
                id: runBtn
                text: qsTr("Running")
                checkable: true
                checked: timer.running
                onCheckedChanged: timer.running = checked
            }

        }

        ColumnLayout {
            id: columnLayout2
            Layout.fillWidth: true

            TextField {
                id: textField1
                Layout.fillWidth: true
                placeholderText: qsTr("Activity description")
            }

            Button {
                id: button2
                text: qsTr("Add")
            }
        }
        TableView {
            id: tableView1
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        states: State {
            name: "running"
            when: running
            PropertyChanges {
                target: startStopBtn
                text: qsTr("Stop")
                onClicked: timer.running = false
            }
            PropertyChanges {
                target: elapsedEdit
                readOnly: true
            }
        }
    }
}
