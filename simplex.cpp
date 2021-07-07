#include <iostream>
#include "simplex.h"
#include "operators.h"

using namespace std;

Simplex::Simplex(){}
Simplex::Simplex(vector<vector<float>>a, vector<float>b, vector<float>c, vector<string> ineg, string P){

    problem = P;
    rows = a.size();
    cols = a[0].size();

    Solution.resize( cols , 0);
    BasicSolution.resize( c.size() + b.size(), 0 );

    A = a;
    B = b;
    C = c;

    if(problem == "Max")
        C = c;

    else if(problem == "Min")
            C = -1*c;

    Ineg = ineg;

    int nbr = 0;
    for (int i = 0; i < Ineg.size(); i++){
        if(Ineg[i] == ">="){
            nbr++;
        }
    }

    C.resize(cols + rows , 0);
    A.resize( rows , vector<float>( rows + cols + nbr,0));

    for (int i=0; i < A.size(); i++){
        A[i].resize(rows + cols + nbr,0);
    }

    StandarForme();
}

void Simplex::StandarForme(){
    BaseIndex.resize( rows );
    int nbr = 0;

    for(int i=0 ; i<rows ; i++){

        if(Ineg[i] == ">="){
            towPhase = true;
            A[i][cols+i] = -1;
            A[i][rows+cols+nbr] = 1;
            BaseIndex[i] = rows+cols+nbr;
            nbr++;
        }
        else if(Ineg[i] == "<="){
            A[i][cols+i] = 1;
            BaseIndex[i] = cols+i;
        }
    }

}

bool Simplex::Phase1(){

    W.resize( A[0].size() ,0);
    ObjW = 0;

    for(int i=0 ; i<rows ; i++){
        if(Ineg[i] == ">="){
            W[BaseIndex[i]] = -1;
        }
    }

    for(int i=0 ; i<rows ; i++){
        if(Ineg[i] == ">="){
            ObjW += B[i];
            W = W + A[i];
        }
    }

    while(!ChekOptimalSimplex(W)){

        int *Pivot = GetPivot(W);

        float valPivot = A[Pivot[0]][Pivot[1]];
        float   bPivot = B[Pivot[0]];
        float   wPivot = W[Pivot[1]];

        A[Pivot[0]] = A[Pivot[0]]/valPivot;
        B[Pivot[0]] = B[Pivot[0]]/valPivot;

        for(int i=0 ; i<rows ; i++){
            if(i != Pivot[0] ){
                float currentPivot = A[i][Pivot[1]];

                A[i] = A[i] - currentPivot*A[Pivot[0]];
                B[i] = B[i] - currentPivot*B[Pivot[0]];
            }
        }
        BaseIndex[Pivot[0]] = Pivot[1];

        W = W - wPivot*A[Pivot[0]];
        ObjW -= wPivot*B[Pivot[0]];

        for(int i=0 ; i<rows ; i++)
            BasicSolution[BaseIndex[i]] = B[i];

        for(int i=0 ; i<cols ; i++)
            Solution[i] = BasicSolution[i];
    }

    if(ObjW == 0){
        for(int i=0 ; i<rows ; i++){
            A[i].resize(cols + rows);

            float cCurrent = C[BaseIndex[i]];
            C = C - cCurrent*A[i];
            ObjectifFunction -= cCurrent*B[i];
        }
        return true;
    }
    return false;
}


void Simplex::PivotageSimplex(){
    while(!ChekOptimalSimplex(C)){

        int *Pivot = GetPivot(C);

        float valPivot = A[Pivot[0]][Pivot[1]];
        float   bPivot = B[Pivot[0]];
        float   cPivot = C[Pivot[1]];

        A[Pivot[0]] = A[Pivot[0]]/valPivot;
        B[Pivot[0]] = B[Pivot[0]]/valPivot;

        for(int i=0 ; i<rows ; i++)
            if(i != Pivot[0] )
                if(A[i][Pivot[1]] != 0){
                    float currentPivot = A[i][Pivot[1]];
                    A[i] = A[i] - currentPivot*A[Pivot[0]];
                    B[i] = B[i] - currentPivot*B[Pivot[0]];
                }

        BaseIndex[Pivot[0]] = Pivot[1];

        if(C[Pivot[1]] != 0){
            C = C - cPivot*A[Pivot[0]];
            ObjectifFunction -= cPivot*B[Pivot[0]];
        }

        for(int i=0 ; i<BasicSolution.size() ; i++)
            BasicSolution[i] = 0;
        for(int i=0 ; i<rows ; i++)
            BasicSolution[BaseIndex[i]] = B[i];

        for(int i=0 ; i<cols ; i++)
            Solution[i] = BasicSolution[i];
    }

    if(problem == "Max")
        ObjectifFunction = -ObjectifFunction;

}




