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

#include <QStandardPaths>
#include <QDir>

#include <sqlpp11/sqlite3/sqlite3.h>
#include <sqlpp11/sqlpp11.h>

#include <date.h>

#include "entrymodel.h"
#include "logging.h"
#include "timer_db.h"

using namespace TimerDB;
using namespace std::chrono;
namespace sql = sqlpp::sqlite3;

Q_LOGGING_CATEGORY(timer, "qml")


static sql::connection *get_db() {
    QString data_dir_path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir::root().mkpath(data_dir_path);
    sql::connection_config config;
    bool create = false;
    QString db_path(data_dir_path + "/entries.db");
    config.path_to_database = db_path.toStdString();
    config.flags = SQLITE_OPEN_READWRITE;
    if (!QFile(db_path).exists()) {
        config.flags |= SQLITE_OPEN_CREATE;
        create = true;
    }
    config.debug = true;
    sql::connection *db = new sql::connection(config);
    if (create) {
        QFile schema(":/timer.sql");
        schema.open(QIODevice::ReadOnly);
        db->execute(schema.readAll().toStdString());
        schema.close();
    }
    return db;
}

EntryModel::EntryModel(QObject *parent) : QAbstractTableModel(parent) {
    sql::connection *db = get_db();
    Entries ent_table;
    Entry::time_point startDate = std::chrono::system_clock::now() - std::chrono::hours(24 * 32);

    for (const auto& e : (*db)(select(all_of(ent_table)).from(ent_table).where(ent_table.startTime > startDate))) {
        sqlpp::chrono::microsecond_point t = e.startTime;
        Entry::time_point u = time_point_cast<Entry::time_point::duration>(t);
        Entry en((int)e.duration, ((std::string)e.description).c_str(), (int)e.id, u);
        add_entry(en);
    }
    delete db;
}

void EntryModel::add_entry(Entry& e) {
    qCDebug(timer) << "add" << e.time_ms;
    this->entries.emplace_back(e);
    this->insertRow(0, QModelIndex());
}

void EntryModel::save_data() {
    sql::connection *db = get_db();
    Entries ent_table;
    for (Entry& e : this->entries) {
        auto param = sql::insert_or_replace_into(ent_table) \
                .set(ent_table.id = sqlpp::tvin(e.id),
                     ent_table.description = e.description.toStdString(),
                     ent_table.duration = e.time_ms,
                     ent_table.startTime = e.start_time);
        e.id = (*db)(param);
    }
    delete db;
}

int EntryModel::get_week_total()
{
    sql::connection *db = get_db();
    Entries ent_table;
    Entry::time_point startDate = std::chrono::system_clock::now() - std::chrono::hours(24 * 7);

    const auto& row = (*db)(select(sum(ent_table.duration)).from(ent_table).where(ent_table.startTime > startDate)).front();
    delete db;
    return row.sum;
}

bool EntryModel::insertRows(int row, int count, const QModelIndex &parent) {
    qCDebug(timer) << "insert" << row << count;
    if (row != 0 || count != 1) { // supports only inserting in the front
        return false;
    }
    this->beginInsertRows(parent, row, row + count - 1);
    this->endInsertRows();
    return true;
}

int EntryModel::rowCount(const QModelIndex &parent) const {
    (void)parent;
    qCDebug(timer) << "rowCount" << this->entries.size();
    return this->entries.size();
}

int EntryModel::columnCount(const QModelIndex &parent) const {
    qCDebug(timer) << "columnCount" << Entry::columns_count;
    return Entry::columns_count;
}

QVariant EntryModel::data(const QModelIndex &index, int role) const {
    const Entry *e = &this->entries[this->entries.size() - index.row() - 1]; // vector grows in the back; items need to grow on the top
    qCDebug(timer) << "data" << index.row() << index.column() << role;
    switch (role) {
        case Entry::roles::DESCRIPTION: {
            return QVariant::fromValue(e->description);
        }
        case Entry::roles::TIME_MS: {
            return QVariant::fromValue(e->time_ms);
        }
        case Entry::roles::START: {
            QString d(date::format("%F", date::floor<hours>(e->start_time)).c_str());
            return QVariant::fromValue(d);
        }
    }
    return QVariant();
}
