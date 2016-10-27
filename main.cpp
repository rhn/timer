#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>

#include "stopwatch.h"
#include "entrymodel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv); // QGuiApplication will not style properly
    qmlRegisterType<StopWatch>("timer", 0,1, "StopWatch");
    //qmlRegisterType<EntryModel>("timer", 0,1, "TimeLogger");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
