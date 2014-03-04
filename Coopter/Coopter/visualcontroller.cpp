#include "visualcontroller.h"
#include "ui_visualcontroller.h"

#include <QKeyEvent>

VisualController::VisualController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisualController)
{
    ui->setupUi(this);
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

    }
}
/*
****************************************************************************************************
*/
