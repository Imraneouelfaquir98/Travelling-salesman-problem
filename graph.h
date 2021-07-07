#ifndef GRAPH_H
#define GRAPH_H

#include <QtGui>
#include <QGraphicsView>
#include "edge.h"
#include "ui_mainwindow.h"

class Vertex;

class Graph : public QGraphicsView
{
private:

    void addEdge(Vertex *source, Vertex *dest);
    void removeEdge(Vertex *source, Vertex *dest);
    QGraphicsScene *Scene;
    unsigned int nVertex;
    unsigned int nSelectedVertex;
    QVector <Vertex*> V;
    QVector <Vertex*> selectedV;
    QList<Edge*> EdgesPainted;
    QList<Edge*> EdgesPaintedOfSelectedV;

public:

    Graph(QGraphicsScene *scene,int n);
        ~Graph();

    QRectF boundingRect() const;
    unsigned int getNVertex() const;
    unsigned int getNSelectedVertex() const;
    void addVertex(QGraphicsScene *scene, Ui::MainWindow * ui);
    //void reloadVertex(QGraphicsScene *scene);
    void reloadVertex(QGraphicsScene *scene);
    void allocateEdges();
    void desallocateEdges();
    QVector <Vertex*> getVector() const {return V;}
    Vertex * getVectorAt(int i) const {return V.at(i);}
    QVector <Vertex*> getSelectedVector() const {return selectedV;}
    void drawPath(QVector<unsigned int> array);
    void setVertex(QString id, int size, int weight);
    void insertSelectedV();
    int totalWeight();
    int totalSize();

};

#endif // GRAPH_H
