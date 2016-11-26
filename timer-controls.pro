TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11

SOURCES += main.cpp \
    entrymodel.cpp \
    stopwatch.cpp

RESOURCES += \
    qml/qml.qrc \
    schema/schema.qrc

LIBS += -lsqlpp11-connector-sqlite3 \
        -lsqlite3

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES += \
    qml/main.qml

HEADERS += \
    entrymodel.h \
    stopwatch.h \
    logging.h \
    timer_db.h
