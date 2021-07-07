#include "branchandbound.h"

#include <iostream>

BranchAndBound::BranchAndBound(vector <vector<float>>a, vector <float>b, vector <float>c, vector<string> ing, string P){
    SolInteger.resize( a[0].size() , 0);
    PL = Simplex(a,b,c,ing,P);
    PL.Solve();

    for(int i=0 ; i<PL.Solution.size() ; i++)
        SolInteger[i] = PL.Solution[i];
    Max=0;


    problem = P;
    rows = a.size();
    cols = a[0].size();

    A.resize( rows , vector<float>( cols , 0 ) );
    B.resize( b.size() );
    C.resize( cols , 0 );
    Inegalite.resize( rows );

        for(int i=0 ; i<rows ; i++)
            for(int j= 0; j< cols;j++ )
                A[i][j] = a[i][j];

        for(int i=0 ; i< cols ; i++ )
            C[i] = c[i];

        for(int i=0 ; i< rows ; i++ ){
            B[i] = b[i];
            Inegalite[i] = ing[i];
        }
}


bool BranchAndBound::ChekIntegerSolution(vector<float>S){
      for(int i=0 ; i<S.size() ; i++)
              if(S[i] != floor(S[i]))
                      return false;
      return true;
}

void BranchAndBound::CalculBranchAndBound(vector <vector<float>>a, vector <float>b, vector <float>c, vector<string> ing, string p){


    PL = Simplex(a,b,c,ing,p);
    PL.Solve();

    if(PL.realisable == true){

        if(ChekIntegerSolution(PL.Solution)){
            if(Max < PL.ObjectifFunction){
                Max = PL.ObjectifFunction;
                for(int i=0 ; i<PL.Solution.size() ; i++)
                    SolInteger[i] = PL.Solution[i];
            }
        }
        else{
                int i=0;
                while( i<PL.Solution.size() && PL.Solution[i] == floor(PL.Solution[i]))
                    i++;

                ing.resize( ing.size()+1,"<=");
                b.resize( b.size()+1 , floor(PL.Solution[i]));

                a.resize( a.size()+1 ,vector<float>(a[0].size(),0));
                a[a.size()-1][i] = 1;


                CalculBranchAndBound(a,b,c,ing,p);

                ing[ing.size()-1] = ">=";
                b[b.size()-1] += 1;

                CalculBranchAndBound(a,b,c,ing,p);
        }
    }
}


void BranchAndBound::print(){

    cout<<"\n\n_____Resolution Branch and Bound_____\n"<<endl;
    for(int j=0 ; j<A.size() ; j++){
        for(int i=0 ; i<A[0].size() ; i++)
            printf("    %4.2f",A[j][i]);
        cout<<"  "<<Inegalite[j];
        printf("       %4.2f\n",B[j]);
    }
    cout<<""<<endl;
    for(int i=0 ; i<cols ; i++)
        printf("    %4.2f",C[i]);
    cout<<"\n"<<endl;
    for(int i=0; i<SolInteger.size() ; i++)
        cout<<"x"<<i<<" = "<<SolInteger[i]<<endl;
    cout<<"\nMax = "<<Max<<"\n\n"<<endl;

}

