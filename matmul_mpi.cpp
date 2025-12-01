#include <mpi.h>
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    if (argc < 4) {
        if (int rank; !MPI_Comm_rank(MPI_COMM_WORLD, &rank) && rank == 0)
            cerr << "Usage: mpirun -n P ./matmul_mpi R C K\n";
        MPI_Finalize();
        return 1;
    }

    int R = stoi(argv[1]);
    int Cc = stoi(argv[2]);
    int Kt = stoi(argv[3]);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rows_per_proc = R / size;
    int start = rank * rows_per_proc;
    int end = (rank == size - 1) ? R : start + rows_per_proc;

    vector<vector<double>> A(R, vector<double>(Cc, 1.0));
    vector<vector<double>> B(Cc, vector<double>(Kt, 1.0));
    vector<vector<double>> Cmat(R, vector<double>(Kt, 0.0));

    auto start_time = chrono::high_resolution_clock::now();

    for(int i=start;i<end;i++)
        for(int j=0;j<Kt;j++)
            for(int k=0;k<Cc;k++)
                Cmat[i][j] += A[i][k] * B[k][j];

    auto end_time = chrono::high_resolution_clock::now();
    double local_ms = chrono::duration<double, milli>(end_time - start_time).count();

    double max_time;
    MPI_Reduce(&local_ms, &max_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) cout << max_time << endl;

    MPI_Finalize();
    return 0;
}

