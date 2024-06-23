#include "customgraphicsview.h"

CustomGraphicsView::CustomGraphicsView(QWidget *parent) : QGraphicsView(parent) {}

void CustomGraphicsView::mousePressEvent(QMouseEvent *event) {
    emit mousePressed(event);
    QGraphicsView::mousePressEvent(event);
}

void CustomGraphicsView::mouseMoveEvent(QMouseEvent *event) {
    emit mouseMoved(event);
    QGraphicsView::mouseMoveEvent(event);
}

void CustomGraphicsView::mouseReleaseEvent(QMouseEvent *event) {
    emit mouseReleased(event);
    QGraphicsView::mouseReleaseEvent(event);
}
