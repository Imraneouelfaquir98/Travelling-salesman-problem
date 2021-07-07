#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <vector>
#include <string>
#include <bits/stdc++.h>



using namespace std;


class Simplex
{
public:
    int rows;
    int cols;

    vector<vector<float>> A;
    vector<float> B;
    vector<float> C;
    vector<float> BasicSolution;
    vector<float> Solution;
    vector<float> BaseIndex;
    vector<float> W;

    vector<string> Ineg;


    string problem;

    float ObjectifFunction = 0;
    float ObjW ;

    bool towPhase = false;
    bool realisable = true;

    Simplex();
    Simplex(vector<vector<float>>a, vector<float>b, vector<float>c, vector<string> Ineg, string P);

    void   StandarForme();
    void   print();
    void   printPhase1();
    bool   PhaseOne();
    bool   Phase1();
    void   PivotageSimplex();
    bool   ChekOptimalSimplex(vector <float> T);
    int  * GetPivot(vector <float> G);
    int    IndexMinPositive(vector <float> V);
    int    IndexMinPositiveStrinct(vector <float> V);
    void   Solve();
};

#endif // SIMPLEX_H
