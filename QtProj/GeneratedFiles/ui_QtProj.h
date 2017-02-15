/********************************************************************************
** Form generated from reading UI file 'QtProj.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTPROJ_H
#define UI_QTPROJ_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtProjClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtProjClass)
    {
        if (QtProjClass->objectName().isEmpty())
            QtProjClass->setObjectName(QStringLiteral("QtProjClass"));
        QtProjClass->resize(600, 400);
        menuBar = new QMenuBar(QtProjClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        QtProjClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtProjClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtProjClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QtProjClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QtProjClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtProjClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtProjClass->setStatusBar(statusBar);

        retranslateUi(QtProjClass);

        QMetaObject::connectSlotsByName(QtProjClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtProjClass)
    {
        QtProjClass->setWindowTitle(QApplication::translate("QtProjClass", "QtProj", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtProjClass: public Ui_QtProjClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTPROJ_H
