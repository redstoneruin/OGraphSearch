#ifndef SEARCHALG_H
#define SEARCHALG_H

#include <QObject>
#include <QThread>

#include "Graphics/Grapher.h"
#include "Graphics/GraphEdge.h"
#include "Graphics/GraphPoint.h"


/**
 * Template class for search algorithms
 * @brief The SearchAlg class
 */
class SearchAlg : public QThread
{
    Q_OBJECT
public:
    explicit SearchAlg					(Grapher* grapher);
    explicit SearchAlg					(const SearchAlg &alg);

    // getters
    GraphPoint* src						();
    GraphPoint* dst						();

    virtual void run					();


signals:


public slots:

    // setters
    void setSrc							(GraphPoint* src);
    void setDst							(GraphPoint* dst);


protected:
    Grapher* _grapher;

    GraphPoint* _src;
    GraphPoint* _dst;
};

#endif // SEARCHALG_H
