#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <QObject>

#include "SearchAlg.h"

class Dijkstra : public SearchAlg
{
    Q_OBJECT
public:
    explicit Dijkstra(Grapher* grapher);

    void run						() override;

signals:


private:
    double* d;
    unsigned int* p;

    bool setup						();

};

#endif // DIJKSTRA_H
