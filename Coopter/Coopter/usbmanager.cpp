#include "usbmanager.h"

#include <QTimer>
#include <qmath.h>

#include <QDebug>

#define SAPMLE_RATE 600
#define CUT_OFF_LOW 180
#define CUT_OFF_HIGH 200

#define SAMPLE_COUNT 30

USBManager::USBManager(QObject *parent) :
    QObject(parent),
    mVID(0x04B4),
    mPID(0xF232),
    mUSBDevice(NULL),
    mDeviceHandle(NULL),
    mDeviceState(false),
    mLogger(0),
    mConnectorChecker(NULL),

    mSampleArrayGyroX(NULL),
    mSampleArrayGyroY(NULL),
    mSampleArrayGyroZ(NULL),

    mGyroXX({0,0,0}),
    mGyroXY({0,0,0}),

    mGyroYX({0,0,0}),
    mGyroYY({0,0,0}),

    mGyroZX({0,0,0}),
    mGyroZY({0,0,0}),
    mFilterType(FilterParams::NONE)
{
    slotInitUSB();
    mSampleArrayGyroX = new double[SAMPLE_COUNT];
    mSampleArrayGyroY = new double[SAMPLE_COUNT];
    mSampleArrayGyroZ = new double[SAMPLE_COUNT];
    for (int i = 0; i < SAMPLE_COUNT; i++)
    {
        mSampleArrayGyroX[i] = 0;
        mSampleArrayGyroY[i] = 0;
        mSampleArrayGyroZ[i] = 0;
    }

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
    delete [] mSampleArrayGyroX;
    delete [] mSampleArrayGyroY;
    delete [] mSampleArrayGyroZ;
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
        usb_control_msg(mDeviceHandle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_IN, 0x33, 0, 0, lBuffer, n, 100);

//        qDebug() << QString().fromLatin1(lBuffer, n);
        QStringList lMessage = QString(lBuffer).split("\n");
        QString lBarometerInfo = QString(lMessage.at(0)).remove("P = ");
        QString lTemperatureInfo = QString(lMessage.at(1)).remove("t = ");
        QString lHigh = QString(lMessage.at(2)).remove("h = ");
//        qDebug() << lBarometerInfo;
//        qDebug() << lTemperatureInfo;
//        qDebug() << lHigh;
//        qDebug() << lMessage;
        for (int i = 1; i < SAMPLE_COUNT; i++)
        {
            mSampleArrayGyroX[i] = mSampleArrayGyroX[i-1];
            mSampleArrayGyroY[i] = mSampleArrayGyroY[i-1];
            mSampleArrayGyroZ[i] = mSampleArrayGyroZ[i-1];
        }
        mSampleArrayGyroX[0] = (int) ((char) lBuffer[35] & 0xFF) | ((char)(lBuffer[36] & 0xFF) << 8);
        mSampleArrayGyroY[0] = (int) ((char) lBuffer[37] & 0xFF) | ((char)(lBuffer[38] & 0xFF) << 8);
        mSampleArrayGyroZ[0] = (int) ((char) lBuffer[39] & 0xFF) | ((char)(lBuffer[40] & 0xFF) << 8);
//        qDebug() << mSampleArrayGyroX[0];

        if (mFilterType == FilterParams::LPF)
        {
            low_pass_filter(mSampleArrayGyroX, SAPMLE_RATE, CUT_OFF_LOW, mGyroXX, mGyroXY);
            low_pass_filter(mSampleArrayGyroY, SAPMLE_RATE, CUT_OFF_LOW, mGyroYX, mGyroYY);
            low_pass_filter(mSampleArrayGyroZ, SAPMLE_RATE, CUT_OFF_LOW, mGyroZX, mGyroZY);
        }
        else if (mFilterType == FilterParams::BPF)
        {
            band_pass_filter(mSampleArrayGyroX, SAPMLE_RATE, CUT_OFF_HIGH, CUT_OFF_LOW, mGyroXX, mGyroXY);
            band_pass_filter(mSampleArrayGyroY, SAPMLE_RATE, CUT_OFF_HIGH, CUT_OFF_LOW, mGyroYX, mGyroYY);
            band_pass_filter(mSampleArrayGyroZ, SAPMLE_RATE, CUT_OFF_HIGH, CUT_OFF_LOW, mGyroZX, mGyroZY);
        }


        rResult.append(mSampleArrayGyroX[0]);
        rResult.append(mSampleArrayGyroY[0]);
        rResult.append(mSampleArrayGyroZ[0]);

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
                    qDebug() << "lDeviceHandle: " << lDeviceHandle;
                }
