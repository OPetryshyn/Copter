#ifndef USBMANAGER_H
#define USBMANAGER_H

#include <QObject>
#if defined(Q_OS_LINUX)
#include "libs/linux/libusb/usb.h"
#elif defined(Q_OS_WIN)
#include "libs/win/lusb0_usb.h"
#endif
class QTimer;

class USBManager : public QObject
{
    Q_OBJECT
public:
    explicit USBManager(QObject *parent = 0);
    ~USBManager();

    bool IsDeviceOpened();

    QVector<int> getDataVector();

public slots:
    void slotInitUSB();
    void slotConnect();
    void slotDisconnect();
    void slotDebugLogger();

private slots:
    void slotConnectSignals(bool pEnable = true);

private:
    ushort mVID;
    ushort mPID;

    struct usb_device *mUSBDevice;
    usb_dev_handle *mDeviceHandle;

    bool mDeviceState;
    int mLogger;

    QTimer *mConnectorChecker;

};

#endif // USBMANAGER_H
