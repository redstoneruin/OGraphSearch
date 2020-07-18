#include <QtDebug>
#include <QTime>

#include "Dijkstra.h"

Dijkstra::Dijkstra(Grapher* grapher) : SearchAlg(grapher)
{
    p = nullptr;
    d = nullptr;
}



/**
 * Run Dijkstra alg on the grapher
 * @brief Dijkstra::run
 */
void Dijkstra::run()
{
    if(!setup()) {
        qDebug() << "Failed setup phase";
        return;
    }

    QList<GraphPoint*> Q = _grapher->points();

    // keep looping while nodes are still available
    while(Q.size() != 0) {

        // find min in distance
        double minDist = std::numeric_limits<double>::max();
        GraphPoint* u = nullptr;

        // store position in Q to delete
        int posInQ = 0;
        for(int i = 0; i < Q.size(); i++) {
            unsigned int id = Q.at(i)->id();
            if(d[id] < minDist) {
                u = Q.at(i);
                posInQ = i;
            }
        }

        // remove this point from open list
        Q.removeAt(posInQ);


        if(u == _dst) {
            qDebug() << "Found destination";
            return;
        }


        QList<GraphPoint*> neighbors = u->edges();

        // loop through each edge and determine weights
        for(int i = 0; i < neighbors.size(); i++) {
            GraphPoint* v = neighbors.at(i);
            // get this edge to find weight
            GraphEdge* e = _grapher->getEdge(u, v);
            e->setColor(0,255,0);
            qDebug() << "Setting color";
            double weight = e->weight();

            // find weight from source
            double alt = d[u->id()] + weight;

            // if this is lowest weight, update distance and parent
            if(alt < d[v->id()]) {
                d[v->id()] = alt;
                p[v->id()] = v->id();
            }
        }

        //int timestamp = QTime::currentTime().msecsSinceStartOfDay();

        //while(QTime::currentTime().msecsSinceStartOfDay() - timestamp < 1000) {
        //    continue;
        //}
    }
}



bool Dijkstra::setup()
{
    if(d != nullptr) {
        free(d);
    }

    if(_src == nullptr) {
        qDebug() << "Need source node to run Dijkstra's";
        return false;
    }
    if(_dst == nullptr) {
        qDebug() << "Need destination node to run Dijkstra's";
        return false;
    }

    QList<GraphPoint*> points = _grapher->points();

    int pointsSize = points.size();

    // create space for distance and seen arrays
    d = (double*) malloc (sizeof(double) * pointsSize);
    p = (unsigned int*) malloc (sizeof(unsigned int) * pointsSize);

    // set id of points to ensure in correct range
    for(int i = 0; i < pointsSize; i++) {
        points.at(i)->setId(i);
        p[i] = std::numeric_limits<unsigned int>::max();
        d[i] = std::numeric_limits<double>::max();
    }

    d[_src->id()] = 0;

    return true;

}
