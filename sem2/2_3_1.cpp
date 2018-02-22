#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std ;

int Partition (int* arr,int n) {
    int bas=n-1;
    swap(arr[n/2], arr[bas]);
    int i(0),j(0);
    while (j<n-1) {
        if (arr[j]>arr[bas]) {
            j+=1;
        } else {
            swap (arr[i],arr[j]);
            i+=1;
            j+=1;
        }
    }
    swap (arr[i],arr[bas]);
    return i;
}
int ordstat (int*arr,int n,int k) {
    int left(0),right=n;
    while (true) {
        int j=Partition(arr+left, right-left);
        j+=left;
        //cout<<"j: "<<j<<" left "<<left<<" right "<<right<<endl;
        //for (int i(0);i<n;++i) {
        //    cout<<arr[i]<<" ";
        //}
        //cout<<endl;
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
    cout<<ordstat(arr, n, k);
return 0;
}








