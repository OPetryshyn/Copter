#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dataconverter.h"
#include "datamonitor.h"
#include "visualcontroller.h"
#include "glwidget.h"
#include "motioncontroller.h"

#include <QKeyEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mDataMonitor(NULL),
    mDataConverter(NULL),
    mVisualController(NULL),
    mMotionController(NULL)
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
    ui->centralWidget->setFocusPolicy(Qt::NoFocus);

    mDataMonitor = new DataMonitor(this);
    ui->mDataView->setModel(mDataMonitor);

    mDataConverter = new DataConverter(this);
    mDataConverter->setModel(mDataMonitor);

    mVisualController = new VisualController(NULL);

    mMotionController = new MotionController(this);
    mMotionController->setModel(mDataMonitor);
    mMotionController->setGLWidget(ui->dockGLWidget->widget());

    QMenu *lMenu = new QMenu(menuBar());
    lMenu->setTitle("Tools");
    lMenu->addAction("Visual controller", mVisualController, SLOT(show()));
//    lMenu->addAction("Gl Scene", mGLWidget, SLOT(show()));
    menuBar()->addMenu(lMenu);

}
