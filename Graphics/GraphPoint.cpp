#include <QtDebug>
#include <QBrush>

#include "GraphPoint.h"

GraphPoint::GraphPoint(QObject *parent) : QObject(parent)
{
    _x = _y = _z = _id = 0;
    _selected = false;
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
QList<GraphPoint*> GraphPoint::edges(){return _edges;}


QList<QGraphicsItem*> GraphPoint::graphicsItems()
{
    QList<QGraphicsItem*> items;

    items.push_back(_ellipse);

    return items;
}

void GraphPoint::setX(double x){_x = x;updateEllipse();}
void GraphPoint::setY(double y){_y = y;updateEllipse();}
void GraphPoint::setZ(double z){_z = z;updateEllipse();}
void GraphPoint::setId(unsigned int id){_id = id;}


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


void GraphPoint::toggleSelect()
{
    setSelected(!_selected);
}

void GraphPoint::setSelected(bool selected)
{
    //qDebug() << "setting selected: " << selected;
    if(selected) {
        _ellipse->setBrush(QBrush(QColor::fromRgb(0,255,0)));
    } else {
        _ellipse->setBrush(QBrush(QColor::fromRgb(0,0,0)));
    }

    _selected= selected;
}






