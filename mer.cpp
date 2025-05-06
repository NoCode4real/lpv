#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>
using namespace std;

void merge(vector<int>& a, int l, int m, int r) {
    vector<int> t;
    int i = l, j = m + 1;
    while (i <= m && j <= r) t.push_back(a[i] <= a[j] ? a[i++] : a[j++]);
    while (i <= m) t.push_back(a[i++]);
    while (j <= r) t.push_back(a[j++]);
    for (int k = 0; k < t.size(); k++) a[l + k] = t[k];
}

void seqSort(vector<int>& a, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        seqSort(a, l, m);
        seqSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

void parSort(vector<int>& a, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            { parSort(a, l, m); }

            #pragma omp section
            { parSort(a, m + 1, r); }
        }
        merge(a, l, m, r);
    }
}

int main() {
    int n; cout << "Enter number of elements: "; cin >> n;
    vector<int> a(n), b(n);
    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) cin >> a[i], b[i] = a[i];

    auto t1 = chrono::high_resolution_clock::now(); seqSort(a, 0, n - 1);
    auto t2 = chrono::high_resolution_clock::now(); parSort(b, 0, n - 1);
    auto t3 = chrono::high_resolution_clock::now();

    cout << "\nSequential: "; for (int x : a) cout << x << " ";
    cout << "\nTime: " << chrono::duration<double, milli>(t2 - t1).count() << " ms\n";

    cout << "\nParallel:   "; for (int x : b) cout << x << " ";
    cout << "\nTime: " << chrono::duration<double, milli>(t3 - t2).count() << " ms\n";
}
