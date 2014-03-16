#include "motioncontroller.h"

#include <QAbstractTableModel>
#include "glwidget.h"

#include <QDebug>

MotionController::MotionController(QObject *parent) :
    QObject(parent),
    mGLWidget(NULL),
    mRotX(0),
    mRotY(0),
    mRotZ(0),
    mRotAmplitude(10)
{
}
QAbstractTableModel *MotionController::getModel() const
{
    return mModel;
}

void MotionController::setModel(QAbstractTableModel *value)
{
    mModel = value;
    if (mModel)
    {
        connect(mModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(slotUpdateMovement()));
    }
}

void MotionController::slotUpdateMovement()
{
    if (mModel->hasIndex(0, 1))
    {
        int lCurrentX = mModel->index(0, 1).data().toInt();
        if (mRotX != lCurrentX)
        {
            mRotX = lCurrentX;
            if (mGLWidget)
            {
                mGLWidget->setXRotation(mRotX * 360 / mRotAmplitude);
            }
        }
    }
    if (mModel->hasIndex(0, 2))
    {
        int lCurrentY = mModel->index(0, 2).data().toInt();
        if (mRotY != lCurrentY)
        {
            mRotY = lCurrentY;
            if (mGLWidget)
            {
                mGLWidget->setYRotation(mRotY * 360 / mRotAmplitude);
            }
        }
    }
    if (mModel->hasIndex(0, 2))
    {
        int lCurrentZ = mModel->index(0, 2).data().toInt();
        if (mRotZ != lCurrentZ)
        {
            mRotZ = lCurrentZ;
            if (mGLWidget)
            {
                mGLWidget->setZRotation(mRotZ * 360 / mRotAmplitude);
            }
        }
    }
}
GLWidget *MotionController::getGLWidget() const
{
    return mGLWidget;
}

void MotionController::setGLWidget(GLWidget *value)
{
    mGLWidget = value;
}


