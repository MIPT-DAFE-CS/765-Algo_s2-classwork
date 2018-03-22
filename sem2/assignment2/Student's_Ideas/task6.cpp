#include <iostream>
#include <queue>
#include <vector>
#include <limits>

using namespace std;

void floid (int** arr, int n) {
    for (int k(0);k<n;++k) {
        for (int i(0);i<n;++i) {
            for (int j(0);j<n;++j) {
                if (arr[i][j]>arr[i][k]+arr[k][j]) {
                    arr[i][j]=arr[i][k]+arr[k][j];
                }
            }
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    int** arr = new int* [n];
    for (int i(0);i<n;++i) {
        arr[i] = new int[n];
    }
    for (int i(0); i < n; ++i)
    {
        for (int j(0); j<n; ++j) {
            std::cin >> arr[i][j];
        }
    }
    floid (arr,n);
    for (int i(0); i < n; ++i)
    {
        for (int j(0); j<n; ++j) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}



/*
 0 5 7 13
 12 0 2 8
 11 16 0 7
 4 9 11 0
 */









