#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include "edge.h"
#include "vertex.h"
#include "graph.h"

#include "ui_mainwindow.h"

Vertex::Vertex(QString id, Ui::MainWindow *ui)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    this->id=id;
    this->ui = ui;
    //connect(this,SIGNAL(),,SLOT());
}

Vertex::~Vertex()
{

}

void Vertex::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}
QString Vertex::getID() const
{
    return id;
}

void Vertex::setSize(int s)
{
    this->size = s;
}

void Vertex::setWeight(int w)
{
    this->weight = w;
}

unsigned int Vertex::getSize()
{
    return this->size;
}

unsigned int Vertex::getWeight()
{
    return this->weight;
}

QString Vertex::getId()
{
    return this->id;
}

QRectF Vertex::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -10 - adjust, -10 - adjust, 33 + adjust, 33 + adjust);
}

void Vertex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    QRadialGradient gradient(-3, -3, 10);
    if (option->state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, QColor(Qt::yellow).light(120));
        gradient.setColorAt(0, QColor(Qt::darkYellow).light(120));
    }
    else {
        if(this->id == "P"){
            gradient.setColorAt(0, Qt::red);
            gradient.setColorAt(1, Qt::darkRed);
        }else{
            gradient.setColorAt(0, Qt::blue);
            gradient.setColorAt(1, Qt::darkBlue);
        }
    }
    painter->setBrush(gradient);

    painter->setPen(QPen(Qt::black, 0));                                                // Dibuja el borde de la elipse
    if(this->id == "P"){
        painter->drawEllipse(-10, -10, 30, 30);
        painter->setPen(QPen(Qt::white, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->setFont(QFont("Arial", 16, QFont::Bold));
        painter->drawText(QPointF(0, 12),this->id);
    }
    else {
        painter->drawEllipse(-10, -10, 20, 20);
        painter->setPen(QPen(Qt::white, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->setFont(QFont("Arial", 14, QFont::Bold));
        painter->drawText(QPointF(-4, 6),this->id);                                         // Dibuja el ID del vertice
    }                                        // Dibuja el ID del vertice
}

QVariant Vertex::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        foreach (Edge *edge, edgeList)
            edge->adjust();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void Vertex::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    ui->Idlabel->setText(this->id);
    ui->weight->setText(QString::number(this->weight));
    ui->size->setText(QString::number(this->size));
    if(this->selected)
        ui->selected->setText("Selected");
    else
        ui->selected->setText("Not selected");
    QGraphicsItem::mousePressEvent(event);
}

void Vertex::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}


