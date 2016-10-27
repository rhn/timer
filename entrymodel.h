#ifndef ENTRYMODEL_H
#define ENTRYMODEL_H

#include <vector>
#include <QAbstractTableModel>

class Entry {
public:
    Entry(const int time_ms, const QString description) :
        time_ms(time_ms),
        description(description)
    {}

    static const int columns_count = 2;
    int time_ms;
    QString description;
};

class EntryModel : public QAbstractTableModel
{
    Q_OBJECT
    std::vector<Entry*> entries;
public:
    explicit EntryModel(QObject *parent = 0);
    void add_entry(Entry *e);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    Q_INVOKABLE void add(const int ms, const QString description) {
        return add_entry(new Entry(ms, description));
    }

signals:

public slots:
};

#endif // ENTRYMODEL_H
