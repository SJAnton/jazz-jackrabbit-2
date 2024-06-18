#include "leveleditor.h"
#include "ui_leveleditor.h"
#include <QIcon>
#include <QDataStream>
#include <QResizeEvent>
#include "spriteitem.h"

// Función para agregar SpriteItem a una QListWidget
void addSpriteItemToListWidget(QListWidget *listWidget, const QString &path, const QString &name, const QSize &size) {
    QIcon icon(path);
    SpriteItem *item = new SpriteItem(icon, size);
    item->setText(name);
    listWidget->addItem(item);
}


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

    addSpriteItemToListWidget(ui->terrainListWidget, ":/sprites/tile013.png", "Floor", QSize(32, 32));
    addSpriteItemToListWidget(ui->terrainListWidget, ":/sprites/tile000.png", "Floor Left Corner", QSize(32, 32));
    addSpriteItemToListWidget(ui->terrainListWidget, ":/sprites/tile001.png", "Floor Right Corner", QSize(32, 32));
    addSpriteItemToListWidget(ui->terrainListWidget, ":/sprites/tile008.png", "Underground 1", QSize(32, 32));
    addSpriteItemToListWidget(ui->terrainListWidget, ":/sprites/tile009.png", "Underground 2", QSize(32, 32));
    addSpriteItemToListWidget(ui->terrainListWidget, ":/sprites/tile003.png", "Background", QSize(32, 32));

    addSpriteItemToListWidget(ui->objectsListWidget, ":/sprites/gold_coin.png", "Gold Coin", QSize(32, 32));
    addSpriteItemToListWidget(ui->objectsListWidget, ":/sprites/silver_coin.png", "Silver Coin", QSize(32, 32));
    addSpriteItemToListWidget(ui->objectsListWidget, ":/sprites/red_gem.png", "Red Gem", QSize(32, 32));

    addSpriteItemToListWidget(ui->playerEnemiesListWidget, ":/sprites/spaz.png", "Spaz", QSize(48, 40));
    addSpriteItemToListWidget(ui->playerEnemiesListWidget, ":/sprites/rat.png", "Rat", QSize(72, 32));
    addSpriteItemToListWidget(ui->playerEnemiesListWidget, ":/sprites/bat.png", "Bat", QSize(32, 32));
    addSpriteItemToListWidget(ui->playerEnemiesListWidget, ":/sprites/diablo.png", "Diablo", QSize(64, 96));

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
    SpriteItem *selectedItem = nullptr;
    bool isObject = false;

    if (ui->tabWidget->currentIndex() == 0) {  // 'Terrain' tab
        selectedItem = dynamic_cast<SpriteItem *>(ui->terrainListWidget->currentItem());
    } else if (ui->tabWidget->currentIndex() == 1) {  // 'Objects' tab
        selectedItem = dynamic_cast<SpriteItem *>(ui->objectsListWidget->currentItem());
        isObject = true;
    } else if (ui->tabWidget->currentIndex() == 2) {  // 'PlayerEnemies' tab
        selectedItem = dynamic_cast<SpriteItem *>(ui->playerEnemiesListWidget->currentItem());
        isObject = true;  // Consideramos los enemigos como objetos para la colocación
    }

    if (selectedItem) {
        QIcon icon = selectedItem->icon();
        QSize spriteSize = selectedItem->getSize();
        int gridSize = 32;  // Tamaño del tile
        int spriteWidth = spriteSize.width();
        int spriteHeight = spriteSize.height();

        int x = static_cast<int>(scenePos.x()) / gridSize;
        int y = static_cast<int>(scenePos.y()) / gridSize;

        int widthInTiles, heightInTiles;

        // Si el tamaño del sprite es igual al tamaño de la grilla
        if (spriteWidth == gridSize && spriteHeight == gridSize) {
            widthInTiles = 1;
            heightInTiles = 1;
        } else {
            // Para sprites más grandes que la grilla
            widthInTiles = (spriteWidth + gridSize - 1) / gridSize;  // Redondear hacia arriba
            heightInTiles = (spriteHeight + gridSize - 1) / gridSize;  // Redondear hacia arriba
        }

        if (map->isValidCoordinate(x, y) && map->canPlaceSprite(x, y, widthInTiles, heightInTiles, isObject)) {
            QGraphicsPixmapItem *item = new QGraphicsPixmapItem(icon.pixmap(spriteWidth, spriteHeight));
            item->setPos(x * gridSize, y * gridSize);
            item->setZValue(isObject ? 1 : 0);
            scene->addItem(item);

            map->setSpriteOccupied(x, y, widthInTiles, heightInTiles, true, isObject);
        }
    }
}


