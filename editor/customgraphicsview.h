#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>

class CustomGraphicsView : public QGraphicsView
{
    Q_OBJECT

    public:
        explicit CustomGraphicsView(QWidget *parent = nullptr);

    signals:
        void mousePressed(QMouseEvent *event);
        void mouseMoved(QMouseEvent *event);
        void mouseReleased(QMouseEvent *event);

    protected:
        void mousePressEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // CUSTOMGRAPHICSVIEW_H