bool Simplex::ChekOptimalSimplex(vector<float> T){
    for(int i=0 ; i<T.size() ; i++)
        if(T[i] > 0)
           return false;
    return true;
}



int * Simplex::GetPivot(vector <float> G){
    int *Pivot = new int[2];
    vector <float> tmp(B.size(),-1);

    Pivot[0] = -1;
    Pivot[1] = -1;

    Pivot[1] = IndexMinPositiveStrinct(G);
    //Pivot[1] = max_element(G.begin(),G.end()) - G.begin();

    for(int i=0; i<rows ; i++)
        if(A[i][Pivot[1]]>0)
            tmp[i] = B[i]/A[i][Pivot[1]];

    Pivot[0] = IndexMinPositive(tmp);

    return Pivot;
}

int Simplex::IndexMinPositive(vector <float> V){
    int indexMin = max_element(V.begin(),V.end()) - V.begin();

    for(int i=0; i<V.size() ; i++)
        if(V[i]>=0 && V[i]<V[indexMin])
            indexMin = i;

    return (V[indexMin]>=0) ? indexMin : -1 ;
}

int Simplex::IndexMinPositiveStrinct(vector <float> V){
    int indexMin = max_element(V.begin(),V.end())-V.begin();

    /*for(int i=0; i<V.size() ; i++)
        if(V[i]>0 && V[i]<V[indexMin])
            indexMin = i;*/

    return (V[indexMin]>0) ? indexMin : -1 ;
}

void Simplex::Solve(){
    if(towPhase){
        if(Phase1())
            PivotageSimplex();
        else
            realisable = false;
    }
    else
        PivotageSimplex();
}


void Simplex::print(){
    cout<<"\n\n";
    for(int j=0 ; j<A.size() ; j++){
        for(int i=0 ; i<A[0].size() ; i++){
            if(A[j][i] < 0)
                printf("   %2.1f",A[j][i]);
            else
                printf("    %2.1f",A[j][i]);
        }
        printf("       %2.1f\n",B[j]);
    }
    cout<<""<<endl;
    for(int i=0 ; i<C.size() ; i++){
        if(C[i] < 0)
            printf("   %2.1f",C[i]);
        else
            printf("    %2.1f",C[i]);
    }

    printf("      Z*=%2.1f",ObjectifFunction);

    cout<<"\n\n"<<"l\'indice de la base :\n    I = [ ";
    for(int i=0 ; i<rows ; i++){
        cout<<BaseIndex[i];
        if(i != rows-1) cout<<", ";
    }
    cout<<"]"<<endl;

    cout<<"\n"<<"Solution de base :\n    S = [ ";
    for(int i=0 ; i<rows+cols ; i++){
        cout<<BasicSolution[i];
        if(i != rows+cols-1) cout<<", ";
    }
    cout<<"]"<<endl;

    cout<<"\n"<<"Solution : "<<endl;
    for(int i=0 ; i<cols ; i++)
        cout<<"   Variable_"<<i+1<<" = "<<Solution[i]<<endl;
    cout<<"\nMax Z = "<<ObjectifFunction<<endl;
    printf("\n\n===============================================================\n\n");

}

void Simplex::printPhase1(){
    cout<<"\n\n";
    for(int j=0 ; j<A.size() ; j++){
        for(int i=0 ; i<A[0].size() ; i++){
            if(A[j][i] < 0)
                printf("   %2.1f",A[j][i]);
            else
                printf("    %2.1f",A[j][i]);
        }
        printf("       %2.1f\n",B[j]);
    }
    cout<<""<<endl;
    for(int i=0 ; i<W.size() ; i++){
        if(W[i] < 0)
            printf("   %2.1f",W[i]);
        else
            printf("    %2.1f",W[i]);
    }

    printf("      W*=%2.1f",ObjW);

    cout<<"\n\n"<<"l\'indice de la base :\n    I = [ ";
    for(int i=0 ; i<rows ; i++){
        cout<<BaseIndex[i];
        if(i != rows-1) cout<<", ";
    }
    cout<<"]"<<endl;

    cout<<"\n"<<"Solution de base :\n    S = [ ";
    for(int i=0 ; i<rows+cols ; i++){
        cout<<BasicSolution[i];
        if(i != rows+cols-1) cout<<", ";
    }
    cout<<"]"<<endl;

    cout<<"\n"<<"Solution : "<<endl;
    for(int i=0 ; i<cols ; i++)
        cout<<"   Variable_"<<i+1<<" = "<<Solution[i]<<endl;
    printf("\n\n==========================Phase 1======================\n\n");

}
