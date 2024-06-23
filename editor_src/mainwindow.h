#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include "leveleditor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_createScenarioButton_clicked();
    void on_startLevelEditorButton_clicked();

private:
    Ui::MainWindow *ui;
    LevelEditor *levelEditor;
    QPushButton *createScenarioButton;
    QWidget *inputWidget;
    QLineEdit *rowsInput;
    QLineEdit *colsInput;
};

#endif // MAINWINDOW_H

