#include "tspgraph.h"
#include <QHash>
#include "edge.h"

TSPGraph::TSPGraph(unsigned int n, QVector<Vertex*> V) {

    N = n;

    Distances = new unsigned int* [n-1];
    for (unsigned int i = 0; i<(n-1) ; i++) {

        Distances[i] = new unsigned int[i+1];
        for (unsigned int j = 0 ; j<(i+1) ; j++)

            foreach(Edge *e, V.at(i+1)->getEdges())

                if(QString::compare(e->destVertex()->getID(),V.at(j)->getID())==0) {
                    Distances[i][j] = e->getLenght();
                    break;
                }
    }

    if (n<=1)
        hamiltonianCycle.cost = 0;
    else
        calculateCycle();
}


TSPGraph::~TSPGraph() {
    for (unsigned int i = 0 ; i < (N-1) ; i++) {
        delete [] Distances[i];
    }
    delete [] Distances;
}


unsigned int TSPGraph::cycleCost() const {
    return hamiltonianCycle.cost;
}

QVector<unsigned int> TSPGraph::travel() const {
    return hamiltonianCycle.road;
}

unsigned int TSPGraph::distance(unsigned int i, unsigned int j) const {

    if (i==j)
        return 0;
    else if (i<j)
        return Distances[j-1][i];
    else
        return Distances[i-1][j];
}

void TSPGraph::Keys(unsigned int s, QString key, unsigned int posI, QList<QString> &list) {
    if (s==0)
        list.append(key);
    else
        for (unsigned int i = posI ; i <= N-s ; i++)
            Keys(s-1,key+QString::number(i),i+1,list);
}

QList<QString> TSPGraph::cardinalKeys(unsigned int s) {

    QList<QString> list;

    if (s==N) {
        QString key = "";
        for (unsigned int i = 1 ; i < N ; i++)
            key = key + QString::number(i);
        list.append(key);
    }

    else
        Keys(s-1,"",1,list);

    return list;
}

void TSPGraph::calculateCycle() {

    QHash<QString,Cycle> tabl;

    for (unsigned int k = 1; k < N ; k++) {
        QString key = QString::number(k);
        Cycle cycle;
        cycle.cost = distance(0,k);
        cycle.road.append(k);
        tabl.insert(key,cycle);
    }

    for (unsigned int s = 3; s <= N ; s++) {

        QList<QString> Claves = cardinalKeys(s);
        foreach (QString key, Claves) {

            QString key2 = key;
            key2.remove(0,1);
            Cycle cycle;
            cycle.cost = tabl[key2].cost + distance((unsigned int)key[0].digitValue(),tabl[key2].road.last());
            cycle.road = tabl[key2].road;
            cycle.road.append((unsigned int)key[0].digitValue());
            tabl.insert(key,cycle);

            for (int i = 1 ; i < key.length() ; i++ ) {
                QString key2 = key;
                key2.remove(i,1);
                Cycle cycle;
                cycle.cost = tabl[key2].cost + distance((unsigned int)key[i].digitValue(), tabl[key2].road.last());

                if (cycle.cost < tabl[key].cost){
                    cycle.road = tabl[key2].road;
                    cycle.road.append((unsigned int)key[i].digitValue());
                    tabl.insert(key,cycle);
                }
            }
        }
    }

    QString keyV = "";
    for (unsigned int i = 1 ; i < N ; i++)
        keyV = keyV + QString::number(i);

    hamiltonianCycle.cost = tabl[keyV].cost + distance(tabl[keyV].road.last(),0);
    hamiltonianCycle.road = tabl[keyV].road;
}
