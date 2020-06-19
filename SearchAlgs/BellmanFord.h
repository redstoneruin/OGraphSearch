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

    void initializeSingleSource							();

};

#endif // BELLMANFORD_H
