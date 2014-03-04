#ifndef DATACONVERTER_H
#define DATACONVERTER_H

#include <QObject>

class QAbstractTableModel;
class USBManager;
class QTimer;

class DataConverter : public QObject
{
    Q_OBJECT
public:
    explicit DataConverter(QObject *parent = 0);

    QAbstractTableModel *getModel() const;
    void setModel(QAbstractTableModel *value);

private:
    QTimer *mDataRefresher;
    QAbstractTableModel *mModel;
    USBManager *mManager;

private slots:
    void slotUpdateModel();
};

#endif // DATACONVERTER_H
