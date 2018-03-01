/****************************************************************************
Задача 1_5.

Вывести квадраты натуральных чисел от 1 до n, используя только
O(n) операций сложения и вычитания (умножением пользоваться нельзя).
n ≤ 1000.

  in  | out
  ----| -------------
  5   | 1 4 9 16 25
****************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <time.h>
using namespace std ;

int kvadrat (int a,int b) {
    int kvadr=b;
    if (a>1) {
        kvadr=kvadrat (a-1,b)+b;
    }
    return kvadr;
}
int main () {
    
    int n;
    cin>>n;
    for (int i=1;i<=n;++i) {
    cout<<kvadrat(i,i)<<" ";
    }
    return 0;
    
}

