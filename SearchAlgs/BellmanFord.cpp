#include <QtDebug>

#include "BellmanFord.h"


// constructor for bellman ford algorithm
BellmanFord::BellmanFord(Grapher* grapher)
    : SearchAlg(grapher)
{
    n = 0;
    d = nullptr;
    p = nullptr;
}


/**
 * Run Bellman-Ford with source and dest points
 * @brief BellmanFord::run
 */
void BellmanFord::run()
{
    if(_src == nullptr) {
        qDebug() << "Need valid source to run Bellman-Ford";
        return;
    }

    n = _grapher->pointSize();


    // set new id for all points to keep track
    QList<GraphPoint*> points = _grapher->points();
    QList<GraphEdge*> edges = _grapher->edges();

    for(int i = 0; i < n; i++) {
        points.at(i)->setId(i);
    }


    // call setup function
    initializeSingleSource();

    // src is the first node to open
    open.clear();
    open.push_back(_src);

    QList<GraphPoint*> nextOpen;

    qDebug() << "Entering first loop";

    // enter main Bellman-Ford Loop
    for(int i = 0; i < open.size(); i++) {
        // i is path length, must loop through all edges with this path length
        GraphPoint* p = open.at(i);
        QList<GraphPoint*> pEdges = p->edges();

        qDebug() << "Entering second loop";

        //GraphPoint* u = points.at(i);
        for(int j = 0; j < pEdges.size(); j++) {
            GraphPoint* p2 = pEdges.at(j);
            nextOpen.push_back(p2);
            qDebug() << "Calling relax";
            relax(p, p2);
            qDebug() << "Relax ended";
        }

        // replace open list with new points
        open.clear();
        open = nextOpen;
        nextOpen.clear();
    }

    for(int i = 0; i < edges.size(); i++) {
        GraphEdge* e = edges.at(i);
        if(d[e->p2()->id()] > d[e->p1()->id()] + e->weight()) {
            qDebug() << "Negative weight cycle exists";
            return;
        }
    }

    qDebug() << "Path found";
}



/**
 * Initialize Bellman-Ford
 * @brief BellmanFord::initializeSingleSource
 */
void BellmanFord::initializeSingleSource()
{
    if(d != nullptr) free(d);
    if(p != nullptr) free(p);

    // allocate enough space for n distances and parents
    d = (double*) malloc (sizeof(double) * n);
    p = (GraphPoint**) malloc (sizeof(GraphPoint*) * n);

    double inf = std::numeric_limits<double>::max();

    // set distance infinite, parents nil
    for(int i = 0; i < n; i++) {
        d[i] = inf;
        p[i] = nullptr;
    }
    //qDebug() << "d[0]: " << d[0];

    // set the distance for root node at 0
    d[_src->id()] = 0;
}


/**
 * @brief BellmanFord::relax
 * @param u
 * @param v
 */
void BellmanFord::relax(GraphPoint* u, GraphPoint* v)
{
    // lookup edge
    GraphEdge* e = _grapher->getEdge(u, v);

    if(e == nullptr) {
        qDebug() << "Could not find edge";
        return;
    }

    if(d[v->id()] > d[u->id()] + e->weight()) {
        d[v->id()] = d[u->id()] + e->weight();
        p[v->id()] = u;
    }
}
