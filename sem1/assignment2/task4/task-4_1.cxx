/****************************************************************************
 Задача 4_1. Первые k элементов длинной последовательности.

Дана очень длинная последовательность целых чисел длины n. Требуется вывести
в отсортированном виде её первые k элементов. Последовательность может не
помещаться в память. Время работы O(n * log(k)). Доп. память O(k).
Использовать слияние.

in                 | out
------------------ | ---
9 4                | 1 2 3 4
3 7 4 5 6 1 15 4 2 |

****************************************************************************/

//Created by Yaishenka
//Copyright © 2017 Yaishenka. All rights reserved.
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include  <stdint.h>
using namespace std;

void Merge (int* arr1,int* arr2,int n1,int n2,int* ans) {
    int i(0),j(0);
    while (i<n1 && j<n2) {
        if (arr1[i]<=arr2[j]){
            ans[i+j]=arr1[i];
            ++i;
        } else {
            ans[i+j]=arr2[j];
            ++j;
        }
    }
    if (i==n1) {
        for (;j<n2;++j) {
            ans[i+j]=arr2[j];
        }
    } else if (j==n2) {
        for (;i<n1;++i) {
            ans[i+j]=arr1[i];
        }
    }
}
void MergeSort (int* arr,int n){
    if (n<=1) {
        return;
    }
    int leftl,rightl;
    leftl=n/2;
    rightl=n-leftl;
    MergeSort(arr, leftl);
    MergeSort(arr+leftl,rightl);
    int* ans=new int[n];
    Merge (arr,arr+leftl,leftl,rightl,ans);
    for (int i(0);i<n;++i) {
        arr[i]=ans[i];
    }
    //memcpy( arr, ans, sizeof( int ) * n );
    delete[] ans;
}
int main () {
    int n,k,count(0);
    cin>>n>>k;
    int arr[2*k];
    for (int i(0);i<k;++i) {
        cin>>arr[i];
        count+=1;
    }
    //cout<<count<<endl;
    while (count<n) {
        for (int i(k);i<2*k && count<n;++i) {
            cin>>arr[i];
            count+=1;
        }
        MergeSort(arr, 2*k);
    }
    for (int i(0);i<k;++i) {
        cout<<arr[i]<<" ";
    }
}











