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
