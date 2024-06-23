#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QApplication>
#include <QDesktopWidget>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , levelEditor(nullptr)
{
    ui->setupUi(this);

    // Crear el botón "Crear escenario"
    createScenarioButton = new QPushButton("Crear escenario", this);
    connect(createScenarioButton, &QPushButton::clicked, this, &MainWindow::on_createScenarioButton_clicked);

    // Crear el widget de entrada de filas y columnas (inicialmente oculto)
    inputWidget = new QWidget(this);
    QVBoxLayout *inputLayout = new QVBoxLayout(inputWidget);

    QLabel *instructionLabel = new QLabel("Ingrese filas y columnas:", inputWidget);
    rowsInput = new QLineEdit(inputWidget);
    rowsInput->setPlaceholderText("Filas");
    colsInput = new QLineEdit(inputWidget);
    colsInput->setPlaceholderText("Columnas");

    QPushButton *startLevelEditorButton = new QPushButton("Iniciar Editor de Niveles", inputWidget);
    connect(startLevelEditorButton, &QPushButton::clicked, this, &MainWindow::on_startLevelEditorButton_clicked);

    inputLayout->addWidget(instructionLabel);
    inputLayout->addWidget(rowsInput);
    inputLayout->addWidget(colsInput);
    inputLayout->addWidget(startLevelEditorButton);

    inputWidget->setLayout(inputLayout);
    inputWidget->setVisible(false); // Inicialmente oculto

    // Layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(createScenarioButton);
    mainLayout->addWidget(inputWidget);
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Centrar la ventana en la pantalla
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_createScenarioButton_clicked()
{
    createScenarioButton->setVisible(false);
    inputWidget->setVisible(true);
}

void MainWindow::on_startLevelEditorButton_clicked()
{
    bool ok;
    int rows = rowsInput->text().toInt(&ok);
    if (!ok) {
        qDebug() << "Error: Número de filas no válido";
        return;
    }

    int cols = colsInput->text().toInt(&ok);
    if (!ok) {
        qDebug() << "Error: Número de columnas no válido";
        return;
    }

    qDebug() << "Iniciando Level Editor con" << rows << "filas y" << cols << "columnas";

    if (!levelEditor) {
        levelEditor = new LevelEditor(nullptr, cols, rows);
    }
    levelEditor->show();
    this->hide();
}
