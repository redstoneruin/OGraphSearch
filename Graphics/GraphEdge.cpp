#include <QtDebug>
#include <QtMath>

#include "GraphEdge.h"

/**
 * Default constructor for graph edge, private
 * @brief GraphEdge::GraphEdge
 * @param parent
 */
GraphEdge::GraphEdge(QObject *parent) : QObject(parent)
{
    _id = 0;
    _p1 = _p2 = nullptr;
    _line = _arrowLine1 = _arrowLine2 = nullptr;
}


/**
 * Copy constructor for Graph Edge
 * @brief GraphEdge::GraphEdge
 * @param edge
 */
GraphEdge::GraphEdge(const GraphEdge &edge) : GraphEdge()
{
    _id = edge._id;
    _p1 = edge._p1;
    _p2 = edge._p2;
    _weight = edge._weight;
    updateLine();
}



/**
 * Construct new graph edge using two points
 * @brief GraphEdge::GraphEdge
 * @param p1
 * @param p2
 */
GraphEdge::GraphEdge(unsigned int id, GraphPoint* p1, GraphPoint* p2, double weight) : GraphEdge()
{
    _id = id;
    _p1 = p1;
    _p2 = p2;
    _weight = weight;
    updateLine();
}

// alternate constructors
GraphEdge::GraphEdge(GraphPoint* p1, GraphPoint* p2, double weight) : GraphEdge(0, p1, p2, weight){}


/**
 * Deconstructor for graph edge
 * @brief GraphEdge::~GraphEdge
 */
GraphEdge::~GraphEdge()
{
    if(_line != nullptr) {delete _line;}
    if(_arrowLine1 != nullptr) {delete _arrowLine1;}
    if(_arrowLine2 != nullptr) {delete _arrowLine2;}
}



// getters
unsigned int GraphEdge::id(){return _id;}
GraphPoint* GraphEdge::p1(){return _p1;}
GraphPoint* GraphEdge::p2(){return _p2;}
double GraphEdge::weight(){return _weight;}

QList<QGraphicsItem*> GraphEdge::graphicsItems()
{
    QList<QGraphicsItem*> items;
    items.push_back(_line);
    items.push_back(_arrowLine1);
    items.push_back(_arrowLine2);
    return items;
}

// setters
void GraphEdge::setWeight(double weight){_weight = weight;};
void GraphEdge::setId(unsigned int id){_id = id;}




/**
 * Update the line graphics item
 * @brief GraphEdge::updateLine
 */
void GraphEdge::updateLine()
{
    double arrowDisplacement = 10;


    if(_line == nullptr) {
        _line = new QGraphicsLineItem(_p2->x(), _p2->y(), _p1->x(), _p1->y());

        // make new lines from for the arrow head
        QLineF line1 = _line->line();
        line1.setLength(arrowDisplacement);

        QLineF line2(line1);

        line1.setAngle(line1.angle() + 45);
        line2.setAngle(line2.angle() - 45);

        _arrowLine1 = new QGraphicsLineItem(line1);
        _arrowLine2 = new QGraphicsLineItem(line2);
    } else {
        _line->setLine(_p1->x(), _p1->y(), _p2->x(), _p2->y());
    }
}




/**
 * Check whether edges are identical
 * @brief GraphEdge::sameAs
 * @param edge
 * @return
 */
bool GraphEdge::sameAs(const GraphEdge &edge)
{
    return (_p1 == edge._p1 && _p2 == edge._p2);
}
