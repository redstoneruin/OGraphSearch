#ifndef BELLMANFORD_H
#define BELLMANFORD_H

#include <QObject>

#include "SearchAlg.h"

class BellmanFord : public SearchAlg
{
    Q_OBJECT
public:
    BellmanFord											(Grapher* grapher);

    void run											() override;

private:
    // number of points
    int n;
    // distances
    double *d;
    //parents
    GraphPoint** p;
    QList<GraphPoint*> open;

    void initializeSingleSource							();
    void relax											(GraphPoint* u, GraphPoint* v);

};

#endif // BELLMANFORD_H
