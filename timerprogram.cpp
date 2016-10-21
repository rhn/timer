#include "timerprogram.h"

Q_LOGGING_CATEGORY(timer, "qml")

TimerProgram::TimerProgram(QObject *parent) : QObject(parent) {
    connect(&this->ticker, SIGNAL(timeout()), this, SLOT(on_tick()));
}

void TimerProgram::runningChanged(const bool running) {
    if (running) {
        this->timekeep.start();
        this->ticker.start(1000);
    } else {
        this->ticker.stop();
        this->on_tick();
        this->last_time = this->current_time;
    }
}

QString TimerProgram::format_time(const int milliseconds, const QString format) {
    QTime time = QTime::fromMSecsSinceStartOfDay(milliseconds);
    return time.toString(format);
}

void TimerProgram::on_tick() {
    this->current_time = this->last_time + this->timekeep.elapsed();
    emit currentTimeChanged(this->current_time);
}
