#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std ;
char check (string text,int t) {
    if (t>=text.size()) {
        return 0;
    } else return text[t];
}
void MSD (string* arr,int right,int t, long long int maxlen) {
    if (right==0 || right==1 || t>maxlen) {
        return;
    }
    int c[256];
    int cc [256];
    string b [right];
    for (int i(0);i<256;++i) {
        c[i]=0;
    }
    for (int i(0);i<right;++i) {
         c[check(arr[i],t)]+=1;
    }
    int sum=0;
    for (int i(0);i<256;++i) {
        cc[i]=c[i];
        int tmp = c[i];
        c[i] = sum;
        sum += tmp;
    }
    for (int i(0);i<right;++i) {
        b[c[check(arr[i],t)]]=arr[i];
        c[check(arr[i],t)]+=1;
    }
    for (int i(0);i<right;++i) {
        arr[i]=b[i];
    }
    int left(0);
    for (int i(0);i<256;++i) {
        MSD (arr+left,c[i]-left,t+1,maxlen);
        left=c[i];
    }
}
int main () {
    string arr[100001];
    long long int maxlen=0;
    int count=-1;
    while (cin) {
        count+=1;
        cin>>arr[count];
        if (arr[count].size()>maxlen) {
            maxlen=arr[count].size();
        }
    }
    MSD(arr, count, 0,maxlen);
    for (int i(0);i<count;++i) {
        cout<<arr[i]<<endl;
    }
    
    
}