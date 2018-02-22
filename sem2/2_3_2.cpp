#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std ;
int Partition (int* arr,int n) {
    int bas=0;
    swap(arr[n/2], arr[bas]);
    int i(n-1),j(n-1);
    while (j>0) {
        if (arr[j]<arr[bas]) {
            j-=1;
        } else {
            swap (arr[i],arr[j]);
            i-=1;
            j-=1;
        }
    }
    swap (arr[i],arr[bas]);
    //for (int i(0);i<n;++i) {
    //    cout<<arr[i]<<" ";
    //}
    //cout<<endl;
    return i;
}
int ordstat (int*arr,int n,int k) {
    int left(0),right=n;
    while (true) {
        int j=Partition(arr+left, right-left);
        j+=left;
        if (k<j) {
            right=j;
        } else if (k>j) {
            left=j+1;
            
        } else {
            return arr[k];
        }
    }
}
int main () {
    int n,k;
    cin>>n>>k;
    int arr[n];
    for (int i(0);i<n;++i) {
        cin>>arr[i];
    }
    //Partition(arr, n);
    cout<<ordstat(arr, n, k);
    return 0;
}








