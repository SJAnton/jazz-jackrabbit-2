#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , setupWindow(new SetupWindow)
{
    ui->setupUi(this);

    // Centrar la ventana en la pantalla
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete setupWindow;
}

void MainWindow::on_createScenarioButton_clicked()
{
    setupWindow->show();
    this->close();
}

