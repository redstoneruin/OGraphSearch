#ifndef BELLMANFORD_H
#define BELLMANFORD_H

#include <QObject>

#include "SearchAlg.h"

class BellmanFord : public SearchAlg
{
    Q_OBJECT
public:
    BellmanFord(Grapher* grapher);

    void run() override;
};

#endif // BELLMANFORD_H
