#include "leveleditor.h"
#include "ui_leveleditor.h"
#include <QIcon>
#include <QDebug>
#include <QDataStream>
#include <QResizeEvent>
#include <unordered_set>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include "spriteitem.h"

// Función para agregar SpriteItem a una QListWidget
void addSpriteItemToListWidget(QListWidget *listWidget, const QString &path, const QString &name, const QSize &size) {
    QIcon icon(path);
    SpriteItem *item = new SpriteItem(icon, size);
    item->setText(name);
    listWidget->addItem(item);
}

std::unordered_map<QString, int> LevelEditor::initializeIds() { //Diccionario de sprites/ids
    return {
        {"Floor", 13}, //ids de los tiles coinciden con los numeros de los archivos
        {"Background", 3},
        {"Floor Left Corner", 16}, //Cambiar nombre de archivo, no puede ser tile000.png
        {"Floor Right Corner", 1},
        {"Underground 1", 8},
        {"Underground 2", 9},

        {"Gold Coin", 0},
        {"Silver Coin", 1},
        {"Red Gem", 2},

        {"Spaz", 0},
        {"Rat", 1},
        {"Bat", 2},
        {"Diablo", 3}
    };
}

LevelEditor::LevelEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LevelEditor),
    map(new Map(30, 20)),  // Inicializa el mapa con el tamaño deseado
    isMousePressed(false), ids(initializeIds())
{
    ui->setupUi(this);

    // Calcular el tamaño de la escena
    int gridSize = 32;
    int sceneWidth = 30 * gridSize;
    int sceneHeight = 20 * gridSize;

    // Inicializar la escena
    scene = new QGraphicsScene(0, 0, sceneWidth, sceneHeight, this);
    ui->graphicsView->setScene(scene);

    addSpriteItemToListWidget(ui->terrainListWidget, ":/sprites/tile013.png", "Floor", QSize(32, 32));
    addSpriteItemToListWidget(ui->terrainListWidget, ":/sprites/tile000.png", "Floor Left Corner", QSize(32, 32));
    addSpriteItemToListWidget(ui->terrainListWidget, ":/sprites/tile001.png", "Floor Right Corner", QSize(32, 32));
    addSpriteItemToListWidget(ui->terrainListWidget, ":/sprites/tile008.png", "Underground 1", QSize(32, 32));
    addSpriteItemToListWidget(ui->terrainListWidget, ":/sprites/tile009.png", "Underground 2", QSize(32, 32));
    addSpriteItemToListWidget(ui->terrainListWidget, ":/sprites/tile003.png", "Background", QSize(32, 32));

    addSpriteItemToListWidget(ui->objectsListWidget, ":/sprites/gold_coin.png", "Gold Coin", QSize(23, 23));
    addSpriteItemToListWidget(ui->objectsListWidget, ":/sprites/silver_coin.png", "Silver Coin", QSize(23, 23));
    addSpriteItemToListWidget(ui->objectsListWidget, ":/sprites/red_gem.png", "Red Gem", QSize(25, 26));

    addSpriteItemToListWidget(ui->playerEnemiesListWidget, ":/sprites/spaz.png", "Spaz", QSize(45, 37));
    addSpriteItemToListWidget(ui->playerEnemiesListWidget, ":/sprites/rat.png", "Rat", QSize(67, 23));
    addSpriteItemToListWidget(ui->playerEnemiesListWidget, ":/sprites/bat.png", "Bat", QSize(21, 29));
    addSpriteItemToListWidget(ui->playerEnemiesListWidget, ":/sprites/diablo.png", "Diablo", QSize(43, 42));

    // Inicializar el diccionario
    initializeIds();

    // Habilitar la selección en la lista
    ui->terrainListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->objectsListWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    // Conectar la señal de clic al slot
    connect(ui->graphicsView, &CustomGraphicsView::mousePressed, this, &LevelEditor::onGraphicsViewClicked);
    connect(ui->graphicsView, &CustomGraphicsView::mouseMoved, this, &LevelEditor::onGraphicsViewMouseMoved);
    connect(ui->graphicsView, &CustomGraphicsView::mouseReleased, this, &LevelEditor::onGraphicsViewMouseReleased);
    connect(ui->fileList, &QListWidget::itemClicked, this, &LevelEditor::handleFileListClick);

    // Añadir modos a la lista de modos
    QListWidgetItem *putMode = new QListWidgetItem(QIcon(":/sprites/put.png"), "Put");
    ui->modeList->addItem(putMode);

    QListWidgetItem *eraseMode = new QListWidgetItem(QIcon(":/sprites/erase.png"), "Erase");
    ui->modeList->addItem(eraseMode);

    // Añadir guardar a las opciones
    QListWidgetItem *save = new QListWidgetItem(QIcon(":/sprites/save.png"), "Save");
    ui->fileList->addItem(save);

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
    delete map; 
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

int nextUniqueId = 0;

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
        QString identifier = selectedItem->text();
        int gridSize = 32;  // Tamaño del tile
        int spriteWidth = spriteSize.width();
        int spriteHeight = spriteSize.height();

        int x = static_cast<int>(scenePos.x()) / gridSize;
        int y = static_cast<int>(scenePos.y()) / gridSize;

        int widthInTiles = (spriteWidth > gridSize) ? (spriteWidth + gridSize - 1) / gridSize : 1;
        int heightInTiles = (spriteHeight > gridSize) ? (spriteHeight + gridSize - 1) / gridSize : 1;

        if (map->isValidCoordinate(x, y) && map->canPlaceSprite(x, y, widthInTiles, heightInTiles, isObject)) {
            QGraphicsPixmapItem *item = new QGraphicsPixmapItem(icon.pixmap(spriteWidth, spriteHeight));
            item->setPos(x * gridSize, y * gridSize);
            item->setZValue(isObject ? 1 : 0);
            scene->addItem(item);

            map->setSpriteOccupied(x, y, widthInTiles, heightInTiles, true, isObject, identifier, spriteSize, nextUniqueId);
            nextUniqueId++;
        }
    }
}

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

                // Calcular la posición de la esquina superior izquierda del sprite
                int startX = pixmapItem->pos().x() / gridSize;
                int startY = pixmapItem->pos().y() / gridSize;

                bool isObject = (pixmapItem->zValue() == 1);

                // Obtener el identificador del sprite
                SpriteInfo info = map->getSpriteInfo(startX, startY, isObject);
                QString identifier = info.identifier;

                // Eliminar el sprite del QGraphicsScene
                scene->removeItem(pixmapItem);
                delete pixmapItem;

                // Actualizar la matriz de ocupación
                map->setSpriteOccupied(startX, startY, widthInTiles, heightInTiles, false, isObject, identifier, spriteSize);
                return;  // Solo queremos borrar un sprite por vez, así que salimos después de borrar uno
            }
        }
    }
}



