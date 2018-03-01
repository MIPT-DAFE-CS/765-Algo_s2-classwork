/****************************************************************************
Задача 2_3.

Даны два строго возрастающих массива целых чисел A[0..n) и
B[0..m) и число k. Найти количество таких пар индексов (i, j), что
A[i] + B[j] = k. Время работы O(n + m). n, m ≤ 100000.

*Указание.* Обходите массив B от конца к началу.

  in             | out
  ---------------|-----
  4              | 3
  -5 0 3 18      | 
  5              | 
  -10 -2 4 7 12  | 
  7              | 

****************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std ;

int main(){
    int n,m,k;
    cin>>n;
    int arr1[n];
    for (int i(0);i<n;++i) {
        cin>>arr1[i];
    }
    cin>>m;
    int arr2[m];
    for (int i(0);i<m;++i) {
        cin>>arr2[i];
    }
    cin>>k;
    
    int left(0),ans(0);
    for (int i(m-1);i>=0;i-=1) {
        while (arr1[left]+arr2[i]<=k && left<=n-1) {
            if (arr1[left]+arr2[i]==k) ans+=1;
            left+=1;
        }
    }
    cout<<ans<<endl;
    return 0;
}


