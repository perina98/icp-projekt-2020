/********************************************************************************
** Form generated from reading UI file 'errorwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ERRORWINDOW_H
#define UI_ERRORWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ErrorWindow
{
public:
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView_3;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ErrorWindow)
    {
        if (ErrorWindow->objectName().isEmpty())
            ErrorWindow->setObjectName(QStringLiteral("ErrorWindow"));
        ErrorWindow->resize(562, 94);
        verticalLayout = new QVBoxLayout(ErrorWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        graphicsView_3 = new QGraphicsView(ErrorWindow);
        graphicsView_3->setObjectName(QStringLiteral("graphicsView_3"));

        verticalLayout->addWidget(graphicsView_3);

        buttonBox = new QDialogButtonBox(ErrorWindow);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ErrorWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), ErrorWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ErrorWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(ErrorWindow);
    } // setupUi

    void retranslateUi(QDialog *ErrorWindow)
    {
        ErrorWindow->setWindowTitle(QApplication::translate("ErrorWindow", "Error", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ErrorWindow: public Ui_ErrorWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ERRORWINDOW_H
