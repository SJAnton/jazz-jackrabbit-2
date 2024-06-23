#include "setupwindow.h"
#include "ui_setupwindow.h"
#include <QDesktopWidget>
#include <QApplication>

SetupWindow::SetupWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetupWindow),
    levelEditor(nullptr)
{
    ui->setupUi(this);

    // Centrar la ventana en la pantalla
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);
}

SetupWindow::~SetupWindow()
{
    delete ui;
    if (levelEditor)
        delete levelEditor;
}

void SetupWindow::on_startLevelEditorButton_clicked()
{
    int rows = ui->rowsInput->text().toInt();
    int cols = ui->colsInput->text().toInt();
    levelEditor = new LevelEditor(nullptr, cols, rows);
    levelEditor->show();
    this->close();
}
