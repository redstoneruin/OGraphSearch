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

    // getters
    GraphPoint* p1						();
    GraphPoint* p2						();
    unsigned int id						();
    double weight						();

    // setters
    void setWeight						(double weight);
    void setId							(unsigned int id);
    void setColor						(int r, int g, int b, int a = 255);


    bool sameAs							(const GraphEdge &edge);


private:
    explicit GraphEdge					(QObject *parent = nullptr);

    // store point pointers that make up this edge
    GraphPoint* _p1;
    GraphPoint* _p2;

    // store graphics items to draw arrow
    QGraphicsLineItem* _line;
    QGraphicsLineItem* _arrowLine1;
    QGraphicsLineItem* _arrowLine2;
    QColor _color;

    unsigned int _id;

    double _weight;

    void updateLine						();
};

#endif // GRAPHEDGE_H
