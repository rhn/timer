A timer program written with QtQuickControls
============================================

**NOTE**: This is work in progress. It may scare your cat.

This program is a demonstration of interfacing of C++ logic with QML user interface.

The QML part is a self-contained UI, which minimally connects to the state and logic defined in C++.

Functionality
-------------

- Starting a timer and resume it.
- Displaying a table of previous timers in this session.
- Saving the currently visible entries to a local database

Requirements
------------

- Qt5.6
- QtQuick
- QtQuickComponents
- sqlpp11
- sqlpp11-connector-sqlite3

Installation
------------

### QtCreator

1. Open the file timer-controls.pro
2. Optionally, set the env variables in run environment:
 - `QT_LOGGING_RULES='*qml.debug=true'`
 - `Qt_LOGGING_TO_CONSOLE=1`

### qtmake

*TODO*

TODO
----

- load saved data
- display start time

### Less important

- edit columns
- edit currently running time
- mark items as submitted
- don't display old items
- sum up time
- display remaining time
