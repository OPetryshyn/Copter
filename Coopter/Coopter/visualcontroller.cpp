#include "visualcontroller.h"
#include "ui_visualcontroller.h"

#include <QKeyEvent>

VisualController::VisualController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisualController)
{
    ui->setupUi(this);
    connect(ui->pushButtonDown, SIGNAL(clicked()), this, SLOT(slotButtonDownClick()));
    connect(ui->pushButtonUp, SIGNAL(clicked()), this, SLOT(slotButtonUpClick()));
    connect(ui->pushButtonLeft, SIGNAL(clicked()), this, SLOT(slotButtonLeftClick()));
    connect(ui->pushButtonRight, SIGNAL(clicked()), this, SLOT(slotButtonRightClick()));
}
/*
****************************************************************************************************
*/
VisualController::~VisualController()
{
    delete ui;
}
/*
****************************************************************************************************
*/
void VisualController::slotButtonUpClick()
{
    qDebug("Up");
}
/*
****************************************************************************************************
*/
void VisualController::slotButtonDownClick()
{
    qDebug("Down");
}
/*
****************************************************************************************************
*/
void VisualController::slotButtonLeftClick()
{
    qDebug("Left");
}
/*
****************************************************************************************************
*/
void VisualController::slotButtonRightClick()
{
    qDebug("Right");
}
/*
****************************************************************************************************
*/
void VisualController::keyPressEvent(QKeyEvent *pEvent)
{
    if (pEvent->key() == Qt::Key_Up)
    {
        slotButtonUpClick();
    }
    else if (pEvent->key() == Qt::Key_Down)
    {
        slotButtonDownClick();
    }
    else if (pEvent->key() == Qt::Key_Right)
    {
        slotButtonRightClick();
    }
    else if (pEvent->key() == Qt::Key_Left)
    {
        slotButtonLeftClick();
    }
}
/*
****************************************************************************************************
*/
