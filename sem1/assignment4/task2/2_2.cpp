#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class T {
public:
    int x1,x2;
    T() {};
    T(int x_,int x__) {
        x1=x_;
        x2=x__;
    }
};
bool operator < (T t1, T t2) {
    return t1.x2<=t2.x2;
}
istream &operator >> (istream &is,  T& t)
{
    return is >> t.x1 >> t.x2;
}


template <class t> //означает что наша функция может работать с пользовательскими типами данных
void insertion_sort (t* arr, size_t size) {
    int i,j;
    for (i = 1 ; i < size; ++i) {
        j = i-1;
        t tmp = arr[i];
        while (tmp < arr[j] && j>=0 ) {
            arr[j+1]=arr[j]; //сдвигаем элементы как бы расчищая место под тот, который двигаем
            j--;
        }
        arr[j+1]=tmp; //ставим элемент на место
    }
}

int main() {
    T arr[20];
    int ans(1);
    int count(-1);
    while (cin) {
        count++;
        cin >> arr[count];
    }
    insertion_sort(arr, count);
    int tmp=arr[0].x2;
    for (int i(1);i<count;++i) {
        if (arr[i].x1>=tmp) {
            ans++;
            tmp=arr[i].x2;
        }
    }
    cout << ans << endl;
    
}









