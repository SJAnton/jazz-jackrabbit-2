/********************************************************************************
** Form generated from reading UI file 'leveleditor.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEVELEDITOR_H
#define UI_LEVELEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "customgraphicsview.h"

QT_BEGIN_NAMESPACE

class Ui_LevelEditor
{
public:
    QWidget *centralwidget;
    QListWidget *objectPalette;
    CustomGraphicsView *graphicsView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *LevelEditor)
    {
        if (LevelEditor->objectName().isEmpty())
            LevelEditor->setObjectName(QString::fromUtf8("LevelEditor"));
        LevelEditor->resize(800, 600);
        centralwidget = new QWidget(LevelEditor);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        objectPalette = new QListWidget(centralwidget);
        objectPalette->setObjectName(QString::fromUtf8("objectPalette"));
        objectPalette->setGeometry(QRect(20, 370, 751, 61));
        objectPalette->setFlow(QListView::LeftToRight);
        graphicsView = new CustomGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(20, 10, 750, 351));
        LevelEditor->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LevelEditor);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        LevelEditor->setMenuBar(menubar);
        statusbar = new QStatusBar(LevelEditor);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        LevelEditor->setStatusBar(statusbar);

        retranslateUi(LevelEditor);

        QMetaObject::connectSlotsByName(LevelEditor);
    } // setupUi

    void retranslateUi(QMainWindow *LevelEditor)
    {
        LevelEditor->setWindowTitle(QApplication::translate("LevelEditor", "LevelEditor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LevelEditor: public Ui_LevelEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEVELEDITOR_H
