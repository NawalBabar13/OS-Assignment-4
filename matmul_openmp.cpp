#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Usage: ./matmul_openmp R C K\n";
        return 1;
    }

    int R = stoi(argv[1]);
    int Cc = stoi(argv[2]);
    int Kt = stoi(argv[3]);

    vector<vector<double>> A(R, vector<double>(Cc, 1.0));
    vector<vector<double>> B(Cc, vector<double>(Kt, 1.0));
    vector<vector<double>> Cmat(R, vector<double>(Kt, 0.0));

    auto start = chrono::high_resolution_clock::now();

    #pragma omp parallel for collapse(2)
    for(int i=0;i<R;i++)
        for(int j=0;j<Kt;j++)
            for(int k=0;k<Cc;k++)
                Cmat[i][j] += A[i][k] * B[k][j];

    auto end = chrono::high_resolution_clock::now();
    double ms = chrono::duration<double, milli>(end - start).count();

    cout << ms << endl;
    return 0;
}

