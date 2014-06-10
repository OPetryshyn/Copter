#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dataconverter.h"
#include "datamonitor.h"
#include "visualcontroller.h"
#include "glwidget.h"
#include "motioncontroller.h"
#include "usbmanager.h"

#include <QDebug>

#include <QKeyEvent>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QToolButton>
#include "filter_wizard/wizard.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mUSBManager(NULL),
    mDataMonitor(NULL),
    mDataConverter(NULL),
    mVisualController(NULL),
    mMotionController(NULL),
    mLogFile(),
    mFilterWizard(NULL)
{
    ui->setupUi(this);

    InitWindow();

}
/**
********************************************************************************
**/
MainWindow::~MainWindow()
{
    delete ui;
    if (mVisualController)
    {
        delete mVisualController;
    }
}
/**
********************************************************************************
**/
void MainWindow::connectTracking(bool pState)
{
    if (pState)
    {
        connect(mDataConverter, SIGNAL(dataRecieved(QVector<int>)), this, SLOT(trackAllData(QVector<int>)), Qt::UniqueConnection);
    }
    else
    {
        disconnect(mDataConverter, SIGNAL(dataRecieved(QVector<int>)), this, SLOT(trackAllData(QVector<int>)));
    }
}
/**
********************************************************************************
**/
void MainWindow::trackAllData(QVector<int> pVector)
{

    if (!mLogFile.isOpen())
    {
        QDir lDir(qApp->applicationDirPath() + "/log");
        if (!lDir.exists())
        {
            qDebug() << lDir.mkpath(lDir.absolutePath());
        }
        mLogFile.setFileName(lDir.absolutePath() + "/data.txt");
        if (!mLogFile.open(QFile::Truncate | QFile::ReadWrite))
        {
            qDebug() << "Can`t create file;";
        }

    }
    if (mLogFile.isOpen())
    {
//        int i = 0;
        mLogFile.write(QString("%1\t%2\t%3\n")
                        .arg(pVector.at(0)).arg(pVector.at(1)).arg(pVector.at(2))
                        //.arg(pVector.at(++i)).arg(pVector.at(++i)).arg(pVector.at(++i))
                       .toLocal8Bit()
                        );
        mLogFile.flush();
    }
}
/**
********************************************************************************
**/
void MainWindow::slotAdjustFilter()
{
    mUSBManager->setMFilterType(FilterParams::FilterType (mFilterWizard->getMFilterType()));
    qDebug() << mUSBManager->getMFilterType();
}
/**
********************************************************************************
**/
void MainWindow::InitWindow()
{
    ui->centralWidget->setFocusPolicy(Qt::NoFocus);

    mUSBManager = new USBManager(this);
    mDataMonitor = new DataMonitor(this);
    ui->mDataView->setModel(mDataMonitor);

    mDataConverter = new DataConverter(this);
    mDataConverter->setModel(mDataMonitor);
    mDataConverter->setUSBManager(mUSBManager);

    mVisualController = new VisualController(NULL);

    mMotionController = new MotionController(this);
    mMotionController->setModel(mDataMonitor);
    mMotionController->setGLWidget(ui->dockGLWidget->widget());

    QMenu *lFileMenu = new QMenu(menuBar());
    lFileMenu->setTitle("File");
    lFileMenu->addAction("&Exit", this, SLOT(close()));
    QMenu *lMenu = new QMenu(menuBar());
    lMenu->setTitle("Tools");
    lMenu->addAction("Visual controller", mVisualController, SLOT(show()));
    QAction *lTrackAction = new QAction("Track Data", lMenu);
    lTrackAction->setCheckable(true);
    connect(lTrackAction, SIGNAL(triggered(bool)), this, SLOT(connectTracking(bool)), Qt::UniqueConnection);
    lMenu->addAction(lTrackAction);

    menuBar()->addMenu(lFileMenu);
    menuBar()->addMenu(lMenu);

    mFilterWizard = new Wizard(this);

    ui->mainToolBar->addAction(QIcon(":/tool_btn/set_gnd"), "Set Ground");
    ui->mainToolBar->addAction("Filter wizard", mFilterWizard, SLOT(show()));
    connect(mFilterWizard, SIGNAL(accepted()), this, SLOT(slotAdjustFilter()), Qt::UniqueConnection);

}
/**
********************************************************************************
**/
