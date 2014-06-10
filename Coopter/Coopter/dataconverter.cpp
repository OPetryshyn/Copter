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
    mUSBManager(NULL)
{
    mDataRefresher = new QTimer(this);
    connect(mDataRefresher, SIGNAL(timeout()), this, SLOT(slotUpdateModel()));
    mDataRefresher->start(30);
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
    if (mModel)
    {
        mModel->setData(mModel->index(0, 0), QString("Gyroscope"), Qt::DisplayRole);
        mModel->setData(mModel->index(1, 0), QString("Accelerometer"), Qt::DisplayRole);
        mModel->setData(mModel->index(2, 0), QString("Other"), Qt::DisplayRole);

    }
}
/**
********************************************************************************
**/
USBManager *DataConverter::getUSBManager() const
{
    return mUSBManager;
}
/**
********************************************************************************
**/
void DataConverter::setUSBManager(USBManager *value)
{
    mUSBManager = value;
}
/**
********************************************************************************
**/
void DataConverter::slotUpdateModel()
{
    if (mUSBManager && mUSBManager->IsDeviceOpened() && mModel)
    {
        QVector<int> lDataBuffer;
        lDataBuffer = mUSBManager->getDataVector();
        emit dataRecieved(lDataBuffer);
        if (!lDataBuffer.isEmpty())
        {
            int j = 0;
            for (int i = 0; i < lDataBuffer.count(); i+=3)
            {
//                mModel->setData(mModel->index(j, 0), QVariant(QString("Item %1").arg(j)), Qt::DisplayRole);
                mModel->setData(mModel->index(j, 1), lDataBuffer.at(i), Qt::DisplayRole);
                mModel->setData(mModel->index(j, 2), lDataBuffer.at(i+1), Qt::DisplayRole);
                mModel->setData(mModel->index(j, 3), lDataBuffer.at(i+2), Qt::DisplayRole);
                j++;
            }
            lDataBuffer.clear();
        }
    }
}
/**
********************************************************************************
**/
