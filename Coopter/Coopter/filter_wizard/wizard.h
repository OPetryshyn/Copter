#ifndef WIZARD_H
#define WIZARD_H

#include <QWizard>
#include "libs/linux/qcustomplot/qcustomplot.h"

namespace Ui {
class Wizard;
}

class Wizard : public QWizard
{
    Q_OBJECT

public:
    explicit Wizard(QWidget *parent = 0);
    ~Wizard();


    int getMFilterType() const;
    void setMFilterType(int value);

public slots:
    void nextPage();
    void slotAdjustFilterType();

private:
    Ui::Wizard *ui;
    QCustomPlot *mPlotWidget;
    int mFilterType;
};

#endif // WIZARD_H
