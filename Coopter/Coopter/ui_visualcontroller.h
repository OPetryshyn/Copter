/********************************************************************************
** Form generated from reading UI file 'visualcontroller.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VISUALCONTROLLER_H
#define UI_VISUALCONTROLLER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VisualController
{
public:
    QGridLayout *gridLayout_2;
    QPushButton *pushButtonDown;
    QPushButton *pushButtonUp;
    QPushButton *pushButtonLeft;
    QPushButton *pushButtonRight;

    void setupUi(QWidget *VisualController)
    {
        if (VisualController->objectName().isEmpty())
            VisualController->setObjectName(QStringLiteral("VisualController"));
        VisualController->resize(255, 70);
        gridLayout_2 = new QGridLayout(VisualController);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButtonDown = new QPushButton(VisualController);
        pushButtonDown->setObjectName(QStringLiteral("pushButtonDown"));
        pushButtonDown->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(pushButtonDown, 1, 1, 1, 1);

        pushButtonUp = new QPushButton(VisualController);
        pushButtonUp->setObjectName(QStringLiteral("pushButtonUp"));
        pushButtonUp->setFocusPolicy(Qt::NoFocus);
        pushButtonUp->setFlat(false);

        gridLayout_2->addWidget(pushButtonUp, 0, 1, 1, 1);

        pushButtonLeft = new QPushButton(VisualController);
        pushButtonLeft->setObjectName(QStringLiteral("pushButtonLeft"));
        pushButtonLeft->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(pushButtonLeft, 1, 0, 1, 1);

        pushButtonRight = new QPushButton(VisualController);
        pushButtonRight->setObjectName(QStringLiteral("pushButtonRight"));
        pushButtonRight->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(pushButtonRight, 1, 2, 1, 1);


        retranslateUi(VisualController);

        QMetaObject::connectSlotsByName(VisualController);
    } // setupUi

    void retranslateUi(QWidget *VisualController)
    {
        VisualController->setWindowTitle(QApplication::translate("VisualController", "Form", 0));
        pushButtonDown->setText(QApplication::translate("VisualController", "Down", 0));
        pushButtonUp->setText(QApplication::translate("VisualController", "Up", 0));
        pushButtonLeft->setText(QApplication::translate("VisualController", "Left", 0));
        pushButtonRight->setText(QApplication::translate("VisualController", "Right", 0));
    } // retranslateUi

};

namespace Ui {
    class VisualController: public Ui_VisualController {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VISUALCONTROLLER_H
