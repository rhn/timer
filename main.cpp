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
#include <QProcessEnvironment>
#include <QQmlApplicationEngine>
#include <QQmlComponent>


#include "stopwatch.h"
#include "bindings.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv); // QGuiApplication will not style properly
//    QApplication::setApplicationName("MyApp");
  //  QApplication::setOrganizationName("Me");

    qmlRegisterType<StopWatch>("timer", 0,1, "StopWatch");
    qmlRegisterType<EntryModel>("timer", 0,1, "TimeLogger");
    qmlRegisterType<CustomersModel>("timer", 0,1, "Customers");
    qmlRegisterType<Generic>("timer", 0,1, "Generic");

    QQmlApplicationEngine engine;
    QString qml_root = QProcessEnvironment::systemEnvironment().value("QML_DATA_DIR", QML_DIR) + "/main.qml";
    engine.load(qml_root);

    return app.exec();
}
