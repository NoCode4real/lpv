#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>
using namespace std;

void sequentialMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C) {
    int n = A.size(), m = B[0].size(), p = A[0].size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            for (int k = 0; k < p; ++k)
                C[i][j] += A[i][k] * B[k][j];
}

void parallelMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C) {
    int n = A.size(), m = B[0].size(), p = A[0].size();
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            for (int k = 0; k < p; ++k)
                C[i][j] += A[i][k] * B[k][j];
}

int main() {
    int n, m, p;
    cout << "Enter dimensions (A: n x p, B: p x m)\n";
    cin >> n >> p >> m;

    vector<vector<int>> A(n, vector<int>(p));
    vector<vector<int>> B(p, vector<int>(m));
    vector<vector<int>> C_seq(n, vector<int>(m, 0));
    vector<vector<int>> C_par(n, vector<int>(m, 0));

    cout << "Enter matrix A:\n";
    for (auto& row : A) for (int& x : row) cin >> x;
    cout << "Enter matrix B:\n";
    for (auto& row : B) for (int& x : row) cin >> x;

    auto t1 = chrono::high_resolution_clock::now();
    sequentialMultiply(A, B, C_seq);
    auto t2 = chrono::high_resolution_clock::now();

    auto t3 = chrono::high_resolution_clock::now();
    parallelMultiply(A, B, C_par);
    auto t4 = chrono::high_resolution_clock::now();

    cout << "\nSequential Result:\n";
    for (auto& row : C_seq) for (int x : row) cout << x << " ";
    cout << "\nTime: " << chrono::duration<double, milli>(t2 - t1).count() << " ms\n";

    cout << "\nParallel Result:\n";
    for (auto& row : C_par) for (int x : row) cout << x << " ";
    cout << "\nTime: " << chrono::duration<double, milli>(t4 - t3).count() << " ms\n";

    return 0;
}
