/********************************************************************************
** Form generated from reading UI file 'Lab1_GUI.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAB1_GUI_H
#define UI_LAB1_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lab1_GUIClass
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *lambda;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QLineEdit *mu;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *start;
    QVBoxLayout *visualization_layout;
    QSlider *time;

    void setupUi(QWidget *Lab1_GUIClass)
    {
        if (Lab1_GUIClass->objectName().isEmpty())
            Lab1_GUIClass->setObjectName(QStringLiteral("Lab1_GUIClass"));
        Lab1_GUIClass->resize(600, 400);
        verticalLayout_2 = new QVBoxLayout(Lab1_GUIClass);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(Lab1_GUIClass);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        lambda = new QLineEdit(Lab1_GUIClass);
        lambda->setObjectName(QStringLiteral("lambda"));

        horizontalLayout_3->addWidget(lambda);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        label_2 = new QLabel(Lab1_GUIClass);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        mu = new QLineEdit(Lab1_GUIClass);
        mu->setObjectName(QStringLiteral("mu"));

        horizontalLayout_3->addWidget(mu);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        start = new QPushButton(Lab1_GUIClass);
        start->setObjectName(QStringLiteral("start"));

        horizontalLayout_3->addWidget(start);

        horizontalLayout_3->setStretch(1, 5);
        horizontalLayout_3->setStretch(2, 1);
        horizontalLayout_3->setStretch(4, 5);
        horizontalLayout_3->setStretch(5, 1);
        horizontalLayout_3->setStretch(6, 3);

        verticalLayout_2->addLayout(horizontalLayout_3);

        visualization_layout = new QVBoxLayout();
        visualization_layout->setSpacing(6);
        visualization_layout->setObjectName(QStringLiteral("visualization_layout"));

        verticalLayout_2->addLayout(visualization_layout);

        time = new QSlider(Lab1_GUIClass);
        time->setObjectName(QStringLiteral("time"));
        time->setMinimum(1);
        time->setMaximum(100);
        time->setValue(50);
        time->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(time);

        verticalLayout_2->setStretch(1, 1);

        retranslateUi(Lab1_GUIClass);

        QMetaObject::connectSlotsByName(Lab1_GUIClass);
    } // setupUi

    void retranslateUi(QWidget *Lab1_GUIClass)
    {
        Lab1_GUIClass->setWindowTitle(QApplication::translate("Lab1_GUIClass", "GUI", Q_NULLPTR));
        label->setText(QApplication::translate("Lab1_GUIClass", "lambda = ", Q_NULLPTR));
        label_2->setText(QApplication::translate("Lab1_GUIClass", "mu = ", Q_NULLPTR));
        start->setText(QApplication::translate("Lab1_GUIClass", "Start", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Lab1_GUIClass: public Ui_Lab1_GUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAB1_GUI_H
