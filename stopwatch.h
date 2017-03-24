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

#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QLoggingCategory>
#include <QTime>
#include <QTimer>

class StopWatch : public QObject
{
    Q_OBJECT
protected:
    QTime timekeep;
    QTimer ticker;
    int last_time = 0; // ms
    int current_time = 0; // ms
public:
    Q_PROPERTY(int currentTime READ get_current_time NOTIFY currentTimeChanged)
    explicit StopWatch(QObject *parent = 0);

    // Q_INVOKABLE means it's callable from QML
    Q_INVOKABLE void _runningChanged(const bool state);
    Q_INVOKABLE void clear();
    Q_INVOKABLE QString format_time(const int milliseconds, const QString format);

    int get_current_time() {
        return this->current_time;
    }

signals:
    void currentTimeChanged(int ms);
public slots:
    void on_tick();
};

#endif // STOPWATCH_H
