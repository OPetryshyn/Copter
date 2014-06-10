#ifndef USBMANAGER_H
#define USBMANAGER_H

#include <QObject>
#if defined(Q_OS_LINUX)
#include "libs/linux/libusb/usb.h"
#elif defined(Q_OS_WIN)
#include "libs/win/lusb0_usb.h"
#endif
#include "FilterTypes.h"

class QTimer;


class USBManager : public QObject
{
    Q_OBJECT
public:
    explicit USBManager(QObject *parent = 0);
    ~USBManager();

    bool IsDeviceOpened();

    QVector<int> getDataVector();

    FilterParams::FilterType getMFilterType() const;
    void setMFilterType(const FilterParams::FilterType &value);

public slots:
    void slotInitUSB();
    void slotConnect();
    void slotDisconnect();
    void slotDebugLogger();

private slots:
    void slotConnectSignals(bool pEnable = true);

private:
    void getLPCoefficientsButterworth2Pole(const int pSamplerate, const double pCutoff, double* const pAx, double* const pBy);
    void low_pass_filter(double *pSampleArray, int pSampleRate, int pCutOffFreq, double *pX, double *pY);
    void band_pass_filter(double *pSampleArray, double pSampleRate, double pCutOffFreqLow, double pCutOffFreqHigh, double *pX, double *pY);

    double *mSampleArrayGyroX;
    double *mSampleArrayGyroY;
    double *mSampleArrayGyroZ;

    double mGyroXX[3];
    double mGyroXY[3];

    double mGyroYX[3];
    double mGyroYY[3];

    double mGyroZX[3];
    double mGyroZY[3];

    ushort mVID;
    ushort mPID;

    struct usb_device *mUSBDevice;
    usb_dev_handle *mDeviceHandle;

    bool mDeviceState;
    int mLogger;

    QTimer *mConnectorChecker;
    FilterParams::FilterType mFilterType;
};

#endif // USBMANAGER_H
