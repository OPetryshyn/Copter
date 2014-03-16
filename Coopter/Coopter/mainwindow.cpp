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

void MainWindow::keyPressEvent(QKeyEvent *pEvent)
{
    if (((pEvent->key() == Qt::Key_Left) || (pEvent->key() == Qt::Key_Right)) && pEvent->modifiers() == Qt::SHIFT)
    {
        if (pEvent->key() == Qt::Key_Left)
        {
            if (ui->stackedWidget->currentIndex() > 0)
            {
                ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 1);
            }
            else
            {
                ui->stackedWidget->setCurrentIndex(ui->stackedWidget->count() - 1);
            }
        }
        else
        {
            if (ui->stackedWidget->currentIndex() < ui->stackedWidget->count() - 1)
            {
                ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
            }
            else
            {
                ui->stackedWidget->setCurrentIndex(0);
            }
        }
    }
}

void MainWindow::InitWindow()
{
    ui->centralWidget->setFocusPolicy(Qt::NoFocus);

    mDataMonitor = new DataMonitor(this);
    ui->MainTableView->setModel(mDataMonitor);

    mDataConverter = new DataConverter(this);
    mDataConverter->setModel(mDataMonitor);

    mVisualController = new VisualController(NULL);

    mMotionController = new MotionController(this);
    mMotionController->setModel(mDataMonitor);
    mMotionController->setGLWidget(ui->page_2);

    QMenu *lMenu = new QMenu(menuBar());
    lMenu->setTitle("Tools");
    lMenu->addAction("Visual controller", mVisualController, SLOT(show()));
//    lMenu->addAction("Gl Scene", mGLWidget, SLOT(show()));
    menuBar()->addMenu(lMenu);

}
