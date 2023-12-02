#include <iostream>
#include <mpi.h>
#include <string.h>

using namespace std;

#define CUT 6

int main(int argc, char **argv){
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int n=10, m=size; // m columns n rows
    char* A = new char[n*m];
    char B[n];
    int scores[size];
    if(rank == 0){
        for(int k = 0; k < n; ++k)
            cin >> B[k];
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                cin >> A[i*n + j];
    }

    char Alocal[n];
    MPI_Scatter(A, n, MPI_CHAR, Alocal, n, MPI_CHAR, 0, MPI_COMM_WORLD);

    MPI_Bcast(B, n, MPI_CHAR, 0, MPI_COMM_WORLD);
    int score = 0;
    for(int i=0; i<n; ++i)
        if(B[i] == Alocal[i])
            score += 1;
    MPI_Gather(&score, 1, MPI_INT, scores, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if(rank == 0){
        for(int j=0; j < size; ++j){
            if(scores[j] >= 6){
                cout << scores[j] << endl << "APROVADO" << endl;
            }
            else{
                cout << scores[j] << endl;
            }
        }
    }
    // string result = (score >= 6) ? 'APROVADO': 'REPROVADO';
    // cout << score << result << endl;

    // int mult = 0, sum=0;
    // for(int i=0; i<4; ++i)
    //     mult += Alocal[i]*B[i];
    // MPI_Gather(&mult, 1, MPI_INT, B, 1, MPI_INT, 0, MPI_COMM_WORLD);
    // if(rank == 0){
    //     for(int i=0; i < 4; ++i)
    //         cout << B[i] << " ";
    //     cout << endl;
    // }
    // MPI_Reduce(&mult, &sum, 1, MPI_INT, MPI_SUM, 1, MPI_COMM_WORLD);
    // cout << sum << endl;
    MPI_Finalize();
    return 0;
}