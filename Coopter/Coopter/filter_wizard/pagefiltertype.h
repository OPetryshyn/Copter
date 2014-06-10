#ifndef PAGEFILTERTYPE_H
#define PAGEFILTERTYPE_H

#include <QWizardPage>
#include "FilterTypes.h"

namespace Ui {
class PageFilterType;
}

//class QCustomPlot;

class PageFilterType : public QWizardPage
{
    Q_OBJECT

public:
    //Q_DECLARE_FLAGS(FilterTypes, FilterType);

    explicit PageFilterType(QWidget *parent = 0);
    ~PageFilterType();

//    void setPlotWidget(const QCustomPlot *pWidget);

    FilterParams::FilterType getMFilterType() const;
    void setMFilterType(const FilterParams::FilterType &value);

public slots:
    void slotRadioChanged();

signals:
    void sFilterTypeChanged();

private:
//        QCustomPlot *mPlotWidget;
    Ui::PageFilterType *ui;
    FilterParams::FilterType mFilterType;
};

#endif // PAGEFILTERTYPE_H
