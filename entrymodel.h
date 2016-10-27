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

    enum roles {
        TIME_MS = Qt::UserRole,
        DESCRIPTION,
        START,
    };

    static const int columns_count = 3;
    int time_ms;
    QString description;
};

class EntryModel : public QAbstractTableModel
{
    Q_OBJECT
    std::vector<Entry*> entries;
public:
    explicit EntryModel(QObject *parent = 0);
    QHash<int, QByteArray> roleNames() const {
        return {{Entry::roles::TIME_MS, "time"},
                {Entry::roles::DESCRIPTION, "description"},
                {Entry::roles::START, "start"}};
    }

  //  void add_entry(Entry *e);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;
    //bool insertRows(int row, int count, const QModelIndex &parent);
    QVariant data(const QModelIndex &index, int role) const;
    Q_INVOKABLE void add(const int ms, const QString description) {
    //    return add_entry(new Entry(ms, description));
    }
signals:

public slots:
};

#endif // ENTRYMODEL_H
