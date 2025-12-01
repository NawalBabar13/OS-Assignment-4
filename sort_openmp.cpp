#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <omp.h>
using namespace std;

int main(int argc, char* argv[]) {
    int n = (argc > 1) ? stoi(argv[1]) : 1000;
    vector<int> arr(n);
    for(int i=0;i<n;i++) arr[i] = rand();

    omp_set_num_threads(4);
    auto start = chrono::high_resolution_clock::now();
    #pragma omp parallel
    {
        #pragma omp single nowait
        sort(arr.begin(), arr.end());
    }
    auto end = chrono::high_resolution_clock::now();
    cout << chrono::duration<double, milli>(end-start).count() << endl;
}

