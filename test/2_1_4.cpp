#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main () {
    int n;
    cin>>n;
    string arr [n];
    cin>>arr[0];
    for (int i(1);i<n;++i) {
        cin>>arr[i];
        string tmp=arr[i];
        int j=i-1;
        while ((tmp<arr[j]) && (j>=0)) {
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=tmp;
    }
    for (int i(0);i<n;++i) {
        cout<<arr[i]<<endl;
    }
}
//4 caba abba ab aba