//                qDebug() << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
//                qDebug() << "Pid: " << QString("%1").arg(lCurrentDevice->descriptor.idProduct, 0, 16);
//                qDebug() << "Vid: " << QString("%1").arg(lCurrentDevice->descriptor.idVendor, 0, 16);
//                qDebug() << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
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
//                qDebug() << metaObject()->className() << " device is already opened!";
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
//        delete mDeviceHandle;
//        mDeviceHandle = NULL;
    }
    mDeviceState = false;
}
/*
****************************************************************************************************
*/
void USBManager::slotDebugLogger()
{
//    qDebug() << "Device state: " << mDeviceState;
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
void USBManager::getLPCoefficientsButterworth2Pole(const int pSamplerate, const double pCutoff, double* const pAx, double* const pBy)
{
    const double PI      = 3.1415926535897932385;
    const double sqrt2 = 1.4142135623730950488;

    double QcRaw  = (2 * PI * CUT_OFF_LOW) / pSamplerate; // Find cutoff frequency in [0..PI]
    double QcWarp = qTan(CUT_OFF_LOW); // Warp cutoff frequency

    double gain = 1 / (1+sqrt2/QcWarp + 2/(QcWarp*QcWarp));
    pBy[2] = (1 - sqrt2/QcWarp + 2/(QcWarp*QcWarp)) * gain;
    pBy[1] = (2 - 2 * 2/(QcWarp*QcWarp)) * gain;
    pBy[0] = 1;
    pAx[0] = 1 * gain;
    pAx[1] = 2 * gain;
    pAx[2] = 1 * gain;
}
/**
********************************************************************************
**/
void USBManager::low_pass_filter(double *pSampleArray, int pSampleRate, int pCutOffFreq, double *pX, double *pY)
{
   double ax[3];
   double by[3];

   getLPCoefficientsButterworth2Pole(pSampleRate, pCutOffFreq, ax, by);

   for (int i=0;i<SAMPLE_COUNT;i++)
   {
       pX[2] = pX[1]; pX[1] = pX[0];
       pX[0] = pSampleArray[i];
       pY[2] = pY[1]; pY[1] = pY[0];

       pY[0] =   (ax[0] * pX[0] + ax[1] * pX[1] + ax[2] * pX[2]
                    - by[1] * pY[0]
                    - by[2] * pY[1]);

       pSampleArray[i] = pY[0];
   }
}
/**
********************************************************************************
**/
void USBManager::band_pass_filter(double *pSampleArray, double pSampleRate, double pCutOffFreqHigh, double pCutOffFreqLow, double *pX, double *pY)
{
//    qDebug() << "band";
    double m_lambda = M_PI * pCutOffFreqLow / (pSampleRate / 2);
    double m_phi = M_PI * pCutOffFreqHigh / (pSampleRate / 2);

    double mm;

    for(int n = 1; n < SAMPLE_COUNT ; n++)
    {
        mm = n - (SAMPLE_COUNT - 1.0) / 2.0;
        if ( mm == 0.0 )
        {
            pSampleArray[n] = (m_phi - m_lambda) / M_PI * pSampleArray[n - 1];
        }
        else
        {
            pSampleArray[n] = (   sin( mm * m_phi ) - sin( mm * m_lambda )   ) / (mm * M_PI) * pSampleArray[n - 1];
        }
    }
}
FilterParams::FilterType USBManager::getMFilterType() const
{
    return mFilterType;
}

void USBManager::setMFilterType(const FilterParams::FilterType &value)
{
    mFilterType = value;
}


/*
****************************************************************************************************
*/

