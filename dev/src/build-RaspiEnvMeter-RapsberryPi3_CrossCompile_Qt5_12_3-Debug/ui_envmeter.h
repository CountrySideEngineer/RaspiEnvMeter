/********************************************************************************
** Form generated from reading UI file 'envmeter.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENVMETER_H
#define UI_ENVMETER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "craspienvmetertimeview.h"

QT_BEGIN_NAMESPACE

class Ui_EnvMeter
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    CRaspiEnvMeterTimeView *AmPmDisplay;
    QHBoxLayout *horizontalLayout_4;
    CRaspiEnvMeterTimeView *TimeHourDisplay;
    QLabel *TimeCoron;
    CRaspiEnvMeterTimeView *TimeMinuteDisplay;
    CRaspiEnvMeterTimeView *TimeSecondDisplay;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    CRaspiEnvMeterTimeView *DateMonthDisplay;
    QLabel *DateSlash;
    CRaspiEnvMeterTimeView *DateDayDisplay;
    QGridLayout *gridLayout_3;
    QLabel *EnvTempDecPartDisplay;
    QLabel *EnvTempDotDisplay;
    QLabel *EnvTempIntPartDisplay;
    QLabel *EnvTempUnitDisplay;
    QVBoxLayout *verticalLayout_2;
    QLabel *EnvPressUnitDisplay;
    QLabel *EnvPressDisplay;
    QVBoxLayout *verticalLayout_3;
    QLabel *EnvLuxUnitDisplay;
    QLabel *EnvLuxDisplay;

    void setupUi(QMainWindow *EnvMeter)
    {
        if (EnvMeter->objectName().isEmpty())
            EnvMeter->setObjectName(QString::fromUtf8("EnvMeter"));
        EnvMeter->resize(480, 320);
        EnvMeter->setMinimumSize(QSize(480, 320));
        EnvMeter->setMaximumSize(QSize(480, 320));
        centralwidget = new QWidget(EnvMeter);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setMinimumSize(QSize(480, 320));
        centralwidget->setMaximumSize(QSize(480, 320));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(10);
        gridLayout_2->setContentsMargins(10, 10, 10, 10);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(5);
        gridLayout->setContentsMargins(5, 5, 5, 5);
        verticalSpacer = new QSpacerItem(20, 120, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 0, 4, 1, 1);

        AmPmDisplay = new CRaspiEnvMeterTimeView(centralwidget);
        AmPmDisplay->setObjectName(QString::fromUtf8("AmPmDisplay"));
        AmPmDisplay->setMinimumSize(QSize(30, 0));
        AmPmDisplay->setMaximumSize(QSize(30, 16777215));

        gridLayout->addWidget(AmPmDisplay, 0, 0, 2, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        TimeHourDisplay = new CRaspiEnvMeterTimeView(centralwidget);
        TimeHourDisplay->setObjectName(QString::fromUtf8("TimeHourDisplay"));
        sizePolicy.setHeightForWidth(TimeHourDisplay->sizePolicy().hasHeightForWidth());
        TimeHourDisplay->setSizePolicy(sizePolicy);
        TimeHourDisplay->setMinimumSize(QSize(161, 167));
        TimeHourDisplay->setMaximumSize(QSize(161, 167));
        QFont font;
        font.setPointSize(82);
        TimeHourDisplay->setFont(font);
        TimeHourDisplay->setLayoutDirection(Qt::LeftToRight);
        TimeHourDisplay->setAutoFillBackground(false);

        horizontalLayout_4->addWidget(TimeHourDisplay, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        TimeCoron = new QLabel(centralwidget);
        TimeCoron->setObjectName(QString::fromUtf8("TimeCoron"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(TimeCoron->sizePolicy().hasHeightForWidth());
        TimeCoron->setSizePolicy(sizePolicy1);
        TimeCoron->setMinimumSize(QSize(30, 0));
        TimeCoron->setMaximumSize(QSize(30, 16777215));
        QFont font1;
        font1.setPointSize(82);
        font1.setBold(true);
        font1.setWeight(75);
        TimeCoron->setFont(font1);
        TimeCoron->setFrameShape(QFrame::Box);
        TimeCoron->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(TimeCoron);

        TimeMinuteDisplay = new CRaspiEnvMeterTimeView(centralwidget);
        TimeMinuteDisplay->setObjectName(QString::fromUtf8("TimeMinuteDisplay"));
        TimeMinuteDisplay->setMinimumSize(QSize(161, 167));
        TimeMinuteDisplay->setMaximumSize(QSize(161, 16777215));
        TimeMinuteDisplay->setFont(font);

        horizontalLayout_4->addWidget(TimeMinuteDisplay);


        gridLayout->addLayout(horizontalLayout_4, 0, 3, 2, 1);

        TimeSecondDisplay = new CRaspiEnvMeterTimeView(centralwidget);
        TimeSecondDisplay->setObjectName(QString::fromUtf8("TimeSecondDisplay"));
        TimeSecondDisplay->setMinimumSize(QSize(48, 48));
        TimeSecondDisplay->setMaximumSize(QSize(48, 48));
        QFont font2;
        font2.setPointSize(18);
        TimeSecondDisplay->setFont(font2);

        gridLayout->addWidget(TimeSecondDisplay, 1, 4, 1, 1);


        verticalLayout->addLayout(gridLayout);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(5);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalLayout_3->setContentsMargins(5, 5, 5, 5);
        DateMonthDisplay = new CRaspiEnvMeterTimeView(centralwidget);
        DateMonthDisplay->setObjectName(QString::fromUtf8("DateMonthDisplay"));
        DateMonthDisplay->setMinimumSize(QSize(58, 99));
        DateMonthDisplay->setMaximumSize(QSize(58, 99));
        QFont font3;
        font3.setPointSize(32);
        DateMonthDisplay->setFont(font3);

        horizontalLayout_3->addWidget(DateMonthDisplay);

        DateSlash = new QLabel(centralwidget);
        DateSlash->setObjectName(QString::fromUtf8("DateSlash"));
        sizePolicy1.setHeightForWidth(DateSlash->sizePolicy().hasHeightForWidth());
        DateSlash->setSizePolicy(sizePolicy1);
        DateSlash->setMinimumSize(QSize(14, 0));
        DateSlash->setMaximumSize(QSize(24, 16777215));
        QFont font4;
        font4.setPointSize(26);
        DateSlash->setFont(font4);
        DateSlash->setFrameShape(QFrame::Box);
        DateSlash->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(DateSlash);

        DateDayDisplay = new CRaspiEnvMeterTimeView(centralwidget);
        DateDayDisplay->setObjectName(QString::fromUtf8("DateDayDisplay"));
        DateDayDisplay->setMinimumSize(QSize(58, 99));
        DateDayDisplay->setMaximumSize(QSize(58, 99));
        DateDayDisplay->setFont(font3);

        horizontalLayout_3->addWidget(DateDayDisplay);


        horizontalLayout_2->addLayout(horizontalLayout_3);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(5);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(5, 5, 5, 5);
        EnvTempDecPartDisplay = new QLabel(centralwidget);
        EnvTempDecPartDisplay->setObjectName(QString::fromUtf8("EnvTempDecPartDisplay"));
        sizePolicy.setHeightForWidth(EnvTempDecPartDisplay->sizePolicy().hasHeightForWidth());
        EnvTempDecPartDisplay->setSizePolicy(sizePolicy);
        EnvTempDecPartDisplay->setMinimumSize(QSize(61, 0));
        EnvTempDecPartDisplay->setFont(font3);
        EnvTempDecPartDisplay->setFrameShape(QFrame::Box);
        EnvTempDecPartDisplay->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(EnvTempDecPartDisplay, 1, 0, 3, 1);

        EnvTempDotDisplay = new QLabel(centralwidget);
        EnvTempDotDisplay->setObjectName(QString::fromUtf8("EnvTempDotDisplay"));
        sizePolicy1.setHeightForWidth(EnvTempDotDisplay->sizePolicy().hasHeightForWidth());
        EnvTempDotDisplay->setSizePolicy(sizePolicy1);
        EnvTempDotDisplay->setMinimumSize(QSize(20, 0));
        EnvTempDotDisplay->setMaximumSize(QSize(20, 16777215));
        QFont font5;
        font5.setPointSize(24);
        EnvTempDotDisplay->setFont(font5);
        EnvTempDotDisplay->setFrameShape(QFrame::Box);
        EnvTempDotDisplay->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        gridLayout_3->addWidget(EnvTempDotDisplay, 2, 1, 2, 1);

        EnvTempIntPartDisplay = new QLabel(centralwidget);
        EnvTempIntPartDisplay->setObjectName(QString::fromUtf8("EnvTempIntPartDisplay"));
        sizePolicy.setHeightForWidth(EnvTempIntPartDisplay->sizePolicy().hasHeightForWidth());
        EnvTempIntPartDisplay->setSizePolicy(sizePolicy);
        EnvTempIntPartDisplay->setFont(font5);
        EnvTempIntPartDisplay->setFrameShape(QFrame::Box);

        gridLayout_3->addWidget(EnvTempIntPartDisplay, 2, 2, 2, 3);

        EnvTempUnitDisplay = new QLabel(centralwidget);
        EnvTempUnitDisplay->setObjectName(QString::fromUtf8("EnvTempUnitDisplay"));
        sizePolicy.setHeightForWidth(EnvTempUnitDisplay->sizePolicy().hasHeightForWidth());
        EnvTempUnitDisplay->setSizePolicy(sizePolicy);
        EnvTempUnitDisplay->setMinimumSize(QSize(76, 0));
        EnvTempUnitDisplay->setFont(font2);
        EnvTempUnitDisplay->setFrameShape(QFrame::Box);
        EnvTempUnitDisplay->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(EnvTempUnitDisplay, 1, 1, 1, 4);


        horizontalLayout_2->addLayout(gridLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(5);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(5, 5, 5, 5);
        EnvPressUnitDisplay = new QLabel(centralwidget);
        EnvPressUnitDisplay->setObjectName(QString::fromUtf8("EnvPressUnitDisplay"));
        EnvPressUnitDisplay->setMinimumSize(QSize(0, 31));
        EnvPressUnitDisplay->setMaximumSize(QSize(16777215, 31));
        EnvPressUnitDisplay->setFont(font2);
        EnvPressUnitDisplay->setFrameShape(QFrame::Box);
        EnvPressUnitDisplay->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(EnvPressUnitDisplay);

        EnvPressDisplay = new QLabel(centralwidget);
        EnvPressDisplay->setObjectName(QString::fromUtf8("EnvPressDisplay"));
        sizePolicy.setHeightForWidth(EnvPressDisplay->sizePolicy().hasHeightForWidth());
        EnvPressDisplay->setSizePolicy(sizePolicy);
        EnvPressDisplay->setMinimumSize(QSize(91, 63));
        EnvPressDisplay->setMaximumSize(QSize(91, 63));
        EnvPressDisplay->setFont(font5);
        EnvPressDisplay->setFrameShape(QFrame::Box);
        EnvPressDisplay->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(EnvPressDisplay);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(5);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(5, 5, 5, 5);
        EnvLuxUnitDisplay = new QLabel(centralwidget);
        EnvLuxUnitDisplay->setObjectName(QString::fromUtf8("EnvLuxUnitDisplay"));
        sizePolicy.setHeightForWidth(EnvLuxUnitDisplay->sizePolicy().hasHeightForWidth());
        EnvLuxUnitDisplay->setSizePolicy(sizePolicy);
        EnvLuxUnitDisplay->setMinimumSize(QSize(26, 31));
        EnvLuxUnitDisplay->setMaximumSize(QSize(16777215, 31));
        EnvLuxUnitDisplay->setFrameShape(QFrame::Box);
        EnvLuxUnitDisplay->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(EnvLuxUnitDisplay);

        EnvLuxDisplay = new QLabel(centralwidget);
        EnvLuxDisplay->setObjectName(QString::fromUtf8("EnvLuxDisplay"));
        sizePolicy.setHeightForWidth(EnvLuxDisplay->sizePolicy().hasHeightForWidth());
        EnvLuxDisplay->setSizePolicy(sizePolicy);
        EnvLuxDisplay->setMinimumSize(QSize(50, 0));
        EnvLuxDisplay->setFont(font5);
        EnvLuxDisplay->setFrameShape(QFrame::Box);
        EnvLuxDisplay->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(EnvLuxDisplay);


        horizontalLayout_2->addLayout(verticalLayout_3);


        horizontalLayout->addLayout(horizontalLayout_2);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);

        EnvMeter->setCentralWidget(centralwidget);

        retranslateUi(EnvMeter);

        QMetaObject::connectSlotsByName(EnvMeter);
    } // setupUi

    void retranslateUi(QMainWindow *EnvMeter)
    {
        EnvMeter->setWindowTitle(QApplication::translate("EnvMeter", "EnvMeter", nullptr));
        TimeCoron->setText(QApplication::translate("EnvMeter", ":", nullptr));
        DateSlash->setText(QApplication::translate("EnvMeter", "/", nullptr));
        EnvTempDecPartDisplay->setText(QApplication::translate("EnvMeter", "12", nullptr));
        EnvTempDotDisplay->setText(QApplication::translate("EnvMeter", ".", nullptr));
        EnvTempIntPartDisplay->setText(QApplication::translate("EnvMeter", "34", nullptr));
        EnvTempUnitDisplay->setText(QApplication::translate("EnvMeter", "\342\204\203", nullptr));
        EnvPressUnitDisplay->setText(QApplication::translate("EnvMeter", "hPa", nullptr));
        EnvPressDisplay->setText(QApplication::translate("EnvMeter", "1234", nullptr));
        EnvLuxUnitDisplay->setText(QApplication::translate("EnvMeter", "Lux", nullptr));
        EnvLuxDisplay->setText(QApplication::translate("EnvMeter", "1234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EnvMeter: public Ui_EnvMeter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENVMETER_H
