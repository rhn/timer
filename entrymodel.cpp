#include <QStandardPaths>
#include <QDir>

//#include <sqlpp11/sqlite3/sqlite3.h>
#include "entrymodel.h"
#include "logging.h"
//#include "timer_db.h"

//using namespace TimerDB;
//namespace sql = sqlpp::sqlite3;

Q_LOGGING_CATEGORY(timer, "qml")

EntryModel::EntryModel(QObject *parent) : QAbstractTableModel(parent) {}

void EntryModel::add_entry(Entry* e) {
    qCDebug(timer) << "add" << e->time_ms;
    this->entries.push_back(e);
    this->insertRow(0, QModelIndex());
}
/*
static void make_db() {
    QString data_dir_path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir::root().mkpath(data_dir_path);
    sql::connection_config config;
    config.path_to_database = (data_dir_path + "/db.sql").toStdString();
    config.flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
    config.debug = true;
    sql::connection db(config);
    QFile schema(":schema/timer.sql");
    db.execute(schema.readAll().toStdString());
}

void EntryModel::save_data() {


    for (Entry* e : this->entries) {

    }
}*/

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
