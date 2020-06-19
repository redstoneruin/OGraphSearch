#include <QtDebug>
#include <QMouseEvent>

#include "GraphicsView.h"

GraphicsView::GraphicsView() : QGraphicsView()
{

}


/**
 * Event for mouse pressed
 * @brief GraphicsView::mousePressEvent
 * @param event
 */
void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    QPointF point = this->mapToScene(event->pos());
    emit mouseClicked(point);
}

void GraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    QPointF point = this->mapToScene(event->pos());
    emit mouseDoubleClicked(point);
}
