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
    mConnectorChecker->start(10000);
    slotConnect();
}
/*
****************************************************************************************************
*/
USBManager::~USBManager()
{
    if (mDeviceHandle)
    {
        usb_close(mDeviceHandle);
    }
//    delete mUSBDevice;
//    delete mDeviceHandle;
//    mDeviceHandle = NULL;
}
/*
****************************************************************************************************
*/
bool USBManager::IsDeviceOpened()
{
    return mDeviceState;
}
/*
****************************************************************************************************
*/
QVector<int> USBManager::getDataVector()
{
    QVector<int> rResult;
    if (mDeviceState)
    {
        const int n = 54;
        char *lBuffer = new char[n];
        usb_control_msg(mDeviceHandle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_IN, 0x33,
                        0, 0, lBuffer, n, 100);

//        qDebug() << QString().fromLatin1(lBuffer, n);

        rResult.append(lBuffer[35] | (lBuffer[36] << 8));
        rResult.append(lBuffer[37] | (lBuffer[38] << 8));
        rResult.append(lBuffer[39] | (lBuffer[40] << 8));

        rResult.append(lBuffer[41] | (lBuffer[42] << 8));
        rResult.append(lBuffer[43] | (lBuffer[44] << 8));
        rResult.append(lBuffer[45] | (lBuffer[46] << 8));

        rResult.append(lBuffer[47] | (lBuffer[48] << 8));
        rResult.append(lBuffer[49] | (lBuffer[50] << 8));
        rResult.append(lBuffer[51] | (lBuffer[52] << 8));
        delete [] lBuffer;
    }
    return rResult;
}
/*
****************************************************************************************************
*/
void USBManager::slotInitUSB()
{
    usb_init();

    usb_find_busses();
    usb_find_devices();

}
/*
****************************************************************************************************
*/
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
            delete mDeviceHandle;
            mDeviceHandle = lDeviceHandle;
        }

        mDeviceState = (mDeviceHandle);
    }
    else
    {
            int lResult = usb_claim_interface(mDeviceHandle, usb_device(mDeviceHandle)->config->interface->altsetting->iInterface);
            if (lResult > 0)
            {
                usb_reset(mDeviceHandle);
                qDebug() << "reset";
            }
            else
            {
                qDebug() << metaObject()->className() << " device is already opened!";
            }
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
    mDeviceState = false;
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

