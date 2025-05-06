#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>
using namespace std;

int partition(vector<int>& a, int l, int h) {
    int p = a[h], i = l - 1;
    for (int j = l; j < h; j++) if (a[j] <= p) swap(a[++i], a[j]);
    swap(a[i + 1], a[h]);
    return i + 1;
}

void seqSort(vector<int>& a, int l, int h) {
    if (l < h) {
        int p = partition(a, l, h);
        seqSort(a, l, p - 1);
        seqSort(a, p + 1, h);
    }
}

void parSort(vector<int>& a, int l, int h) {
    if (l < h) {
        int p = partition(a, l, h);
        #pragma omp parallel sections
        {
            #pragma omp section { parSort(a, l, p - 1); }
            #pragma omp section { parSort(a, p + 1, h); }
        }
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
