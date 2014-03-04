#include "usbmanager.h"

#include <QTimer>

#include <QDebug>

USBManager::USBManager(QObject *parent) :
    QObject(parent),
    mVID(0x04B4),
    mPID(0xF232),
    mUSBDevice(NULL),
    mDeviceHandle(NULL),
    mDeviceState(false),
    mLogger(0),
    mConnectorChecker(NULL)
{
    slotInitUSB();

    mConnectorChecker = new QTimer(this);
    mConnectorChecker->setTimerType(Qt::PreciseTimer);
    connect(mConnectorChecker, SIGNAL(timeout()), this, SLOT(slotConnect()));
    mConnectorChecker->setInterval(10000);
    mConnectorChecker->start();
}
/**
********************************************************************************
**/
USBManager::~USBManager()
{
    if (mDeviceHandle)
    {
        usb_close(mDeviceHandle);
    }
    mDeviceHandle = NULL;
    mUSBDevice = NULL;
    delete mDeviceHandle;
    delete mUSBDevice;
}
/**
********************************************************************************
**/
bool USBManager::IsDeviceOpened()
{
    return mDeviceState;
}
/**
********************************************************************************
**/
QVector<int> USBManager::getDataVector()
{
    QVector<int> rResult;
    if (mDeviceState)
    {
        const int n = 54;
        char *lBuffer = new char[n];
        usb_control_msg(mDeviceHandle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_IN, 0x33,
                        0, 0, lBuffer, n, 100);

        qDebug() << QString().fromLocal8Bit(lBuffer);
        for (int i = 35; i < n; i += 2)
        {
            rResult.append((int) (lBuffer[i] | lBuffer[i + 1] << 8));
        }
    }
    return rResult;
}
/**
********************************************************************************
**/
void USBManager::slotInitUSB()
{
    usb_init();

    usb_find_busses();
    usb_find_devices();

}

void USBManager::slotConnect()
{
    if (!mDeviceState)
    {

        usb_dev_handle *lDeviceHandle = NULL;
        usb_bus *lDeviceBus = NULL;

        struct usb_device *lCurrentDevice;
        for (lDeviceBus = usb_get_busses(); lDeviceBus != NULL && lDeviceHandle == NULL;
             lDeviceBus = lDeviceBus->next)
        {
            for (lCurrentDevice = lDeviceBus->devices; lCurrentDevice != NULL && lDeviceHandle == NULL;
                 lCurrentDevice = lCurrentDevice->next)
            {
                if (lCurrentDevice->descriptor.idVendor == mVID && lCurrentDevice->descriptor.idProduct == mPID)
                {
                    mUSBDevice = lCurrentDevice;
                    lDeviceHandle = usb_open(lCurrentDevice);
                }
            }
        }
        if (lDeviceHandle)
        {
            mDeviceHandle = lDeviceHandle;
            delete lDeviceHandle;
        }

        mDeviceState = (mDeviceHandle);
    }
    else
    {
        qDebug() << metaObject()->className() << " device is already opened!";
    }
    slotDebugLogger();
}
/*
****************************************************************************************************
*/
void USBManager::slotDisconnect()
{
    if (mDeviceHandle)
    {
        usb_close(mDeviceHandle);
        delete mDeviceHandle;
        mDeviceHandle = NULL;
    }
    mDeviceState = (mDeviceHandle);
}
/*
****************************************************************************************************
*/
void USBManager::slotDebugLogger()
{
    qDebug() << "Device state: " << mDeviceState;
}
/*
****************************************************************************************************
*/
void USBManager::slotConnectSignals(bool pEnable)
{
    if (pEnable)
    {
    }
    else
    {
    }
}
/*
****************************************************************************************************
*/

