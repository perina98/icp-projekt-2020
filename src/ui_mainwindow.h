/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *timeLabel;
    QDoubleSpinBox *timeTravelBox;
    QPushButton *resetTimer;
    QLabel *closedLabel;
    QComboBox *comboBox;
    QPushButton *cancelRoad;
    QGraphicsView *graphicsView;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QGraphicsView *graphicsView_2;
    QSlider *ZoomSlider;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1500, 700);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        timeLabel = new QLabel(centralwidget);
        timeLabel->setObjectName(QStringLiteral("timeLabel"));
        QFont font;
        font.setFamily(QStringLiteral("Roboto"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        timeLabel->setFont(font);
        timeLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(timeLabel);

        timeTravelBox = new QDoubleSpinBox(centralwidget);
        timeTravelBox->setObjectName(QStringLiteral("timeTravelBox"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(timeTravelBox->sizePolicy().hasHeightForWidth());
        timeTravelBox->setSizePolicy(sizePolicy);
        timeTravelBox->setMinimum(0.1);
        timeTravelBox->setMaximum(999.99);
        timeTravelBox->setSingleStep(0.1);
        timeTravelBox->setValue(1);

        horizontalLayout_2->addWidget(timeTravelBox);

        resetTimer = new QPushButton(centralwidget);
        resetTimer->setObjectName(QStringLiteral("resetTimer"));
        sizePolicy.setHeightForWidth(resetTimer->sizePolicy().hasHeightForWidth());
        resetTimer->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamily(QStringLiteral("Roboto"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        resetTimer->setFont(font1);

        horizontalLayout_2->addWidget(resetTimer);

        closedLabel = new QLabel(centralwidget);
        closedLabel->setObjectName(QStringLiteral("closedLabel"));
        closedLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(closedLabel);

        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setEnabled(false);

        horizontalLayout_2->addWidget(comboBox);

        cancelRoad = new QPushButton(centralwidget);
        cancelRoad->setObjectName(QStringLiteral("cancelRoad"));
        cancelRoad->setEnabled(false);
        sizePolicy.setHeightForWidth(cancelRoad->sizePolicy().hasHeightForWidth());
        cancelRoad->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(cancelRoad);


        verticalLayout->addLayout(horizontalLayout_2);

        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        verticalLayout->addWidget(graphicsView);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        graphicsView_2 = new QGraphicsView(centralwidget);
        graphicsView_2->setObjectName(QStringLiteral("graphicsView_2"));
        graphicsView_2->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(graphicsView_2->sizePolicy().hasHeightForWidth());
        graphicsView_2->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(graphicsView_2);


        verticalLayout_2->addLayout(horizontalLayout_4);


        verticalLayout->addLayout(verticalLayout_2);


        horizontalLayout->addLayout(verticalLayout);

        ZoomSlider = new QSlider(centralwidget);
        ZoomSlider->setObjectName(QStringLiteral("ZoomSlider"));
        ZoomSlider->setMaximum(100);
        ZoomSlider->setValue(10);
        ZoomSlider->setSliderPosition(10);
        ZoomSlider->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(ZoomSlider);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1500, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::RightToolBarArea, toolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        timeLabel->setText(QString());
#ifndef QT_NO_TOOLTIP
        timeTravelBox->setToolTip(QApplication::translate("MainWindow", "Time multiplier", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        resetTimer->setToolTip(QApplication::translate("MainWindow", "Reset time to default", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        resetTimer->setText(QApplication::translate("MainWindow", "Reset", Q_NULLPTR));
        closedLabel->setText(QApplication::translate("MainWindow", "Closed", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        comboBox->setToolTip(QApplication::translate("MainWindow", "Set street limitations", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        cancelRoad->setToolTip(QApplication::translate("MainWindow", "Close current road", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        cancelRoad->setText(QApplication::translate("MainWindow", "Close Road", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
