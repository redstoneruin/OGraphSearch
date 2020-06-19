#include <QtDebug>

#include "Grapher.h"


/**
 * Default constructor for grapher, requires graphics view widget
 * @brief Grapher::Grapher
 * @param graphicsView
 * @param parent
 */
Grapher::Grapher(GraphicsView* graphicsView, QObject *parent) : QObject(parent)
{

    _graphics = graphicsView;
    _scene = new QGraphicsScene();
    _graphics->setScene(_scene);

    src = dst = nullptr;

    // connect mouse click event
    connect(_graphics, &GraphicsView::mouseClicked, this, &Grapher::handleClick);
    connect(_graphics, &GraphicsView::mouseDoubleClicked, this, &Grapher::handleDoubleClick);
}



/**
 * Set source node based on the selected point
 * @brief Grapher::setSource
 */
void Grapher::setSource()
{
    if(_selectedPoints.size() != 1) {
        qDebug() << "Must select a single point for source";
        return;
    }

    // check whether should remove the old src node
    if(src != nullptr) {
        src->setSrc(false);
    }

    src = _selectedPoints.at(0);
    src->setSrc(true);

    unselectAll();

    emit newSrc(src);
}




/**
 * Set destination node based on the selected point
 * @brief Grapher::setDest
 */
void Grapher::setDest()
{
    if(_selectedPoints.size() != 1) {
        qDebug() << "Must select a single point for source";
        return;
    }

    // check whether should remove the old src node
    if(dst != nullptr) {
        dst->setSrc(false);
    }

    dst = _selectedPoints.at(0);
    dst->setDst(true);

    unselectAll();

    emit newDst(dst);
}


/**
 * Add point to this graph
 * @brief Grapher::addPoint
 * @param x
 * @param y
 * @param z
 * @param name
 */
void Grapher::addPoint(double x, double y, double z)
{
    // create a new point which can be added to the graph
    _points.push_back(new GraphPoint(x, y, z));
    QList<QGraphicsItem*> items = _points.back()->graphicsItems();

    // add all associated graphics items
    for(QGraphicsItem* item : items) {
        _scene->addItem(item);
    }

}



/**
 * Remove all selectedPoints
 * @brief Grapher::removePoint
 */
void Grapher::removeSelectedPoints()
{

    for(int i = 0; i < _points.size(); i++) {
        GraphPoint* point = _points.at(i);

        // check for edges attached to this point
        for(int j = 0; j < _edges.size(); j++) {
            GraphEdge* e = _edges.at(j);

            if(e->p1() == point || e->p2() == point) {
                // point attached, delete this edge
                QList<QGraphicsItem*> items = e->graphicsItems();
                for(int k = 0; k < items.size(); k++) {
                    _scene->removeItem(items.at(k));
                }
                _edges.removeAt(j);
                delete e;
                j--;
            }
        }

        // if this point is selected, remove from list
        if(point->selected()) {
            QList<QGraphicsItem*> items = point->graphicsItems();
            for(int i = 0; i < items.size(); i++) {
                _scene->removeItem(items.at(i));
            }
            _points.removeAt(i);
            delete point;
            i--;
        }
    }
    // remove all selected points
    _selectedPoints.clear();
}



/**
 * Add edge to graph using selected points
 * @brief Grapher::addEdge
 */
void Grapher::addEdge(double weight)
{
    if(_selectedPoints.size() != 2) {
        qDebug() << "Must select 2 points";
        return;
    }

    GraphPoint* p1;
    GraphPoint* p2;

    p1 = _selectedPoints.at(0);
    p2 = _selectedPoints.at(1);

    GraphEdge edge1(p1, p2, weight);


    // look through edges to see if this edge already exists
    for(int i = 0; i < _edges.size(); i++) {
        GraphEdge* edge2 = _edges.at(i);

        // determine whether
        if(edge2->sameAs(edge1)) {
            // edge already exists, can return
            qDebug() << "Edge exists";
            unselectAll();
            return;
        }
    }

    // if edge does not exists, add to edges
    _edges.push_back(new GraphEdge(edge1));

    // add this edge to the point for easier traversal later
    p1->addEdge(p2);

    QList<QGraphicsItem*> items = _edges.back()->graphicsItems();
    for(int i = 0; i < items.size(); i++) {
        _scene->addItem(items.at(i));
    }

    unselectAll();
}


/**
 * Remove edge based on highlighted points
 * @brief Grapher::removeEdge
 */
void Grapher::removeEdge()
{
    if(_selectedPoints.size() != 2) {
        qDebug() << "Must select 2 points";
        return;
    }

    GraphPoint* p1;
    GraphPoint* p2;
    p1 = _selectedPoints.at(0);
    p2 = _selectedPoints.at(1);

    GraphEdge e1(p1, p2, 0);

    // loop through edges to see if selected edge exists
    for(int i = 0; i < _edges.size(); i++) {
        GraphEdge* e2 = _edges.at(i);

        // if the edge is found, can delete
        if(e2->sameAs(e1)) {

            // remove all associated graphics items
            QList<QGraphicsItem*> items = e2->graphicsItems();
            for(int j = 0; j < items.size(); j++) {
                _scene->removeItem(items.at(j));
            }
            p1->removeEdge(p2);
            _edges.removeAt(i);
            delete e2;
            qDebug() << "Edge removed";
            unselectAll();
            return;
        }
    }
}




/**
 * Return the edge between these two points if exists
 * @post returns pointer of edge if found, nullptr if not
 * @brief Grapher::getEdge
 * @param p1 Entry point
 * @param p2 Exit point
 * @return
 */
GraphEdge* Grapher::getEdge(GraphPoint *p1, GraphPoint *p2)
{
    // loop through all edges to find the edge
    // TODO make faster version, possibly hash table
    for(int i = 0; i < _edges.size(); i++) {
        GraphEdge* e1 = _edges.at(i);
        GraphEdge e2(p1, p2, 0);
        if(e1->sameAs(e2)) {
            return e1;
        }
    }

    qDebug() << "Could not find edge";
    return nullptr;
}



/**
 * Handle mouse click, selection of nodes and edges
 * @brief Grapher::mouseClicked
 * @param point
 */
void Grapher::handleClick(QPointF)
{
    for(int i = 0; i < _points.length(); i++) {
        // check whether point selection should be toggled
        GraphPoint* point = _points.at(i);
        bool underMouse = false;

        QList<QGraphicsItem*> items = point->graphicsItems();

        // find whether any of the graphics items from this point
        // are under the cursor at this time
        for(int j = 0; j < items.size(); j++) {
            if(items.at(j)->isUnderMouse()) {
                underMouse = true;
                break;
            }
        }

        if(underMouse) {
            point->toggleSelect();

            // determine whether to add or remove this point
            // from the list
            if(point->selected()) {
                _selectedPoints.push_back(point);
            } else {
                for(int j = 0; j < _selectedPoints.length(); j++) {
                    if(_selectedPoints.at(j) == point) {
                        // found an identical point
                        _selectedPoints.removeAt(j);
                        break;
                    }
                }
            }
        }
    }
}


/**
 * Unselect all currently selected points
 * @brief Grapher::unselectAll
 */
void Grapher::unselectAll()
{
    for(int i = 0; i < _selectedPoints.size(); i++) {
        GraphPoint* p = _selectedPoints.at(i);
        p->toggleSelect();
    }
    _selectedPoints.clear();
}



/**
 * Handle double click event
 * @brief Grapher::handleDoubleClick
 * @param point
 */
void Grapher::handleDoubleClick(QPointF point)
{
    addPoint(point.x(), point.y(), 0);
}
