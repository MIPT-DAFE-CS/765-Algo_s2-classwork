#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include  <stdint.h>
using namespace std;

void Merge (int* arr1,int* arr2,int n1,int n2,int* ans,int64_t* cnt) {
    int i(0),j(0);
    while (i<n1 && j<n2) {
        if (arr1[i]<=arr2[j]){
            ans[i+j]=arr1[i];
            ++i;
        } else {
            ans[i+j]=arr2[j];
            if (arr1[i]!=arr2[j])
                *cnt+=n1-i;
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
void MergeSort (int* arr,int n,int64_t* cnt){
    if (n<=1) {
        return;
    }
    int leftl,rightl;
    leftl=n/2;
    rightl=n-leftl;
    MergeSort(arr, leftl,cnt);
    MergeSort(arr+leftl,rightl,cnt);
    int* ans=new int[n];
    Merge (arr,arr+leftl,leftl,rightl,ans,cnt);
    for (int i(0);i<n;++i) {
        arr[i]=ans[i];
    }
    //memcpy( arr, ans, sizeof( int ) * n );
    delete[] ans;
}
int main () {
    int arr[1000000];
    int64_t cnt(0);
    int count(-1);
    while (cin) {
        count+=1;
        cin>>arr[count];
    }
    MergeSort(arr, count,&cnt);
    cout<<cnt;
}










