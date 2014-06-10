#include "motioncontroller.h"

#include <QAbstractTableModel>
#include "glwidget.h"

#include <qmath.h>
#include <QDebug>

MotionController::MotionController(QObject *parent) :
    QObject(parent),
    mGLWidget(NULL),
    mRotX(0),
    mRotY(0),
    mRotZ(0),
    mRotAmplitude(16),
    mRotCircle(180.0 / M_PI)
{
}
/**
********************************************************************************
**/
QAbstractTableModel *MotionController::getModel() const
{
    return mModel;
}
/**
********************************************************************************
**/
void MotionController::setModel(QAbstractTableModel *value)
{
    mModel = value;
    if (mModel)
    {
        connect(mModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(slotUpdateMovement()));
    }
}
/**
********************************************************************************
**/
void MotionController::slotUpdateMovement()
{
    if (mGLWidget /*&& mModel*/)
    {
        if (mModel->hasIndex(0, 1))
        {
            int lCurrentX = mModel->index(0, 1).data().toInt();
            if (mRotX != lCurrentX)
            {
                mRotX = lCurrentX;
                lCurrentX -= 5;
                if (qAbs(lCurrentX) < 510.0)
                {
                    double lAngle = asin(lCurrentX / 510.0) * mRotCircle;
//                    qDebug() << "X: " << lCurrentX;
                    mGLWidget->setXRotation(lAngle * mRotAmplitude);
                }
                else
                {
//                    qDebug() << "error: X " << mRotX;
                }
            }
        }
        if (mModel->hasIndex(0, 2))
        {
            int lCurrentY = mModel->index(0, 2).data().toInt();
            if (mRotY != lCurrentY)
            {
                mRotY = lCurrentY;
                lCurrentY -= 12;
                if (qAbs(lCurrentY) < 508.0)
                {
                    double lAngle = asin(lCurrentY / 508.0) * mRotCircle;
//                qDebug() << "Y: " << lCurrentY;
                    mGLWidget->setYRotation(lAngle * mRotAmplitude);
                }
                else
                {
//                    qDebug() << "error: Y " << mRotY;
                }
            }
        }
        if (mModel->hasIndex(0, 3))
        {
            int lCurrentZ = mModel->index(0, 3).data().toInt();
            if (mRotZ != lCurrentZ)
            {
                mRotZ = lCurrentZ;
                lCurrentZ -= 40;
                if (qAbs(lCurrentZ) < 515.0)
                {
                    double lAngle = asin((lCurrentZ) / 515.0) * mRotCircle;
//                qDebug() << "Z: " << lAngle;
                    mGLWidget->setZRotation(lAngle * mRotAmplitude);
                }
                else
                {
//                    qDebug() << "error: Z " << lCurrentZ;
                }
            }
        }
    }
}
/**
********************************************************************************
**/
GLWidget *MotionController::getGLWidget() const
{
    return mGLWidget;
}
/**
********************************************************************************
**/
void MotionController::setGLWidget(QWidget *value)
{
    mGLWidget = qobject_cast<GLWidget *> (value);
}
/**
********************************************************************************
**/
