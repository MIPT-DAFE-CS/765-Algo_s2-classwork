/****************************************************************************
Задача 1_6.

Дан массив целых чисел A[0..n). Не используя других массивов
переставить элементы массива A в обратном порядке за O(n).
n ≤ 10000.

  in        | out
  ----------|----------
  4         | 2 -5 9 3
  3 9 -5 2  | 
****************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std ;
int main ()
{
    cin.tie(0);
    int n;
    int a;
    cin>>n;
    int arr [n];
    for (int i=0;i<n;++i){
        cin>>arr[i];
    }
    for (int i=0;i<n/2;++i){ 
        a=arr[i];
        arr[i]=arr[n-1-i];
        arr[n-1-i]=a;
    }
    
    for (int i=0;i<n;++i){
        cout<<arr[i]<<" ";
    }
    return 0;
}

