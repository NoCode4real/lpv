#include <iostream>
#include <omp.h>
using namespace std;

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    int arr[n];
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) cin >> arr[i];

    int minv = arr[0], maxv = arr[0], sum = 0;

    #pragma omp parallel for reduction(min:minv) reduction(max:maxv) reduction(+:sum)
    for (int i = 0; i < n; i++) {
        if (arr[i] < minv) minv = arr[i];
        if (arr[i] > maxv) maxv = arr[i];
        sum += arr[i];
    }

    cout << "Min: " << minv << "\nMax: " << maxv << "\nSum: " << sum << "\nAverage: " << (double)sum / n << '\n';
    return 0;
}
