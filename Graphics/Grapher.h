#ifndef GRAPHER_H
#define GRAPHER_H

#include <QObject>
#include <QList>
#include <QString>

//#include "GraphPoint.h"
#include "GraphEdge.h"
#include "GraphicsView.h"

/**
 * Class for drawing graph points and edges in graphics widget
 * @brief The Grapher class
 */
class Grapher : public QObject
{
    Q_OBJECT
public:
    explicit Grapher(GraphicsView* graphicsView, QObject *parent = nullptr);

    // set source and destination points for search
    // based on currently selected point
    void setSource();
    void setDest();


signals:

public slots:
    void addPoint					(double x, double y, double z);
    void removeSelectedPoints		();

    // add edge using selected points
    void addEdge					(double weight);
    void removeEdge					();

    void unselectAll				();

private slots:
    void handleClick				(QPointF point);
    void handleDoubleClick			(QPointF point);

private:
    GraphicsView* _graphics;
    QGraphicsScene* _scene;
    QList<GraphPoint*> _points, _selectedPoints;
    QList<GraphEdge*> _edges;

    GraphPoint* src;
    GraphPoint* dst;

    unsigned int pointId, edgeId;
};

#endif // GRAPHER_H
