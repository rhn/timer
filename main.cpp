/*/*
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

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>

#include "stopwatch.h"
#include "entrymodel.h"
#include "bindings.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv); // QGuiApplication will not style properly
//    QApplication::setApplicationName("MyApp");
  //  QApplication::setOrganizationName("Me");

    qDebug() << "defegegege";
    qmlRegisterType<StopWatch>("timer", 0,1, "StopWatch");
    qmlRegisterType<EntryModel>("timer", 0,1, "TimeLogger");
    qmlRegisterType<Log>("timer", 0, 1, "TimeLog");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
