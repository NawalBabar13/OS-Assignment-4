#include <iostream>
#include <pthread.h>
#include <vector>
#include <chrono>
using namespace std;

int R, Cc, Kt, NUM_THREADS;

vector<vector<double>> A, B, Cmat;

void* worker(void* arg) {
    int tid = (long)arg;
    int start = tid * (R / NUM_THREADS);
    int end = (tid == NUM_THREADS-1) ? R : start + (R / NUM_THREADS);

    for(int i=start;i<end;i++)
        for(int j=0;j<Kt;j++)
            for(int k=0;k<Cc;k++)
                Cmat[i][j] += A[i][k] * B[k][j];

    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        cerr << "Usage: ./matmul_pthread R C K threads\n";
        return 1;
    }

    R = stoi(argv[1]);
    Cc = stoi(argv[2]);
    Kt = stoi(argv[3]);
    NUM_THREADS = stoi(argv[4]);

    A.assign(R, vector<double>(Cc, 1.0));
    B.assign(Cc, vector<double>(Kt, 1.0));
    Cmat.assign(R, vector<double>(Kt, 0.0));

    auto start = chrono::high_resolution_clock::now();

    vector<pthread_t> threads(NUM_THREADS);
    for(long t=0; t<NUM_THREADS; t++)
        pthread_create(&threads[t], NULL, worker, (void*)t);

    for(int t=0; t<NUM_THREADS; t++)
        pthread_join(threads[t], NULL);

    auto end = chrono::high_resolution_clock::now();
    double ms = chrono::duration<double, milli>(end - start).count();

    cout << ms << endl;
    return 0;
}

