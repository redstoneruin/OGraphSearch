#include <QtDebug>
#include <QtMath>

#include <QBrush>

#include "GraphPoint.h"

GraphPoint::GraphPoint(QObject *parent) : QObject(parent)
{
    _x = _y = _z = _id = 0;
    _selected = _src = _dst = false;
    _ellipse = nullptr;
}


/**
 * Copy constructor for GraphPoint type
 * @brief GraphPoint::GraphPoint
 * @param point
 */
GraphPoint::GraphPoint(const GraphPoint &point)
{
    _x = point._x;
    _y = point._y;
    _z = point._z;
    _id = point._id;
    updateEllipse();
}

/**
 * Constructor for GraphPoint with xyz and name
 * @brief GraphPoint::GraphPoint
 * @param x
 * @param y
 * @param z
 * @param name
 */
GraphPoint::GraphPoint(unsigned int id, double x, double y, double z) : GraphPoint()
{
    _x = x;
    _y = y;
    _z = z;
    _id = id;
    updateEllipse();
}


// alternate constructors
GraphPoint::GraphPoint(double x, double y, double z) : GraphPoint(0, x, y, z){}
GraphPoint::GraphPoint(double x, double y) : GraphPoint(0, x, y, 0){}


/**
 * Deconstructor for GraphPoint
 * @brief GraphPoint::~GraphPoint
 */
GraphPoint::~GraphPoint()
{
    delete _ellipse;
}


// getters
double GraphPoint::x(){return _x;}
double GraphPoint::y(){return _y;}
double GraphPoint::z(){return _z;}
unsigned int GraphPoint::id(){return _id;}
bool GraphPoint::selected(){return _selected;}
bool GraphPoint::src(){return _src;}
bool GraphPoint::dst(){return _dst;}

QList<GraphPoint*> GraphPoint::edges(){return _edges;}



/**
 * Return list of graphics items that represent this point
 * @brief GraphPoint::graphicsItems
 * @return
 */
QList<QGraphicsItem*> GraphPoint::graphicsItems()
{
    QList<QGraphicsItem*> items;

    items.push_back(_ellipse);

    return items;
}


// setters
void GraphPoint::setX(double x){_x = x;updateEllipse();}
void GraphPoint::setY(double y){_y = y;updateEllipse();}
void GraphPoint::setZ(double z){_z = z;updateEllipse();}
void GraphPoint::setId(unsigned int id){_id = id;}



/**
 * Set source point in graph
 * @brief GraphPoint::setSrc
 * @param src
 */
void GraphPoint::setSrc(bool src)
{
    _src = src;
    _color = src ? QColor::fromRgb(252, 5, 248) : QColor::fromRgb(0,0,0);

    // can set pen color if not selected
    if(!_selected) {
        _ellipse->setBrush(_color);
    }
}


/**
 * Set destination point in graph
 * @brief GraphPoint::setDst
 * @param dst
 */
void GraphPoint::setDst(bool dst)
{
    _dst = dst;
    _color = dst ? QColor::fromRgb(252,248,5) : QColor::fromRgb(0,0,0);

    if(!_selected) {
        _ellipse->setBrush(_color);
    }
}


/**
 * Add this edge to the graph
 * @brief GraphPoint::addEdge
 * @param e
 */
void GraphPoint::addEdge(GraphPoint* p2)
{

    // check whether this edge is already in edge list
    for(int i = 0; i < _edges.size(); i++) {
        GraphPoint* p1 = _edges.at(i);

        if(p1 == p2) {
            qDebug() << "Edge already attached";
            return;
        }
    }

    _edges.push_back(p2);
}


/**
 * Remove the edge to point p2 if exists
 * @brief GraphPoint::removeEdge
 * @param p2
 */
void GraphPoint::removeEdge(GraphPoint* p2)
{
    for(int i = 0; i < _edges.size(); ++i) {
         GraphPoint* p1 = _edges.at(i);

         // if this edge is in the list, delete
         if(p1 == p2) {
             _edges.removeAt(i);
             i--;
             return;
         }
    }
}


/**
 * Update the size and bounds of the ellipse for displaying this point
 * @brief GraphPoint::updateEllipse
 */
void GraphPoint::updateEllipse()
{
    int width, height;
    width = height = 10;

    // first delete old ellispe
    if(_ellipse != nullptr) {
        _ellipse->setRect(_x-width/2, _y-height/2, width, height);
    } else {
        // create new ellipse at coords
        _ellipse = new QGraphicsEllipseItem(_x-width/2, _y-height/2, width, height);
        _ellipse->setBrush(QBrush(QColor::fromRgb(0,0,0)));
    }
}


/**
 * Toggle this point's selected status
 * @brief GraphPoint::toggleSelect
 */
void GraphPoint::toggleSelect()
{
    setSelected(!_selected);
}

/**
 * Set this point's selected status
 * @brief GraphPoint::setSelected
 * @param selected
 */
void GraphPoint::setSelected(bool selected)
{
    //qDebug() << "setting selected: " << selected;
    if(selected) {
        _ellipse->setBrush(QBrush(QColor::fromRgb(0,255,0)));
    } else {
        _ellipse->setBrush(_color);
    }

    _selected= selected;
}


/**
 * Get the straight line distance from this point to the given point
 * @brief GraphPoint::distanceTo
 * @param p2
 * @return
 */
double GraphPoint::distanceTo(const GraphPoint &p2)
{
    double dx = p2._x - _x;
    double dy = p2._y - _y;


    return qSqrt(dx*dx+dy*dy);
}



