#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QItemModel;
class DataMonitor;
class DataConverter;
class VisualController;
class GLWidget;
class MotionController;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    DataMonitor *mDataMonitor;
    DataConverter *mDataConverter;
    VisualController *mVisualController;
    GLWidget *mGLWidget;
    MotionController *mMotionController;
    Ui::MainWindow *ui;

    void InitWindow();
};

#endif // MAINWINDOW_H
