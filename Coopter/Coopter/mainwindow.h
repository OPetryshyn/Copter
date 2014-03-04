#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QItemModel;
class DataMonitor;
class DataConverter;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    DataMonitor *mDataMonitor;
    DataConverter *mDataConverter;
    Ui::MainWindow *ui;

    void InitWindow();
};

#endif // MAINWINDOW_H
