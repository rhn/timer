#include "entrymodel.h"


EntryModel::EntryModel(QObject *parent) : QAbstractTableModel(parent) {}

void EntryModel::add_entry(Entry* e) {
    this->entries.push_back(e);
}
int EntryModel::rowCount(const QModelIndex &parent) const {
    return this->entries.size();
}

int EntryModel::columnCount(const QModelIndex &parent) const {
    return Entry::columns_count;
}

QVariant EntryModel::data(const QModelIndex &index, int role) const {
    Entry *e = this->entries[index.row()];
    switch (index.column()) {
        case 0: {
            return QVariant::fromValue(e->description);
        }
        case 1: {
            return QVariant::fromValue(e->time_ms);
        }
        case 2: {
            return QVariant::fromValue(0);
        }
    }
}
