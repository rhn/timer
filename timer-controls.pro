TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11

SOURCES += main.cpp \
    entrymodel.cpp \
    stopwatch.cpp \
    bindings.cpp

RESOURCES += \
    qml/qml.qrc \
    schema/schema.qrc

LIBS += -lsqlpp11-connector-sqlite3 \
        -lsqlite3 \
        -ldl \
        debug/librust.a

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
    timer_db.h \
    bindings.h

RUST_FILES += \
    $$PWD/rust/src/implementation.rs \
    $$PWD/rust/src/interface.rs \
    $$PWD/rust/src/lib.rs

dupa.commands = touch $$mytarget.target
dupa.target = dupa.h

rust.commands = sh $$PWD/rust/start-cargo.sh $$PWD
rust.target = debug/librust.a
rust.depends = $$RUST_FILES

QMAKE_EXTRA_TARGETS += rust
PRE_TARGETDEPS += debug/librust.a
QMAKE_CLEAN += debug/librust.a
