#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>

#include "timerprogram.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv); // QGuiApplication will not style properly
    qmlRegisterType<TimerProgram>("timer", 0,1, "TimerProgram");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
