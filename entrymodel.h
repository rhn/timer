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

#ifndef ENTRYMODEL_H
#define ENTRYMODEL_H

#include <vector>
#include <chrono>
#include <QAbstractTableModel>
#include <QTimer>

class Entry {
public:
    typedef std::chrono::time_point<std::chrono::system_clock> time_point;

    Entry(const int time_ms, const QString description, const int id=0, const time_point start_time=std::chrono::system_clock::now()) :
        id(id),
        time_ms(time_ms),
        description(description),
        start_time(start_time)
    {}

    enum roles {
        TIME_MS = Qt::UserRole,
        DESCRIPTION,
        START,
    };

    static const int columns_count = 3;
    int id;
    int time_ms;
    QString description;
    time_point start_time;
};

class EntryModel : public QAbstractTableModel
{
    Q_OBJECT
    std::vector<Entry> entries;
public:
    explicit EntryModel(QObject *parent = 0);
    QHash<int, QByteArray> roleNames() const {
        return {{Entry::roles::TIME_MS, "time"},
                {Entry::roles::DESCRIPTION, "description"},
                {Entry::roles::START, "start"}};
    }
    Qt::ItemFlags flags(const QModelIndex &index) const {
        (void)index;
        return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    // internal
    void add_entry(Entry &e);
    void save_data();

    // tracker for past entries
    QTimer ticker;
    Q_PROPERTY(int weekTotal READ get_week_total NOTIFY weekTotalChanged)
    int get_week_total();

    // for QAbstractTableModel
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;
    bool insertRows(int row, int count, const QModelIndex &parent);
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    // for QML
    Q_INVOKABLE void add(const int ms, const QString description) {
        Entry e(ms, description);
        return add_entry(e);
    }
    Q_INVOKABLE void save() {
        save_data();
    }
    Q_INVOKABLE void setProperty(const int index, const QString &roleName, const QVariant &value);
signals:
    void weekTotalChanged(int ms);
public slots:
    void on_tick();
};

#endif // ENTRYMODEL_H
