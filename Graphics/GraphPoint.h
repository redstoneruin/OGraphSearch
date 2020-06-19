#ifndef GRAPHPOINT_H
#define GRAPHPOINT_H

#include <QObject>
#include <QString>
#include <QGraphicsEllipseItem>

//class GraphEdge;

/**
 * Class for storing point implementation in visual graph.
 * Also stores attached edges for graph search
 * @brief The GraphPoint class
 */
class GraphPoint : public QObject
{
    Q_OBJECT
public:
    GraphPoint							(const GraphPoint &point);
    GraphPoint							(unsigned int id, double x, double y, double z);
    GraphPoint							(double x, double y, double z);
    GraphPoint							(double x, double y);
    ~GraphPoint							();

    // getters
    double x							();
    double y							();
    double z							();
    unsigned int id						();
    bool selected						();
    bool src							();
    bool dst							();


    double distanceTo					(const GraphPoint &p2);

    // return list of edges attached to this point
    QList<GraphPoint*> edges				();


    // add edge to this point. which check if this is
    // a valid edge on this point
    void addEdge						(GraphPoint* p2);
    void removeEdge						(GraphPoint* p2);


    QList<QGraphicsItem*> graphicsItems			();

    void setX							(double x);
    void setY							(double y);
    void setZ							(double z);
    void setId							(unsigned int id);
    void setSrc							(bool src);
    void setDst							(bool dst);

    void toggleSelect					();
    void setSelected					(bool selected);
signals:

private:
    explicit GraphPoint					(QObject *parent = nullptr);

    double _x, _y, _z;
    unsigned int _id;

    bool _selected, _src, _dst;

    QGraphicsEllipseItem* _ellipse;
    QColor _color;


    QList<GraphPoint*> _edges;

    void updateEllipse					();

};

#endif // GRAPHPOINT_H
