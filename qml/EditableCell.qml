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

import QtQuick 2.0
import QtQuick.Controls 1.3

Item {
    id: cell
    property bool editing: false
    anchors.fill: parent
    function formatArg(arg) {
        return arg;
    }
    function decode(text) {
        return text;
    }
    signal updated(variant value);

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
            if (label.text !== text) {
                updated(decode(text));
            }
            cell.editing = false;
        }
    }
}
