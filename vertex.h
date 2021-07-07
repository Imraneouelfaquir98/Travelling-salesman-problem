#ifndef VERTEX_H
#define VERTEX_H

#include <QGraphicsItem>
#include <QList>
#include "ui_mainwindow.h"


class Edge;
class Graph;
class QGraphicsSceneMouseEvent;

class Vertex : public QGraphicsItem
{

private:

    QList<Edge *> edgeList;
    QString id;
    unsigned int size = 0;
    unsigned int weight = 0;

    // funciones privadas
    QRectF boundingRect() const;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:

    bool selected = false;
    Vertex(QString id, Ui::MainWindow * ui);
    ~Vertex();
    void addEdge(Edge *edge);
    QString getID() const;
    void setSize(int s);
    void setWeight(int w);
    unsigned int getSize();
    unsigned int getWeight();
    QString getId();
    QList <Edge*> getEdges() const {return edgeList;}

    Ui::MainWindow * ui;

};
#endif // VERTEX_H
