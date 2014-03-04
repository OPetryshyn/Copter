#ifndef USBMANAGER_H
#define USBMANAGER_H

#include <QObject>
#include "libs/lusb0_usb.h"

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
