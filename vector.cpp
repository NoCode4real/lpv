#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>
using namespace std;

void sequentialMultiply(const vector<vector<int>>& mat, const vector<int>& vec, vector<int>& res) {
    for (int i = 0; i < mat.size(); ++i)
        for (int j = 0; j < vec.size(); ++j)
            res[i] += mat[i][j] * vec[j];
}

void parallelMultiply(const vector<vector<int>>& mat, const vector<int>& vec, vector<int>& res) {
    #pragma omp parallel for
    for (int i = 0; i < mat.size(); ++i)
        for (int j = 0; j < vec.size(); ++j)
            res[i] += mat[i][j] * vec[j];
}

int main() {
    int n, m;
    cout << "Enter rows and columns of matrix: ";
    cin >> n >> m;

    vector<vector<int>> mat(n, vector<int>(m));
    vector<int> vec(m), res_seq(n, 0), res_par(n, 0);

    cout << "Enter matrix:\n";
    for (auto& row : mat) for (int& x : row) cin >> x;

    cout << "Enter vector:\n";
    for (int& x : vec) cin >> x;

    auto t1 = chrono::high_resolution_clock::now();
    sequentialMultiply(mat, vec, res_seq);
    auto t2 = chrono::high_resolution_clock::now();

    auto t3 = chrono::high_resolution_clock::now();
    parallelMultiply(mat, vec, res_par);
    auto t4 = chrono::high_resolution_clock::now();

    cout << "\nSequential Result:\n";
    for (int x : res_seq) cout << x << " ";
    cout << "\nTime: " << chrono::duration<double, milli>(t2 - t1).count() << " ms\n";

    cout << "\nParallel Result:\n";
    for (int x : res_par) cout << x << " ";
    cout << "\nTime: " << chrono::duration<double, milli>(t4 - t3).count() << " ms\n";

    return 0;
}