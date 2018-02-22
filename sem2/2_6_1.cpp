#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std ;
struct params {
    int* arr;
    int n;
};

struct stack {
    int count=0;
    int end=0;
    params buffer [10000000];
    void push(params param) {
        buffer[end]=param;
        count+=1;
        end+=1;
    }
    params pop () {
        params tmp;
        tmp.n=-2;
        if (count ==0 ) {
            return tmp;
        } else {
            end-=1;
            count-=1;
            return buffer[end];
        }
    }
    
};
stack stack;

inline int Partition (int* arr,int n) {
    if (n<=1) {
        return 0;
    }
    if (n==2) {
        if (arr[0]>arr[1]) {
            swap (arr[0],arr[1]);
        }
        return 1;
    }
    int bas=n/2;
    swap(arr[n-1], arr[bas]);
    int i(0),j(0);
    while (j<n-1) {
        if (arr[j]>arr[n-1]) {
            j+=1;
        } else {
            swap (arr[i],arr[j]);
            i+=1;
            j+=1;
        }
    }
    swap (arr[i],arr[n-1]);
    
    
    return i;
}
inline void quicksort (int*arr,int n) {
    if (n<=1) {
        return;
    }
    int i=Partition(arr,n);
    params param1;
    param1.arr=arr;
    param1.n=i;
    stack.push(param1);
    param1.arr=arr+i;
    param1.n=n-i;
    stack.push(param1);
    while (stack.count>0) {
        param1=stack.pop();
        if (param1.n<=1) {
            continue;
        } else {
            i=Partition(param1.arr, param1.n);
            params param2;
            param2.arr=param1.arr+i;
            param2.n=param1.n-i;
            param1.n=i;
            stack.push(param1);
            stack.push(param2);
            
        }
    }
    
    
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int arr[100000000];
    int count=-1;
    while (cin) {
        count+=1;
        cin>>arr[count];
    }
    //cout<<Partition(arr, count)<<endl;
    quicksort(arr, count);
    for (int i(9);i<count;i+=10) {
        cout<<arr[i]<<" ";
    }
    return 0;
}









