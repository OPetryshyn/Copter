#include "pagefiltertype.h"
#include "ui_pagefiltertype.h"

#include <QDebug>

PageFilterType::PageFilterType(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::PageFilterType),
    mFilterType(FilterParams::NONE)
{
    ui->setupUi(this);
    connect(ui->radioButton_LPF, SIGNAL(clicked()), this, SLOT(slotRadioChanged()), Qt::UniqueConnection);
    connect(ui->radioButton_BPF, SIGNAL(clicked()), this, SLOT(slotRadioChanged()), Qt::UniqueConnection);
    connect(ui->radioButton_HPF, SIGNAL(clicked()), this, SLOT(slotRadioChanged()), Qt::UniqueConnection);
    connect(ui->radioButton_NONE, SIGNAL(clicked()), this, SLOT(slotRadioChanged()), Qt::UniqueConnection);
}

PageFilterType::~PageFilterType()
{
    delete ui;
}
/**
********************************************************************************
**/
FilterParams::FilterType PageFilterType::getMFilterType() const
{
    return mFilterType;
}
/**
********************************************************************************
**/
void PageFilterType::setMFilterType(const FilterParams::FilterType &value)
{
    mFilterType = value;
}
/**
********************************************************************************
**/
void PageFilterType::slotRadioChanged()
{
    if (ui->radioButton_HPF->isChecked())
    {
        setMFilterType(FilterParams::HPF);
    }
    else if (ui->radioButton_LPF->isChecked())
    {
        setMFilterType(FilterParams::LPF);
    }
    else if (ui->radioButton_BPF->isChecked())
    {
        setMFilterType(FilterParams::BPF);
    }
    else if (ui->radioButton_NONE->isChecked())
    {
        setMFilterType(FilterParams::NONE);
    }
    emit sFilterTypeChanged();
}
/**
********************************************************************************
**/
//void PageFilterType::setPlotWidget(const QCustomPlot *pWidget)
//{
//    if (pWidget && pWidget != mPlotWidget)
//    {
//        mPlotWidget = pWidget;
//    }
//}
