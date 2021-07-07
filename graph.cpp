#include "graph.h"
#include "vertex.h"
#include <QtGui>
#include <QString>


Graph::Graph(QGraphicsScene *scene, int n){
    this->Scene=scene;
    this->nVertex = n;
    this->nSelectedVertex = 0;
}

Graph::~Graph(){

}

QRectF Graph::boundingRect() const{
    return QRectF(0,0,100,100);
}

unsigned int Graph::getNVertex() const{
    return nVertex;
}

unsigned int Graph::getNSelectedVertex() const
{
    return nSelectedVertex;
}

void Graph::addVertex(QGraphicsScene *scene, Ui::MainWindow *ui){
    QString id = "P";
    Vertex * v=new Vertex(id,ui);
    v->selected = true;
    V.append(v);
    V.at(0)->setPos(qrand()%500-200,qrand()%500-280);
    scene->addItem(v);
    for(unsigned int i=1; i<nVertex; i++){
        QString id = QString::number(i);
        Vertex * v=new Vertex(id,ui);
//        if(i % 2 == 0)
//            v->selected = true;
        V.append(v);
        V.at(i)->setPos(qrand()%500-200,qrand()%500-280);
        scene->addItem(v);
    }
//    this->insertSelectedV();
}

void Graph::reloadVertex(QGraphicsScene *scene)
{
    for(unsigned int i=1; i<nVertex; i++){
        scene->addItem(V.at(i));
    }
}


void Graph::allocateEdges(){
    for(unsigned int i=0; i<nSelectedVertex; i++){
        for(unsigned int j=0; j<nSelectedVertex; j++){
            if(j != i)
                addEdge(selectedV.at(i), selectedV.at(j));
        }
    }
}

void Graph::desallocateEdges()
{
    for(unsigned int i=0; i<nSelectedVertex; i++) {
        for(unsigned int j=0; j<nSelectedVertex; j++){
            if(j != i)
                removeEdge(selectedV.at(i), selectedV.at(j));
        }
    }
}


void Graph::drawPath(QVector<unsigned int> array)
{
    foreach (Edge* a, EdgesPainted)
        Scene->removeItem(a);

    EdgesPainted.clear();

    QString color = "blue";

    Edge * a = new Edge(selectedV.at(0),selectedV.at(array.at(0)),color);
    Scene->addItem(a);
    EdgesPainted.append(a);

    for(int i=1 ; i<array.size(); i++) {
        Edge* e = new Edge(selectedV.at(array.at(i-1)),selectedV.at(array.at(i)),color);
        Scene->addItem(e);
        EdgesPainted.append(e);
    }
    a = new Edge(selectedV.at(array.last()),selectedV.at(0),color);
    Scene->addItem(a);
    EdgesPainted.append(a);
}

void Graph::setVertex(QString id, int size, int weight)
{
    for(int i=0; i<V.size(); i++){
        if(id == V[i]->getId()){
            V[i]->setSize(size);
            V[i]->setWeight(weight);
            break;
        }
    }
}

void Graph::insertSelectedV()
{
    selectedV.clear();
    this->nSelectedVertex = 0;
    for(unsigned int i=0; i<V.size(); i++){
        if(V.at(i)->selected == true){
            this->nSelectedVertex++;
            selectedV.append(V.at(i));
        }
    }
    //printf("nombre des sommets selectione : %d\n",selectedV.size());
}

int Graph::totalWeight()
{
    int weight = 0;
    for(int i=1; i<selectedV.size(); i++)
        weight += selectedV.at(i)->getWeight();
    return weight;
}

int Graph::totalSize()
{
    int size = 0;
    for(int i=1; i<selectedV.size(); i++)
        size += selectedV.at(i)->getSize();
    return size;
}

void Graph::addEdge(Vertex *source, Vertex *dest)
{
    QString color= "black";
    Scene->addItem(new Edge(source, dest,color));
}

void Graph::removeEdge(Vertex *source, Vertex *dest)
{
    QString color= "white";
    Scene->addItem(new Edge(source, dest,color));
//    this->reloadVertex(Scene);
//    for(unsigned int i=1; i<nVertex; i++){
//        Scene->addItem(V.at(i));
//    }
}
