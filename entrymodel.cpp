#include <QStandardPaths>
#include <QDir>

#include <sqlpp11/sqlite3/sqlite3.h>
#include <sqlpp11/sqlpp11.h>
#include "entrymodel.h"
#include "logging.h"
#include "timer_db.h"

using namespace TimerDB;
namespace sql = sqlpp::sqlite3;

Q_LOGGING_CATEGORY(timer, "qml")

EntryModel::EntryModel(QObject *parent) : QAbstractTableModel(parent) {}

void EntryModel::add_entry(Entry* e) {
    qCDebug(timer) << "add" << e->time_ms;
    this->entries.push_back(e);
    this->insertRow(0, QModelIndex());
}

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

void EntryModel::save_data() {
    sql::connection *db = get_db();
    Entries ent_table;
    for (Entry* e : this->entries) {
        auto param = sql::insert_or_replace_into(ent_table) \
                .set(ent_table.id = sqlpp::tvin(e->id),
                     ent_table.description = e->description.toStdString(),
                     ent_table.duration = e->time_ms,
                     ent_table.startTime = e->start_time);
        e->id = (*db)(param);
    }
    delete db;
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
    Entry *e = this->entries[this->entries.size() - index.row() - 1]; // vector grows in the back; items need to grow on the top
    qCDebug(timer) << "data" << index.row() << index.column() << role;
    switch (role) {
        case Entry::roles::DESCRIPTION: {
            return QVariant::fromValue(e->description);
        }
        case Entry::roles::TIME_MS: {
            return QVariant::fromValue(e->time_ms);
        }
        case Entry::roles::START: {
            return QVariant::fromValue(0);
        }
    }
    return QVariant();
}
