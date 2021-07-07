#ifndef TSPGRAPH_H
#define TSPGRAPH_H

#include <QVector>
#include <QString>
#include <QList>
#include "vertex.h"

class TSPGraph {

    private:

        struct Cycle {
            unsigned int cost;
            QVector<unsigned int> road;
        };

        unsigned int N;
        unsigned int** Distances;
        Cycle hamiltonianCycle;

        void calculateCycle();
        QList<QString> cardinalKeys(unsigned int s);
        void Keys(unsigned int s, QString key, unsigned int posI, QList<QString> & list);


    public:

        TSPGraph(unsigned int n, QVector<Vertex *> V);

        ~TSPGraph();

        unsigned int distance(unsigned int i, unsigned int j) const;
        unsigned int cycleCost() const;
        QVector<unsigned int> travel() const;

};

#endif // TSPGRAPH_H