void LevelEditor::handleFileListClick(QListWidgetItem *item) {
    if (item->text() == "Save") {
        saveLevel();
    }
}


void LevelEditor::saveLevel() {
    YAML::Emitter out;

    // Obteniendo las dimensiones del mapa
    int rows = map->getRows();
    int cols = map->getCols();
    int tiles_num = rows * cols;

    // Encontrando el SpawnPoint
    int spawnX = -1, spawnY = -1;
    bool spawnPointAdded = false;
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (map->isObjectOccupied(x, y)) {
                QString identifier = map->getIdentifier(x, y, true);
                if (identifier == "Spaz" && !spawnPointAdded) {
                    spawnX = x * 32; 
                    spawnY = y * 32; 
                    spawnPointAdded = true;
                }
            }
        }
    }

    // Inicio del archivo YAML
    out << YAML::BeginMap;

    // Añadir el SpawnPoint
    if (spawnX != -1 && spawnY != -1) {
        out << YAML::Key << "SpawnPoint" << YAML::Value << YAML::BeginMap;
        out << YAML::Key << "x" << YAML::Value << spawnX;
        out << YAML::Key << "y" << YAML::Value << spawnY;
        out << YAML::EndMap;
    }

    // Añadir el número de tiles
    out << YAML::Key << "tiles_num" << YAML::Value << tiles_num;

    // Añadir las capas
    out << YAML::Key << "Layers" << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "height" << YAML::Value << rows;
    out << YAML::Key << "width" << YAML::Value << cols;
    out << YAML::Key << "tile_map" << YAML::Value << YAML::BeginSeq;

    for (int y = 0; y < rows; ++y) {
        out << YAML::Flow << YAML::BeginSeq;
        for (int x = 0; x < cols; ++x) {
            QString identifier = map->getIdentifier(x, y, false);
            if (!identifier.isEmpty()) {
                int id = ids[identifier];
                out << id;
            } else {
                out << 0; // 0 es el valor predeterminado para un tile vacío
            }
        }
        out << YAML::EndSeq;
    }

    out << YAML::EndSeq;
    out << YAML::EndMap;

    // Conjuntos para llevar el registro de objetos y enemigos ya añadidos
    QSet<int> addedEnemies;
    QSet<int> addedObjects;

    // Añadir los enemigos
    out << YAML::Key << "Enemies" << YAML::Value << YAML::BeginSeq;

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (map->isObjectOccupied(x, y)) {
                QString identifier = map->getIdentifier(x, y, true);
                int uniqueId = map->getUniqueId(x, y);
                if (identifier != "Spaz") {
                    int id = ids[identifier];
                    if (ui->playerEnemiesListWidget->findItems(identifier, Qt::MatchExactly).size() > 0) {
                        if (!addedEnemies.contains(uniqueId)) {
                            int realX = x * 32; 
                            int realY = y * 32; 

                            out << YAML::BeginMap;
                            out << YAML::Key << "enemy_id" << YAML::Value << id;
                            out << YAML::Key << "x" << YAML::Value << realX;
                            out << YAML::Key << "y" << YAML::Value << realY;
                            out << YAML::EndMap;

                            addedEnemies.insert(uniqueId);
                        }
                    }
                }
            }
        }
    }

    out << YAML::EndSeq;

    // Añadir los objetos
    out << YAML::Key << "Objects" << YAML::Value << YAML::BeginSeq;

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (map->isObjectOccupied(x, y)) {
                QString identifier = map->getIdentifier(x, y, true);
                int uniqueId = map->getUniqueId(x, y); 
                int id = ids[identifier];
                if (ui->objectsListWidget->findItems(identifier, Qt::MatchExactly).size() > 0) {
                    if (!addedObjects.contains(uniqueId)) {
                        int realX = x * 32; 
                        int realY = y * 32; 

                        out << YAML::BeginMap;
                        out << YAML::Key << "object_id" << YAML::Value << id;
                        out << YAML::Key << "x" << YAML::Value << realX;
                        out << YAML::Key << "y" << YAML::Value << realY;
                        out << YAML::EndMap;

                        addedObjects.insert(uniqueId);
                    }
                }
            }
        }
    }

    out << YAML::EndSeq;

    // Fin del archivo YAML
    out << YAML::EndMap;

    // Guardar en archivo
    std::ofstream fout("level.yaml");
    fout << out.c_str();
    fout.close();

    qDebug() << "Level saved to level.yaml";
}










