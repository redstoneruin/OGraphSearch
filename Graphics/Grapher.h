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

    // get the edge object between these two points, if exists
    // O(n)
    GraphEdge* getEdge				(GraphPoint* p1, GraphPoint* p2);

    // get point by id O(n)
    GraphPoint* getPoint			(unsigned int id);

    // set source and destination points for search
    // based on currently selected point
    void setSource					();
    void setDest					();

    GraphPoint* src						();
    GraphPoint* dst						();

    int pointSize						();
    int edgeSize						();
    QList<GraphPoint*> points			();
    QList<GraphEdge*> edges				();

signals:
    void newSrc						(GraphPoint* src);
    void newDst						(GraphPoint* dst);

public slots:
    void addPoint					(double x, double y, double z);
    void removeSelectedPoints		();

    // add edge using selected points
    void addEdge					(double weight);
    void removeEdge					();

    // unselect all currently selected points
    void unselectAll				();

private slots:
    void handleClick				(QPointF point);
    void handleDoubleClick			(QPointF point);

private:
    GraphicsView* _graphics;
    QGraphicsScene* _scene;
    QList<GraphPoint*> _points, _selectedPoints;
    QList<GraphEdge*> _edges;

    GraphPoint* _src;
    GraphPoint* _dst;

    unsigned int pointId, edgeId;
};

#endif // GRAPHER_H
