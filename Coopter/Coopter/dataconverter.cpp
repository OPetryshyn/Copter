#include "dataconverter.h"
#include "usbmanager.h"

#include <QAbstractTableModel>
#include <QTimer>
#include <QVector>
#include <QDebug>

DataConverter::DataConverter(QObject *parent) :
    QObject(parent),
    mDataRefresher(NULL),
    mModel(NULL),
    mManager(NULL)
{
    mManager = new USBManager(this);
    mDataRefresher = new QTimer(this);
    connect(mDataRefresher, SIGNAL(timeout()), this, SLOT(slotUpdateModel()));
    mDataRefresher->start(100);
}
/**
********************************************************************************
**/
QAbstractTableModel *DataConverter::getModel() const
{
    return mModel;
}
/**
********************************************************************************
**/
void DataConverter::setModel(QAbstractTableModel *value)
{
    mModel = value;
}
/**
********************************************************************************
**/
void DataConverter::slotUpdateModel()
{
    if (mManager->IsDeviceOpened() && mModel)
    {
        QVector<int> lDataBuffer;
        lDataBuffer = mManager->getDataVector();
        int j = 0;
        for (int i = 0; i < lDataBuffer.count(); i+=3)
        {
            mModel->setData(mModel->index(j, 0), QVariant(QString("Item %1").arg(j)), Qt::DisplayRole);
            mModel->setData(mModel->index(j, 1), lDataBuffer.at(i), Qt::DisplayRole);
            mModel->setData(mModel->index(j, 2), lDataBuffer.at(i), Qt::DisplayRole);
            mModel->setData(mModel->index(j, 3), lDataBuffer.at(i), Qt::DisplayRole);
            j++;
        }
        lDataBuffer.clear();
    }
}
/**
********************************************************************************
**/
