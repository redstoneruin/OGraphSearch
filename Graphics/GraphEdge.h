#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H

#include <QObject>

#include "GraphPoint.h"

class GraphEdge : public QObject
{
    Q_OBJECT
public:
    GraphEdge							(const GraphEdge &edge);
    GraphEdge							(unsigned int id, GraphPoint* p1, GraphPoint* p2, double weight = 0);
    GraphEdge							(GraphPoint* p1, GraphPoint* p2, double weight);
    ~GraphEdge							();

    QList<QGraphicsItem*> graphicsItems			();

    GraphPoint* p1						();
    GraphPoint* p2						();
    unsigned int id						();
    double weight						();

    void setWeight						(double weight);
    void setId							(unsigned int id);

    bool sameAs							(const GraphEdge &edge);

private:
    explicit GraphEdge					(QObject *parent = nullptr);

    GraphPoint* _p1;
    GraphPoint* _p2;

    QGraphicsLineItem* _line;
    QGraphicsLineItem* _arrowLine1;
    QGraphicsLineItem* _arrowLine2;

    unsigned int _id;

    double _weight;

    void updateLine						();
};

#endif // GRAPHEDGE_H
