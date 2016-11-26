import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1

import timer 0.1

ApplicationWindow {
    title: qsTr("Timer")
    visible: true
    id: timerApp

    StopWatch { // make this a context property?
        id: stopWatch
        property bool running: false
        onRunningChanged: stopWatch._runningChanged(running)
    }

    TimeLogger {
        id: timeLogger
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
                onClicked: stopWatch.running = true
            }

            Label {
                id: label2
                text: stopWatch.format_time(stopWatch.currentTime, "h:mm:ss")
                Layout.alignment: Qt.AlignRight
                Layout.fillWidth: true
            }

            TextField {
                id: elapsedEdit
                readOnly: stopWatch.running
                text: (stopWatch.currentTime / 1000 / 60 / 60).toFixed(3)
                horizontalAlignment: TextInput.AlignRight
            }

            Button {
                id: runBtn
                text: qsTr("Running")
                checkable: true
                checked: stopWatch.running
                onCheckedChanged: stopWatch.running = checked
            }
        }

        ColumnLayout {
            id: columnLayout2
            Layout.fillWidth: true

            TextField {
                id: description
                Layout.fillWidth: true
                placeholderText: qsTr("Activity description")
            }

            Button {
                id: button2
                text: qsTr("Add")
                onClicked: {
                    stopWatch.running = false
                    timeLogger.add(stopWatch.currentTime, description.text)
                    description.text = "";
                    stopWatch.clear()
                    timeLogger.save();
                }
            }
        }
        TableView {
            id: tableView1
            Layout.fillHeight: true
            Layout.fillWidth: true

            TableViewColumn {
                role: "description"
                title: "description"
            }
            TableViewColumn {
                role: "time"
                title: "time"
                delegate: EditableCell {
                    function formatArg(arg) {
                        return (styleData.value / 1000 / 60 / 60).toFixed(3);
                    }
                    function decode(text) {
                        return text * 1000 * 60 * 60;
                    }
                }
            }
            TableViewColumn {
                role: "start"
                title: "start"
            }


            model: timeLogger
        }

        Button {
            id: saveBtn
            text: qsTr("Save")
            onClicked: {
                timeLogger.save();
            }
        }

        states: State {
            name: "running"
            when: stopWatch.running
            PropertyChanges {
                target: startStopBtn
                text: qsTr("Stop")
                onClicked: stopWatch.running = false
            }
            PropertyChanges {
                target: elapsedEdit
                readOnly: true
            }
        }
    }
}
