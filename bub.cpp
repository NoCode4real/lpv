#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>
using namespace std;

void seqSort(vector<int>& a) {
    for (int i = 0, n = a.size(); i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j+1]) swap(a[j], a[j+1]);
}

void parSort(vector<int>& a) {
    for (int i = 0, n = a.size(); i < n; i++)
        #pragma omp parallel for
        for (int j = i % 2; j < n - 1; j += 2)
            if (a[j] > a[j+1]) swap(a[j], a[j+1]);
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    vector<int> a(n), b(n);
    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) cin >> a[i], b[i] = a[i];

    auto t1 = chrono::high_resolution_clock::now(); seqSort(a);
    auto t2 = chrono::high_resolution_clock::now(); parSort(b);
    auto t3 = chrono::high_resolution_clock::now();

    cout << "\nSequential Sorted: ";
    for (int x : a) cout << x << " ";
    cout << "\nTime: " << chrono::duration<double, milli>(t2 - t1).count() << " ms";

    cout << "\n\nParallel Sorted:   ";
    for (int x : b) cout << x << " ";
    cout << "\nTime: " << chrono::duration<double, milli>(t3 - t2).count() << " ms\n";
}
