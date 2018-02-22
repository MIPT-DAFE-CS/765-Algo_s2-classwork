

#include <iostream>
#include <cmath>
using namespace std;
long long byte (long long n,int t) {
    long long ans=n;
    for (int i=0;i<t-1;++i) {
        ans>>= 8;
    }
    return ans&255;
}
void LSD (long long* arr,int n) {
    int c[256];
    long long  b [n];
    for (int t=1;t<=8;++t) {
        for (int i(0);i<256;++i) {
            c[i]=0;
        }
        for (int i(0);i<n;++i) {
            c[byte(arr[i], t)]+=1;
        }
        int sum=0;
        for (int i(0);i<256;++i) {
            int tmp = c[i];
            c[i] = sum;
            sum += tmp;
        }
        for (int i(0);i<n;++i) {
            b[c[byte(arr[i], t)]]=arr[i];
            c[byte(arr[i], t)]+=1;
        }
        for (int i(0);i<n;++i) {
            arr[i]=b[i];
        }
    }
}




int main() {
    int n;
    cin >> n;
    
    long long arr[n], max = 0;
    
    for (int i = 0; i < n; i++) {
        long long tmp;
        cin >> tmp;
        arr[i] = tmp;
        arr[i] > max ? max = arr[i] : max;
    }
    
    //Вычисляем максимальную длину
    long long cnt = 0;
    while(max){
        max/=256;
        cnt++;
    }
    LSD(arr, n);
    for (int i = 0; i < n; i++) {
        cout << arr[i]<< " ";
    }
    cout<<endl;
    
}

