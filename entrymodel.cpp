#include "entrymodel.h"
#include "logging.h"

Q_LOGGING_CATEGORY(timer, "qml")

EntryModel::EntryModel(QObject *parent) : QAbstractTableModel(parent) {
    this->entries.push_back(new Entry(1, "sffe"));
}

/*void EntryModel::add_entry(Entry* e) {
    this->entries.push_back(e);
    this->insertRow(0, QModelIndex());
}

bool EntryModel::insertRows(int row, int count, const QModelIndex &parent) {
    if (row != 0 || count != 1) { // supports only inserting in the front
        return false;
    }
    this->beginInsertRows(parent, row, row + count + 1);
    this->endInsertRows();
    return true;
}
*/
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
    Entry *e = this->entries[index.row()];
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
