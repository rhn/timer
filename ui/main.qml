/*
    Copyright 2016 rhn <gihu.rhn@porcupinefactory.org>
    This file is part of timer-controls.

    Foobar is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with timer-controls.  If not, see <http://www.gnu.org/licenses/>.
*/

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

    Customers {
        id: customers
    }

    Generic {
        id: generic
    }

    ColumnLayout {
        id: columnLayout1
        anchors.fill: parent

        RowLayout {
            id: rowLayout2
            Layout.fillWidth: true

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
        TextField {
            id: description
            Layout.fillWidth: true
            placeholderText: qsTr("Activity description")
        }

        ComboBox {
            id: customer
            model: customers
            textRole: "display"
        }

        Button {
            id: button2
            text: qsTr("Add")
            onClicked: {
                stopWatch.running = false
                timeLogger.add(stopWatch.currentTime, description.text, customer.currentText);
                description.text = "";
                stopWatch.clear()
            }
        }

        TableView {
            id: tableView1
            Layout.fillHeight: true
            Layout.fillWidth: true
            TableViewColumn {
                role: "customer"
                title: "customer"
            }
            TableViewColumn {
                role: "description"
                title: "description"
            }
            TableViewColumn {
                role: "duration"
                title: "duration"
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

        GridLayout {
            id: rowLayout3
            columns: 2
            Layout.fillWidth: true

            Label {
                id: label3
                text: "Customer:"
                Layout.alignment: Qt.AlignLeft
            }
            Label {
                id: label4
                text: (generic.weekly_customer(customer.currentText) / 1000 / 60 / 60).toFixed(3)
                Layout.alignment: Qt.AlignLeft
                Layout.fillWidth: true
            }

            Label {
                id: label5
                text: "Total:"
                Layout.alignment: Qt.AlignLeft
            }
            Label {
                id: label6
                text: (generic.weekly_total() / 1000 / 60 / 60).toFixed(3)
                Layout.alignment: Qt.AlignLeft
                Layout.fillWidth: true
            }
        }
    }
}
