#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>

namespace Ui {
class MainWindow;
}

class QItemModel;
class DataMonitor;
class DataConverter;
class VisualController;
class GLWidget;
class MotionController;
class USBManager;

class Wizard;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void connectTracking(bool pState);
    void trackAllData(QVector<int> pVector);
    void slotAdjustFilter();

private:
    Wizard *mFilterWizard;
    QFile mLogFile;
    USBManager *mUSBManager;
    DataMonitor *mDataMonitor;
    DataConverter *mDataConverter;
    VisualController *mVisualController;
    GLWidget *mGLWidget;
    MotionController *mMotionController;
    Ui::MainWindow *ui;

    void InitWindow();
};

#endif // MAINWINDOW_H
