#include <QMessageBox>
#include <QPixmap>
#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graph.h"
#include "vertex.h"
#include "edge.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("salesman.jpg");
    ui->label_pic->setPixmap(pix); //setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio));

    ui->backButton_1->setIcon(QIcon("backIcon.png"));
    ui->backButton_2->setIcon(QIcon("backIcon.png"));

    Scene = new QGraphicsScene(0,0,300,300);
    View = new QGraphicsView(Scene);
    View->scale(qreal(0.9), qreal(0.9));
    Timer = new QTimer(this);
    connect(Timer, SIGNAL(timeout()),this, SLOT(myTimer()));
    Timer->start(0);
    //ui->statusBar->showMessage("Drag and drop any node and use zoom with scrollbar",0);
    graph  = NULL;
    solutionGraph = NULL;
    createInterface();
}

MainWindow::~MainWindow()
{
    delete Scene;
    delete View;
    delete Timer;
    if (graph != NULL)
        delete graph;
    delete centralLayout;
    delete ui;
}

void MainWindow::myTimer()
{
    Scene->update();
}

void MainWindow::createInterface()
{
    View->setRenderHint(QPainter::Antialiasing);
    View->setMinimumSize(800, 800);
    centralLayout = new QHBoxLayout();
    centralLayout->addWidget(View);
    centralLayout->addStretch();
    ui->viewContentLayout->addLayout(centralLayout);
}


void MainWindow::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if(username == "imrane" && password == "imrane"){
        ui->stackedWidget->setCurrentIndex(1);
        ui->lineEdit_username->setText("");
        ui->lineEdit_password->setText("");
    }
    else{
        QMessageBox::warning(this,"Warning","User name or password is incorrect");
        ui->lineEdit_username->setText("");
        ui->lineEdit_password->setText("");
    }
}


void MainWindow::on_realMapButton_clicked(){
    ui->stackedWidget->setCurrentIndex(2);
    ui->webView->load(QUrl("http://maps.google.com"));
}

void MainWindow::on_virtualMapButton_clicked(){
    ui->stackedWidget->setCurrentIndex(3);
}

//================== Sign out buttons =====================

void MainWindow::on_singOutButton_1_clicked(){
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_signOutButton_2_clicked(){
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_signOutButton_3_clicked(){
    ui->stackedWidget->setCurrentIndex(0);
}

//================== Back buttons =====================
void MainWindow::on_backButton_1_clicked(){
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::on_backButton_2_clicked(){
    ui->stackedWidget->setCurrentIndex(1);
}



void MainWindow::on_generateButton_clicked()
{
    Scene->clear();
    if(ui->nVertex->text().toInt()>0)
    {
        graph = new Graph(Scene, ui->nVertex->text().toInt()+1);
        graph->addVertex(Scene,ui);
    }
}

void MainWindow::on_BAndBButton_clicked()
{
    if(ui->nVertex->text().toInt()>0)
    {
        vector <vector<float>> A(graph->getNVertex()+1,vector<float>(graph->getNVertex()-1,0));
        vector <float> B(graph->getNVertex()+1,1);
        vector <float> C(graph->getNVertex()-1,1);
        vector <string> Ineg(graph->getNVertex()+1,"<=");

        B[0] = graph->getVectorAt(0)->getWeight();
        B[1] = graph->getVectorAt(0)->getSize();

        for(int i=0; i<A[0].size(); i++){
            A[0][i] = graph->getVectorAt(i+1)->getWeight();
            A[1][i] = graph->getVectorAt(i+1)->getSize();
        }
        for(int i=0; i<A.size()-2; i++)
            A[i+2][i] = 1;

        BranchAndBound BB = BranchAndBound(A, B, C, Ineg, "Max");
        BB.CalculBranchAndBound(A, B, C, Ineg, "Max");

        for(int i = 0; i<BB.SolInteger.size(); i++){
            if(BB.SolInteger[i] == 1){
                graph->getVectorAt(i+1)->selected = true;
            }
            else {
                graph->getVectorAt(i+1)->selected = false;
            }
        }

        graph->insertSelectedV();
        ui->sizeWeight->setText(QString::number(graph->totalSize())+"\n"+QString::number(graph->totalWeight()));
        graph->allocateEdges();
    }
}

void MainWindow::print(vector<vector<float> > A, vector<float> B, vector<float> C, vector<float> S, vector<string> Ineg)
{
    cout<<"\n\n_____Resolution Branch and Bound_____\n"<<endl;
    for(int j=0 ; j<A.size() ; j++){
        for(int i=0 ; i<A[0].size() ; i++)
            printf("    %4.0f",A[j][i]);
        cout<<"     "<<Ineg[j];
        printf("   %4.0f\n",B[j]);
    }
    cout<<""<<endl;
    for(int i=0 ; i<C.size() ; i++)
        printf("    %4.0f",C[i]);
    cout<<"\n"<<endl;
    for(int i=0; i<S.size() ; i++)
            cout<<"x"<<i<<" = "<<S[i]<<endl;
    printf("A = %d, AA = %d, C = %d, B = %d\n",A.size(),A[0].size(),C.size(),B.size());
}

void MainWindow::on_calculTSPButton_clicked()
{
    if(graph != NULL)
    {
        solutionGraph = new TSPGraph(graph->getNSelectedVertex(),graph->getSelectedVector());
        ui->labelResut->setText(QString::number(solutionGraph->cycleCost()));
        graph->desallocateEdges();
        if(graph->getNSelectedVertex() > 1)
            graph->drawPath(solutionGraph->travel());
        delete solutionGraph;
        solutionGraph = NULL;
    }
}

void MainWindow::on_zoomIn_clicked()
{
    scaleView(qreal(1.2));
}

void MainWindow::on_zoomOut_clicked()
{
    scaleView(1 / qreal(1.2));
}

void MainWindow::scaleView(qreal scaleFactor)
{
    View->scale(scaleFactor, scaleFactor);
}

void MainWindow::on_setButton_clicked()
{
    if(ui->Idlabel->text() != "     ...     "){
        if(ui->size->text() == "" && ui->weight->text() == ""){
            QMessageBox::warning(this,"Warning","Please fill the weight and size");
        }
        else if(ui->size->text() != "" && ui->weight->text() == ""){
            QMessageBox::warning(this,"Warning","Please fill the weight");
        }
        else if(ui->size->text() == "" && ui->weight->text() != ""){
            QMessageBox::warning(this,"Warning","Please fill the size");
        }
        else{
            graph->setVertex(ui->Idlabel->text(),ui->size->text().toInt(),ui->weight->text().toInt());
        }
    }
}

