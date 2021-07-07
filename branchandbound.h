#ifndef BRANCHANDBOUND_H
#define BRANCHANDBOUND_H

#include <vector>
#include "simplex.h"

class BranchAndBound
{
public:

    int rows;
    int cols;

    int Max ;
    vector<float> SolInteger;
    Simplex PL ;//= new Simplex();

    vector <vector<float>> A;
    vector <float> B;
    vector <float> C;
    vector <string> Inegalite;

    string problem;
    BranchAndBound(vector<vector<float>>a, vector<float>b, vector<float>c, vector<string> ing, string P);
    void CalculBranchAndBound(vector<vector<float>>a, vector<float>b, vector<float>c, vector<string> ing, string p);
    bool ChekIntegerSolution(vector<float>S);
    void print();

};

#endif // BRANCHANDBOUND_H
