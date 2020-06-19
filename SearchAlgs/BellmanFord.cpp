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
    if(_src == nullptr || _dst == nullptr) {
        qDebug() << "Need valid source and destination to run Bellman-Ford";
        return;
    }

    n = _grapher->pointSize();


    // set new id for all points to keep track
    QList<GraphPoint*> points = _grapher->points();
    for(int i = 0; i < n; i++) {
        points.at(i)->setId(i);
    }


    // call setup function
    void initializeSingleSource();
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

    // set the distance for root node at 0
    p[_src->id()] = 0;
}