/*
void LevelEditor::eraseSpriteAtPosition(const QPointF &scenePos) {
    // Calcular la posición de la matriz
    int gridSize = 32;  // Tamaño del sprite
    int x = static_cast<int>(scenePos.x()) / gridSize;
    int y = static_cast<int>(scenePos.y()) / gridSize;

    // Verificar si las coordenadas están dentro del rango
    if (map->isValidCoordinate(x, y)) {
        // Buscar y borrar sprites en la posición especificada
        QList<QGraphicsItem *> items = scene->items(QRectF(x * gridSize, y * gridSize, gridSize, gridSize));
        for (QGraphicsItem *item : items) {
            if (QGraphicsPixmapItem *pixmapItem = dynamic_cast<QGraphicsPixmapItem *>(item)) {
                QSize spriteSize = pixmapItem->pixmap().size();
                int spriteWidth = spriteSize.width();
                int spriteHeight = spriteSize.height();
                int widthInTiles = (spriteWidth > gridSize) ? (spriteWidth + gridSize - 1) / gridSize : 1;
                int heightInTiles = (spriteHeight > gridSize) ? (spriteHeight + gridSize - 1) / gridSize : 1;


                if (widthInTiles == 1 && heightInTiles == 1) {
                    // El sprite ocupa un solo tile, verificar si es terreno u objeto
                    if (pixmapItem->zValue() == 1) {  // Verificar si es un objeto
                        scene->removeItem(pixmapItem);
                        delete pixmapItem;
                        map->setObjectOccupied(x, y, false);
                        return;  // Solo queremos borrar un sprite por vez, así que salimos después de borrar uno
                    } else if (pixmapItem->zValue() == 0) {  // Verificar si es terreno
                        scene->removeItem(pixmapItem);
                        delete pixmapItem;
                        map->setOccupied(x, y, false);
                        return;  // Solo queremos borrar un sprite por vez, así que salimos después de borrar uno
                    }
                } else {
                    // El sprite ocupa más de un tile, necesitamos encontrar y borrar todos los sprites en esa área
                    for (int i = x; i < x + widthInTiles; ++i) {
                        for (int j = y; j < y + heightInTiles; ++j) {
                            QList<QGraphicsItem *> itemsAtPosition = scene->items(QRectF(i * gridSize, j * gridSize, gridSize, gridSize));
                            for (QGraphicsItem *subItem : itemsAtPosition) {
                                scene->removeItem(subItem);
                                delete subItem;
                            }
                            map->setSpriteOccupied(i, j, 1, 1, false, pixmapItem->zValue() == 1);
                        }
                    }
                    return;  // Solo queremos borrar un sprite por vez, así que salimos después de borrar uno
                }
            }
        }
    }
}
*/

void LevelEditor::eraseSpriteAtPosition(const QPointF &scenePos) {
    // Calcular la posición de la matriz
    int gridSize = 32;  // Tamaño del tile
    int x = static_cast<int>(scenePos.x()) / gridSize;
    int y = static_cast<int>(scenePos.y()) / gridSize;

    // Verificar si las coordenadas están dentro del rango
    if (map->isValidCoordinate(x, y)) {
        // Buscar y borrar sprites en la posición especificada
        QList<QGraphicsItem *> items = scene->items(QRectF(x * gridSize, y * gridSize, gridSize, gridSize));
        for (QGraphicsItem *item : items) {
            if (QGraphicsPixmapItem *pixmapItem = dynamic_cast<QGraphicsPixmapItem *>(item)) {
                QSize spriteSize = pixmapItem->pixmap().size();
                int spriteWidth = spriteSize.width();
                int spriteHeight = spriteSize.height();
                int widthInTiles = (spriteWidth > gridSize) ? (spriteWidth + gridSize - 1) / gridSize : 1;
                int heightInTiles = (spriteHeight > gridSize) ? (spriteHeight + gridSize - 1) / gridSize : 1;

                bool isObject = (pixmapItem->zValue() == 1);

                // Eliminar el sprite del QGraphicsScene
                scene->removeItem(pixmapItem);
                delete pixmapItem;

                // Actualizar la matriz de ocupación
                map->setSpriteOccupied(x, y, widthInTiles, heightInTiles, false, isObject);
                return;  // Solo queremos borrar un sprite por vez, así que salimos después de borrar uno
            }
        }
    }
}

