#ifndef DATAMONITOR_H
#define DATAMONITOR_H

#include <QAbstractTableModel>



class DataMonitor : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit DataMonitor(QObject *parent = 0);
    QModelIndex index(int pRow, int pColumn, const QModelIndex &pParent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    bool setData(const QModelIndex &pIndex, const QVariant &pValue, int pRole = Qt::DisplayRole);

private:
    int mRowCount;
    int mColCount;
    QHash<QModelIndex, QVariant> mData;
};

#endif // DATAMONITOR_H
