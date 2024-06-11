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
#include "customgraphicsview.h"
#include "map.h"

namespace Ui {
class LevelEditor;
}

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

private:
    Ui::LevelEditor *ui;
    QGraphicsScene *scene;
    Map *map;
};

#endif // LEVELEDITOR_H




