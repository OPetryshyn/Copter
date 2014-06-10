#include "wizard.h"
#include "ui_wizard.h"

#include "pagefiltertype.h"

#include <QVBoxLayout>
#include <QDebug>

Wizard::Wizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::Wizard),
    mPlotWidget(NULL),
    mFilterType(0)
{
    ui->setupUi(this);
    mPlotWidget = new QCustomPlot(this);
    connect(this, SIGNAL(currentIdChanged(int)), this, SLOT(nextPage()));
    connect(ui->wizardPage1, SIGNAL(sFilterTypeChanged()), this, SLOT(slotAdjustFilterType()));
}

Wizard::~Wizard()
{
    delete ui;
}
/**
********************************************************************************
**/
void Wizard::slotAdjustFilterType()
{
    mFilterType = ui->wizardPage1->getMFilterType();
}
/**
********************************************************************************
**/
void Wizard::nextPage()
{
//    qDebug() << "Set page";
    QWizardPage *lPage = currentPage();
    if (lPage)
    {
        QWidget *lPlotWidget = lPage->findChild<QWidget*> (QString("plotPreview"));
//        qDebug() << "lPlotWidget: " << lPlotWidget;
        if (lPlotWidget)
        {
            if (mPlotWidget->parent() != NULL)
            {
                mPlotWidget->setParent(NULL);
            }
            mPlotWidget->setParent(lPage);
            if (lPlotWidget->layout() == NULL)
            {
                QHBoxLayout *lHLayout = new QHBoxLayout(lPlotWidget);
                Q_UNUSED(lHLayout);
            }
            lPlotWidget->layout()->addWidget(mPlotWidget);
            lPlotWidget = mPlotWidget;
        }
    }
}
int Wizard::getMFilterType() const
{
    return mFilterType;
}

void Wizard::setMFilterType(int value)
{
    mFilterType = value;
}

