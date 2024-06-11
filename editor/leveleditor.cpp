#include "leveleditor.h"
#include "ui_leveleditor.h"
#include <QIcon>
#include <QDataStream>

LevelEditor::LevelEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LevelEditor),
    map(new Map(32, 32))  // Inicializa el mapa con el tamaño deseado
{
    ui->setupUi(this);

    // Inicializar la escena
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    // Añadir ejemplos de objetos a la paleta
    QListWidgetItem *floorItem = new QListWidgetItem(QIcon(":/sprites/tile000.png"), "Floor");
    ui->objectPalette->addItem(floorItem);

    QListWidgetItem *wallItem = new QListWidgetItem(QIcon(":/sprites/tile003.png"), "Wall");
    ui->objectPalette->addItem(wallItem);

    // Habilitar la selección en la lista
    ui->objectPalette->setSelectionMode(QAbstractItemView::SingleSelection);

    // Conectar la señal de clic al slot
    connect(ui->graphicsView, &CustomGraphicsView::clicked, this, &LevelEditor::onGraphicsViewClicked);
}

LevelEditor::~LevelEditor() {
    delete ui;
    delete map;  // Eliminar el puntero del mapa
}

void LevelEditor::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist")) {
        event->acceptProposedAction();
    }
}

void LevelEditor::dropEvent(QDropEvent *event) {
    const QMimeData *mimeData = event->mimeData();
    QByteArray encodedData = mimeData->data("application/x-qabstractitemmodeldatalist");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);

    while (!stream.atEnd()) {
        int row, col;
        QMap<int, QVariant> roleDataMap;
        stream >> row >> col >> roleDataMap;
        QIcon icon = qvariant_cast<QIcon>(roleDataMap[Qt::DecorationRole]);
        QPointF pos = ui->graphicsView->mapToScene(event->pos());
        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(icon.pixmap(64, 64));
        item->setPos(pos);
        scene->addItem(item);
    }

    event->acceptProposedAction();
}

void LevelEditor::onGraphicsViewClicked(QMouseEvent *event) {
    QListWidgetItem *selectedItem = ui->objectPalette->currentItem();
    if (selectedItem) {
        QIcon icon = selectedItem->icon();
        QPointF scenePos = ui->graphicsView->mapToScene(event->pos());

        // Calcular la posición de la matriz
        int gridSize = 32;  // Tamaño del sprite
        int x = static_cast<int>(scenePos.x()) / gridSize;
        int y = static_cast<int>(scenePos.y()) / gridSize;

        // Verificar si las coordenadas están dentro del rango
        if (map->isValidCoordinate(x, y)) {
            // Comprobar si la posición está ocupada
            if (!map->isOccupied(x, y)) {
                // Colocar el sprite en la posición calculada
                QGraphicsPixmapItem *item = new QGraphicsPixmapItem(icon.pixmap(gridSize, gridSize));
                item->setPos(x * gridSize, y * gridSize);
                scene->addItem(item);

                // Marcar la posición como ocupada
                map->setOccupied(x, y, true);
            }
        }
    }
}

