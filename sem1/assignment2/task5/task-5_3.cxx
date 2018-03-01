/****************************************************************************

Задача 5_3. Binary MSD для long long.

Дан массив неотрицательных целых 64-разрядных чисел. Количество чисел не
больше 10^6. Отсортировать массив методом MSD по битам (бинарный QuickSort).

in          | out
----------- | ---
3           | 4 7 1000000
4 1000000 7 |

****************************************************************************/

//Created by Yaishenka
//Copyright © 2017 Yaishenka. All rights reserved.
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std ;
long long numbit (long long n) {
    int ans=0;
    while (n>0) {
        ans+=1;
        n/=2;
    }
    return ans;
}
long long bit (long long n,int t) {
    long long ans=n;
    int sdvig=t-1;
    ans>>= sdvig;
    return ans&1;
}

void MSD (long long* arr,int right,int t) {
    if (right==0 || right==1 || t<1) {
        return;
    }
    int c[2];
    long long b [right];
    for (int i(0);i<2;++i) {
        c[i]=0;
    }
    for (int i(0);i<right;++i) {
        c[bit(arr[i],t)]+=1;
    }
    int sum=0;
    c[1]=c[0];
    c[0]=0;
    for (int i(0);i<right;++i) {
        b[c[bit(arr[i],t)]]=arr[i];
        c[bit(arr[i],t)]+=1;
    }
    for (int i(0);i<right;++i) {
        arr[i]=b[i];
    }
    int left(0);
    for (int i(0);i<2;++i) {
        MSD (arr+left,c[i]-left,t-1);
        left=c[i];
    }
}
int main () {
    int n;
    cin>>n;
    long long  arr[n];
    long long max(0);
    for (int i(0);i<n;++i) {
        cin>>arr[i];
        max=arr[i]>max? arr[i]:max;
    }
    MSD(arr, n, numbit(max));
    for (int i(0);i<n;++i) {
        cout<<arr[i]<<" ";
    }
    
    
}


