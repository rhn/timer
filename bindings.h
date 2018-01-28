/* generated by rust_qt_binding_generator */
#ifndef BINDINGS_H
#define BINDINGS_H

#include <QObject>
#include <QAbstractItemModel>

class Log;

class Log : public QObject
{
    Q_OBJECT
public:
    class Private;
private:
    Private * m_d;
    bool m_ownsPrivate;
    Q_PROPERTY(quint64 dayTotal READ dayTotal NOTIFY dayTotalChanged FINAL)
    explicit Log(bool owned, QObject *parent);
public:
    explicit Log(QObject *parent = nullptr);
    ~Log();
    quint64 dayTotal() const;
signals:
    void dayTotalChanged();
};
#endif // BINDINGS_H