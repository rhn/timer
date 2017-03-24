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

#include "stopwatch.h"
#include "logging.h"


StopWatch::StopWatch(QObject *parent) : QObject(parent) {
    connect(&this->ticker, SIGNAL(timeout()), this, SLOT(on_tick()));
}

void StopWatch::_runningChanged(const bool running) {
    if (running) {
        this->timekeep.start();
        this->ticker.start(1000);
    } else {
        this->ticker.stop();
        this->on_tick();
        this->last_time = this->current_time;
    }
}

void StopWatch::clear() {
    if (this->ticker.isActive()) {
        qCWarning(timer) << "Clearing while timer is running";
    }
    this->last_time = 0;
    this->current_time = 0;
    emit currentTimeChanged(this->current_time);
}

QString StopWatch::format_time(const int milliseconds, const QString format) {
    QTime time = QTime::fromMSecsSinceStartOfDay(milliseconds);
    return time.toString(format);
}

void StopWatch::on_tick() {
    this->current_time = this->last_time + this->timekeep.elapsed();
    emit currentTimeChanged(this->current_time);
}
