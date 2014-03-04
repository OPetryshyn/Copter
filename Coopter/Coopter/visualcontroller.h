#ifndef VISUALCONTROLLER_H
#define VISUALCONTROLLER_H

#include <QWidget>

namespace Ui {
class VisualController;
}

class VisualController : public QWidget
{
    Q_OBJECT

public:
    explicit VisualController(QWidget *parent = 0);
    ~VisualController();

public slots:
    void slotButtonUpClick();
    void slotButtonDownClick();
    void slotButtonLeftClick();
    void slotButtonRightClick();

protected:
    void keyPressEvent(QKeyEvent *pEvent);

private:
    Ui::VisualController *ui;
};

#endif // VISUALCONTROLLER_H
