#include "leveleditor.h"
#include "ui_leveleditor.h"
#include <QIcon>
#include <QDataStream>
#include <QResizeEvent>

LevelEditor::LevelEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LevelEditor),
    map(new Map(30, 20)),  // Inicializa el mapa con el tamaño deseado
    isMousePressed(false)
{
    ui->setupUi(this);

    // Calcular el tamaño de la escena
    int gridSize = 32;
    int sceneWidth = 30 * gridSize;
    int sceneHeight = 20 * gridSize;

    // Inicializar la escena
    //scene = new QGraphicsScene(this);
    //scene = new QGraphicsScene(0, 0, ui->graphicsView->width(), ui->graphicsView->height(), this);
    scene = new QGraphicsScene(0, 0, sceneWidth, sceneHeight, this);
    ui->graphicsView->setScene(scene);

    // Añadir ejemplos de objetos a la paleta
    QListWidgetItem *floorItem = new QListWidgetItem(QIcon(":/sprites/tile013.png"), "Floor");
    ui->terrainListWidget->addItem(floorItem);

    QListWidgetItem *floorLeftCornerItem = new QListWidgetItem(QIcon(":/sprites/tile000.png"), "Floor Left Corner");
    ui->terrainListWidget->addItem(floorLeftCornerItem);

    QListWidgetItem *floorRightCornerItem = new QListWidgetItem(QIcon(":/sprites/tile001.png"), "Floor Right Corner");
    ui->terrainListWidget->addItem(floorRightCornerItem);

    QListWidgetItem *undergroundItem1 = new QListWidgetItem(QIcon(":/sprites/tile008.png"), "Underground 1");
    ui->terrainListWidget->addItem(undergroundItem1);

    QListWidgetItem *undergroundItem2 = new QListWidgetItem(QIcon(":/sprites/tile009.png"), "Underground 2");
    ui->terrainListWidget->addItem(undergroundItem2);

    QListWidgetItem *wallItem = new QListWidgetItem(QIcon(":/sprites/tile003.png"), "Background");
    ui->terrainListWidget->addItem(wallItem);

    // Añadir ejemplos de objetos a la paleta en la pestaña 'Objects'
    QListWidgetItem *goldCoinItem = new QListWidgetItem(QIcon(":/sprites/gold_coin.png"), "Gold Coin");
    ui->objectsListWidget->addItem(goldCoinItem);

    QListWidgetItem *silverCoinItem = new QListWidgetItem(QIcon(":/sprites/silver_coin.png"), "Silver Coin");
    ui->objectsListWidget->addItem(silverCoinItem);

    QListWidgetItem *redGemItem = new QListWidgetItem(QIcon(":/sprites/red_gem.png"), "Red Gem");
    ui->objectsListWidget->addItem(redGemItem);

    // Habilitar la selección en la lista
    ui->terrainListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->objectsListWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    // Conectar la señal de clic al slot
    connect(ui->graphicsView, &CustomGraphicsView::mousePressed, this, &LevelEditor::onGraphicsViewClicked);
    connect(ui->graphicsView, &CustomGraphicsView::mouseMoved, this, &LevelEditor::onGraphicsViewMouseMoved);
    connect(ui->graphicsView, &CustomGraphicsView::mouseReleased, this, &LevelEditor::onGraphicsViewMouseReleased);

    // Añadir modos a la lista de modos
    QListWidgetItem *putMode = new QListWidgetItem(QIcon(":/sprites/put.png"), "Put");
    ui->modeList->addItem(putMode);

    QListWidgetItem *eraseMode = new QListWidgetItem(QIcon(":/sprites/erase.png"), "Erase");
    ui->modeList->addItem(eraseMode);

    // Conectar la señal de cambio de selección al slot correspondiente
    connect(ui->modeList, &QListWidget::currentItemChanged, this, &LevelEditor::onModeChanged);

    // Establecer el delegado personalizado para cambiar el tamaño de los ítems
    CustomDelegate *delegate = new CustomDelegate(this);
    ui->modeList->setItemDelegate(delegate);

    // Seleccionar el modo por defecto "Put"
    ui->modeList->setCurrentItem(putMode);
    currentMode = "Put";
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

void LevelEditor::onModeChanged(QListWidgetItem *current, QListWidgetItem *previous) {
    if (current) {
        currentMode = current->text();
    }
}

void LevelEditor::onGraphicsViewClicked(QMouseEvent *event) {
    isMousePressed = true;
    QPointF scenePos = ui->graphicsView->mapToScene(event->pos());
    if (currentMode == "Put") {
        placeSpriteAtPosition(scenePos);
    } else if (currentMode == "Erase") {
        eraseSpriteAtPosition(scenePos);
    }
}

void LevelEditor::onGraphicsViewMouseMoved(QMouseEvent *event) {
    if (isMousePressed) {
        QPointF scenePos = ui->graphicsView->mapToScene(event->pos());
        if (currentMode == "Put") {
            placeSpriteAtPosition(scenePos);
        } else if (currentMode == "Erase") {
            eraseSpriteAtPosition(scenePos);
        }
    }
}

void LevelEditor::onGraphicsViewMouseReleased(QMouseEvent *event) {
    isMousePressed = false;
}

void LevelEditor::placeSpriteAtPosition(const QPointF &scenePos) {
    QListWidgetItem *selectedItem = nullptr;
    bool isObject = false;

    if (ui->tabWidget->currentIndex() == 0) {  // 'Terrain' tab
        selectedItem = ui->terrainListWidget->currentItem();
    } else if (ui->tabWidget->currentIndex() == 1) {  // 'Objects' tab
        selectedItem = ui->objectsListWidget->currentItem();
        isObject = true;
    }

    if (selectedItem) {
        QIcon icon = selectedItem->icon();

        // Calcular la posición de la matriz
        int gridSize = 32;  // Tamaño del sprite
        int x = static_cast<int>(scenePos.x()) / gridSize;
        int y = static_cast<int>(scenePos.y()) / gridSize;

        // Verificar si las coordenadas están dentro del rango
        if (map->isValidCoordinate(x, y)) {
            if (isObject) {
                // Comprobar si la posición no está ocupada por otro objeto
                if (!map->isObjectOccupied(x, y)) {
                    // Colocar el objeto en la posición calculada
                    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(icon.pixmap(gridSize, gridSize));
                    item->setPos(x * gridSize, y * gridSize);
                    item->setZValue(1);  // Asegurar que los objetos estén al frente
                    scene->addItem(item);

                    // Marcar la posición como ocupada
                    map->setObjectOccupied(x, y, true);
                }
            } else {
                // Comprobar si la posición no está ocupada por el terreno
                if (!map->isOccupied(x, y)) {
                    // Colocar el terreno en la posición calculada
                    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(icon.pixmap(gridSize, gridSize));
                    item->setPos(x * gridSize, y * gridSize);
                    item->setZValue(0);  // Asegurar que el terreno esté detrás de los objetos
                    scene->addItem(item);

                    // Marcar la posición como ocupada
                    map->setOccupied(x, y, true);
                }
            }
        }
    }
}

void LevelEditor::eraseSpriteAtPosition(const QPointF &scenePos) {
    // Calcular la posición de la matriz
    int gridSize = 32;  // Tamaño del sprite
    int x = static_cast<int>(scenePos.x()) / gridSize;
    int y = static_cast<int>(scenePos.y()) / gridSize;

    // Verificar si las coordenadas están dentro del rango
    if (map->isValidCoordinate(x, y)) {
        // Buscar y borrar el objeto si existe
        if (map->isObjectOccupied(x, y)) {
            QList<QGraphicsItem *> items = scene->items(QRectF(x * gridSize, y * gridSize, gridSize, gridSize));
            for (QGraphicsItem *item : items) {
                if (item->zValue() == 1) {  // Verificar si es un objeto
                    if (QGraphicsPixmapItem *pixmapItem = dynamic_cast<QGraphicsPixmapItem *>(item)) {
                        scene->removeItem(pixmapItem);
                        delete pixmapItem;
                        map->setObjectOccupied(x, y, false);
                        break;
                    }
                }
            }
        }

        // Buscar y borrar el terreno si existe
        if (map->isOccupied(x, y)) {
            QList<QGraphicsItem *> items = scene->items(QRectF(x * gridSize, y * gridSize, gridSize, gridSize));
            for (QGraphicsItem *item : items) {
                if (item->zValue() == 0) {  // Verificar si es terreno
                    if (QGraphicsPixmapItem *pixmapItem = dynamic_cast<QGraphicsPixmapItem *>(item)) {
                        scene->removeItem(pixmapItem);
                        delete pixmapItem;
                        map->setOccupied(x, y, false);
                        break;
                    }
                }
            }
        }
    }
}
