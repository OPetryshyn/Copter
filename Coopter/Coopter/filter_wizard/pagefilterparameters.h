#ifndef PAGEFILTERPARAMETERS_H
#define PAGEFILTERPARAMETERS_H

#include <QWizardPage>

namespace Ui {
class PageFilterParameters;
}

class PageFilterParameters : public QWizardPage
{
    Q_OBJECT

public:
    explicit PageFilterParameters(QWidget *parent = 0);
    ~PageFilterParameters();

    int getMSamples() const;
    void setMSamples(int value);

    double getMBandwidth() const;
    void setMBandwidth(double value);

    double getMCutOff() const;
    void setMCutOff(double value);

    double getMSampleRate() const;
    void setMSampleRate(double value);

private slots:
    void updateValues();

private:
    void connectSignals(bool pState);

    double mSampleRate;
    double mCutOff;
    double mBandwidth;
    int mSamples;

    Ui::PageFilterParameters *ui;
};

#endif // PAGEFILTERPARAMETERS_H
