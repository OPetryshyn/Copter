#include "pagefilterparameters.h"
#include "ui_pagefilterparameters.h"

//#include <QDebug>

PageFilterParameters::PageFilterParameters(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::PageFilterParameters),
    mSampleRate(0),
    mSamples(0),
    mBandwidth(0),
    mCutOff(0)
{
    ui->setupUi(this);

    connectSignals(true);
    updateValues();
}

PageFilterParameters::~PageFilterParameters()
{
    connectSignals(false);
    delete ui;
}

void PageFilterParameters::updateValues()
{
    if (mSampleRate != ui->doubleSpinBoxSampleRate->value())
    {
        mSampleRate = ui->doubleSpinBoxSampleRate->value();
//        qDebug() << "mSampleRate : " << mSampleRate;
    }
    if (mCutOff != ui->doubleSpinBoxCutOff->value())
    {
        mCutOff = ui->doubleSpinBoxCutOff->value();
//        qDebug() << "mCutOff : " << mCutOff;
    }
    if (mBandwidth != ui->doubleSpinBoxBandWidth->value())
    {
        mBandwidth = ui->doubleSpinBoxBandWidth->value();
//        qDebug() << "mBandwidth : " << mBandwidth;
    }
    if (mSamples != ui->spinBoxSamples->value())
    {
        mSamples = ui->spinBoxSamples->value();
//        qDebug() << "mSamples : " << mSamples;
    }
}
/**
********************************************************************************
**/
void PageFilterParameters::connectSignals(bool pState)
{
    if (pState)
    {
        connect(ui->doubleSpinBoxSampleRate, SIGNAL(valueChanged(double)), this, SLOT(updateValues()), Qt::UniqueConnection);
        connect(ui->doubleSpinBoxCutOff, SIGNAL(valueChanged(double)), this, SLOT(updateValues()), Qt::UniqueConnection);
        connect(ui->doubleSpinBoxBandWidth, SIGNAL(valueChanged(double)), this, SLOT(updateValues()), Qt::UniqueConnection);
        connect(ui->spinBoxSamples, SIGNAL(valueChanged(int)), this, SLOT(updateValues()), Qt::UniqueConnection);
    }
    else
    {
        disconnect(ui->doubleSpinBoxSampleRate, SIGNAL(valueChanged(double)), this, SLOT(updateValues()));
        disconnect(ui->doubleSpinBoxCutOff, SIGNAL(valueChanged(double)), this, SLOT(updateValues()));
        disconnect(ui->doubleSpinBoxBandWidth, SIGNAL(valueChanged(double)), this, SLOT(updateValues()));
        disconnect(ui->spinBoxSamples, SIGNAL(valueChanged(int)), this, SLOT(updateValues()));
    }
}
double PageFilterParameters::getMSampleRate() const
{
    return mSampleRate;
}

void PageFilterParameters::setMSampleRate(double value)
{
    mSampleRate = value;
}

double PageFilterParameters::getMCutOff() const
{
    return mCutOff;
}

void PageFilterParameters::setMCutOff(double value)
{
    mCutOff = value;
}

double PageFilterParameters::getMBandwidth() const
{
    return mBandwidth;
}

void PageFilterParameters::setMBandwidth(double value)
{
    mBandwidth = value;
}

int PageFilterParameters::getMSamples() const
{
    return mSamples;
}

void PageFilterParameters::setMSamples(int value)
{
    mSamples = value;
}

/**
********************************************************************************
**/
