#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QDialog>
#include <QHBoxLayout>
#include <vector>

#include "vertex.h"
#include "graph.h"
#include "tspgraph.h"
#include "branchandbound.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);   // Constructor del MainWindow
    ~MainWindow();                              // Destructor
    void createInterface();

    Ui::MainWindow *ui;


private slots:

    void on_pushButton_login_clicked();
    void on_singOutButton_1_clicked();
    void on_realMapButton_clicked();
    void on_virtualMapButton_clicked();
    void on_signOutButton_2_clicked();
    void on_backButton_1_clicked();
    void on_backButton_2_clicked();
    void on_signOutButton_3_clicked();
    void myTimer(void);
    void on_generateButton_clicked();
    void on_calculTSPButton_clicked();
    void on_zoomIn_clicked();
    void on_zoomOut_clicked();
    void on_setButton_clicked();
    void on_BAndBButton_clicked();

private:

    QHBoxLayout *centralLayout;
    Graph *graph;
    TSPGraph * solutionGraph;
    QGraphicsScene *Scene;
    QGraphicsView *View;
    QTimer *Timer;

    void print(vector<vector<float> > A, vector<float> B, vector<float> C, vector<float> S, vector<string> Ineg);

    void scaleView(qreal scaleFactor);
};
#endif // MAINWINDOW_H
