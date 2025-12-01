#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Usage: ./matmul_seq R C K\n";
        return 1;
    }

    int R = stoi(argv[1]);
    int C = stoi(argv[2]);
    int K = stoi(argv[3]);

    vector<vector<double>> A(R, vector<double>(C, 1.0));
    vector<vector<double>> B(C, vector<double>(K, 1.0));
    vector<vector<double>> Cmat(R, vector<double>(K, 0.0));

    auto start = chrono::high_resolution_clock::now();

    for(int i=0;i<R;i++)
        for(int j=0;j<K;j++)
            for(int k=0;k<C;k++)
                Cmat[i][j] += A[i][k] * B[k][j];

    auto end = chrono::high_resolution_clock::now();
    double ms = chrono::duration<double, milli>(end - start).count();

    cout << ms << endl;
    return 0;
}

