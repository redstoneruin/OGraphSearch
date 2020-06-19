#include "SearchAlg.h"

SearchAlg::SearchAlg(Grapher* grapher, QObject *parent) : QObject(parent)
{
    _grapher = grapher;
    _src = _dst = nullptr;
}

SearchAlg::SearchAlg(const SearchAlg &alg)
{
    _src = alg._src;
    _dst = alg._dst;
    _grapher = alg._grapher;
}



// getters
GraphPoint* SearchAlg::dst(){return _dst;}
GraphPoint* SearchAlg::src(){return _src;}


// setters
void SearchAlg::setDst(GraphPoint* dst)
{
    _dst = dst;
}
void SearchAlg::setSrc(GraphPoint *src)
{
    _src = src;
}



void SearchAlg::run(){}
