#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QStyledItemDelegate>
#include <QString>
#include <unordered_map>
#include "customgraphicsview.h"
#include "qstring_hash.h"
#include "map.h"

namespace Ui {
    class LevelEditor;
}

class CustomDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CustomDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        return QSize(80, 40); // Ajusta el tamaño según tus necesidades
    }
};


class LevelEditor : public QMainWindow {
    Q_OBJECT

public:
    explicit LevelEditor(QWidget *parent = nullptr);
    ~LevelEditor();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private slots:
    void onGraphicsViewClicked(QMouseEvent *event);
    void onGraphicsViewMouseMoved(QMouseEvent *event);
    void onGraphicsViewMouseReleased(QMouseEvent *event);
    void onModeChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void placeSpriteAtPosition(const QPointF &scenePos);
    void eraseSpriteAtPosition(const QPointF &scenePos);
    void handleFileListClick(QListWidgetItem *item);
    void saveLevel();

private:
    Ui::LevelEditor *ui;
    QGraphicsScene *scene;
    Map *map;
    bool isMousePressed;
    QString currentMode;
    std::unordered_map<QString, int> ids;
    std::unordered_map<QString, int> initializeIds();
};

#endif // LEVELEDITOR_H




