#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dataconverter.h"
#include "datamonitor.h"
#include "visualcontroller.h"
#include "glwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mDataMonitor(NULL),
    mDataConverter(NULL),
    mVisualController(NULL)
{
    ui->setupUi(this);

    InitWindow();

}

MainWindow::~MainWindow()
{
    delete ui;
    if (mVisualController)
    {
        delete mVisualController;
    }
//    if (mGLWidget)
//    {
//        delete mGLWidget;
//    }
}

void MainWindow::InitWindow()
{
    mDataMonitor = new DataMonitor(this);
    ui->MainTableView->setModel(mDataMonitor);

    mDataConverter = new DataConverter(this);
    mDataConverter->setModel(mDataMonitor);

    mVisualController = new VisualController(NULL);
//    mGLWidget = new GLWidget(this);

    QMenu *lMenu = new QMenu(menuBar());
    lMenu->setTitle("Tools");
    lMenu->addAction("Visual controller", mVisualController, SLOT(show()));
//    lMenu->addAction("Gl Scene", mGLWidget, SLOT(show()));
    menuBar()->addMenu(lMenu);

}
