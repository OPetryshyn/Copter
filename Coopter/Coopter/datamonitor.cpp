#include "datamonitor.h"

DataMonitor::DataMonitor(QObject *parent) :
    QAbstractTableModel(parent),
    mRowCount(0),
    mColCount(0)
{
}
/*
****************************************************************************************************
*/
QModelIndex DataMonitor::index(int pRow, int pColumn, const QModelIndex &pParent) const
{
    Q_UNUSED(pParent);
    if ((pRow < 0) || (pColumn < 0))
    {
        return QModelIndex();
    }

    return createIndex(pRow, pColumn);
}
/*
****************************************************************************************************
*/
QModelIndex DataMonitor::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}
/*
****************************************************************************************************
*/
QVariant DataMonitor::data(const QModelIndex &index, int role) const
{
    QVariant rResult;
    if (index.isValid())
    {
        if (role == Qt::DisplayRole)
        {
            rResult = mData.value(qMakePair(index.row(), index.column()));
        }
    }
    return rResult;
}
/*
****************************************************************************************************
*/
int DataMonitor::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mRowCount;
}
/*
****************************************************************************************************
*/
int DataMonitor::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mColCount;
}
/*
****************************************************************************************************
*/
bool DataMonitor::setData(const QModelIndex &pIndex, const QVariant &pValue, int pRole)
{
    bool rResult(false);
    if (pIndex.isValid())
    {
        if (pRole == Qt::DisplayRole)
        {
            if (pIndex.column() > mColCount)
            {
                int lLastCol = mColCount - 1;
                if(lLastCol < 0)
                {
                    lLastCol = 0;
                }
                beginInsertColumns(QModelIndex() , lLastCol, pIndex.column());
                mColCount = pIndex.column() + 1;
                endInsertColumns();
            }
            if (pIndex.row() > mRowCount)
            {
                int lLastRow = mRowCount - 1;
                if(lLastRow < 0)
                {
                    lLastRow = 0;
                }
                beginInsertRows(QModelIndex(), lLastRow, pIndex.row());
                mRowCount = pIndex.row() + 1;
                endInsertRows();
            }
            mData[qMakePair(pIndex.row(), pIndex.column())] = pValue;
            emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
        }
    }
    return rResult;
}
/*
****************************************************************************************************
*/
