#include <iostream>
using namespace std ;
struct params {
    int* arr;
    int n;
};
inline void print (int a) {
    char s[10];
    int n=0;
    while (a>0 || n==0) {
        s[n]='0'+a%10;
        a/=10;
        n++;
    }
    for (int i=n-1;i>=0;--i) {
        putchar_unlocked(s[i]);
    }
    putchar_unlocked(' ');
}

struct stack {
    int count=0;
    int end=0;
    params buffer [50];
    inline void push(params param) {
        buffer[end]=param;
        count+=1;
        end+=1;
    }
    inline params pop () {
        end-=1;
        count-=1;
        return buffer[end];
    }
};
void vstavochki (int* arr,int n) {
    if (n==2) {
        if (arr[0]>arr[1]) {
            swap (arr[0],arr[1]);
        }
    }
    for (int i(1);i<n;++i) {
        int tmp=arr[i];
        int j=i-1;
        while (tmp<arr[j]  && (j>=0)) {
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=tmp;
    }
}
stack stack;
inline int Partition (int* arr,int n) {
    int a(arr[0]), b(arr[n / 2]), c(arr[n - 1]), base;
    if ((a <= b && b <= c) || (c <= b && b <= a)) base = n / 2;
    else if ((a <= c && c <= b) || (b <= c && c <= a)) base = n - 1;
    else base = 0;
    swap(arr[n-1], arr[base]);
    base=arr[n-1];
    int i(0),j(0);
    while (j<n-1) {
        if (arr[j]>base) {
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
void quicksort (int*arr,int n) {
    if (n<=1) {
        return;
    }
    if (n<=16) {
        vstavochki(arr, n);
        return;
    }
    int i=Partition(arr,n);
    quicksort(arr+i, n-i);
    quicksort(arr, i);
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int arr[25000000];
    int count=-1;
    char k = '1';
    int num;
    while (k!=EOF) {
        k=getchar_unlocked();
        num=0;
        while (k>='0' && k<='9') {
            num=num*10+k-'0';
            k=getchar_unlocked();
        }
        count+=1;
        arr[count]=num;
    }
    quicksort(arr, count);
    for (int i(9);i<count;i+=10) {
        print(arr[i]);
    }
    return 0;
}





















