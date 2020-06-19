#include <QtDebug>

#include "BellmanFord.h"


// constructor for bellman ford algorithm
BellmanFord::BellmanFord(Grapher* grapher)
    : SearchAlg(grapher)
{

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

    GraphPoint* src = _src;

    QList<GraphPoint*> edges = src->edges();
    for(GraphPoint* edge : edges) {
        GraphEdge* e = _grapher->getEdge(_src, edge);
        e->setColor(0,255,0);
    }
}
