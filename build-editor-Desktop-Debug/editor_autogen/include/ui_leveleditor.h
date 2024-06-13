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
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "customgraphicsview.h"

QT_BEGIN_NAMESPACE

class Ui_LevelEditor
{
public:
    QWidget *centralwidget;
    CustomGraphicsView *graphicsView;
    QListWidget *modeList;
    QTabWidget *tabWidget;
    QWidget *Terrain;
    QListWidget *terrainListWidget;
    QWidget *Objects;
    QListWidget *objectsListWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *LevelEditor)
    {
        if (LevelEditor->objectName().isEmpty())
            LevelEditor->setObjectName(QString::fromUtf8("LevelEditor"));
        LevelEditor->resize(1080, 720);
        centralwidget = new QWidget(LevelEditor);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        graphicsView = new CustomGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(20, 10, 931, 571));
        modeList = new QListWidget(centralwidget);
        modeList->setObjectName(QString::fromUtf8("modeList"));
        modeList->setGeometry(QRect(960, 10, 91, 571));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(20, 580, 1031, 91));
        Terrain = new QWidget();
        Terrain->setObjectName(QString::fromUtf8("Terrain"));
        terrainListWidget = new QListWidget(Terrain);
        terrainListWidget->setObjectName(QString::fromUtf8("terrainListWidget"));
        terrainListWidget->setGeometry(QRect(0, 0, 1031, 61));
        terrainListWidget->setFlow(QListView::LeftToRight);
        tabWidget->addTab(Terrain, QString());
        Objects = new QWidget();
        Objects->setObjectName(QString::fromUtf8("Objects"));
        objectsListWidget = new QListWidget(Objects);
        objectsListWidget->setObjectName(QString::fromUtf8("objectsListWidget"));
        objectsListWidget->setGeometry(QRect(0, 0, 1031, 61));
        objectsListWidget->setFlow(QListView::LeftToRight);
        tabWidget->addTab(Objects, QString());
        LevelEditor->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LevelEditor);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1080, 21));
        LevelEditor->setMenuBar(menubar);
        statusbar = new QStatusBar(LevelEditor);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        LevelEditor->setStatusBar(statusbar);

        retranslateUi(LevelEditor);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LevelEditor);
    } // setupUi

    void retranslateUi(QMainWindow *LevelEditor)
    {
        LevelEditor->setWindowTitle(QApplication::translate("LevelEditor", "LevelEditor", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Terrain), QApplication::translate("LevelEditor", "Terrain", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Objects), QApplication::translate("LevelEditor", "Objects", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LevelEditor: public Ui_LevelEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEVELEDITOR_H
