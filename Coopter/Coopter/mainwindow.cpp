#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dataconverter.h"
#include "datamonitor.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mDataMonitor(NULL),
    mDataConverter(NULL)
{
    ui->setupUi(this);

    mDataMonitor = new DataMonitor(this);
    ui->MainTableView->setModel(mDataMonitor);

    mDataConverter = new DataConverter(this);
    mDataConverter->setModel(mDataMonitor);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitWindow()
{

}
