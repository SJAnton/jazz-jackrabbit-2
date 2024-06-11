#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>

class CustomGraphicsView : public QGraphicsView {
    Q_OBJECT

    public:
        CustomGraphicsView(QWidget *parent = nullptr) : QGraphicsView(parent) {}

    signals:
        void clicked(QMouseEvent *event);

    protected:
        void mousePressEvent(QMouseEvent *event) override {
            QGraphicsView::mousePressEvent(event);
            emit clicked(event);
        }
};

#endif // CUSTOMGRAPHICSVIEW_H
