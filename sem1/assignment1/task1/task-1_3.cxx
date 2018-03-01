/****************************************************************************
Задача 1_3

Даны четыре неотрицательных числа a, b, c и d. Сложить две
рациональные дроби a/b и c/d, а их результат представить в виде
несократимой дроби m/n. Вывести числа m и n.
a, b, c, d ≤ 1000.

  in         | out
  -----------|-------
  3 10 5 18  | 26 45
****************************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std ;

int nod (int a1,int a2) {
    int p;
    p=1;
    while ((a1!=0) and (a2!=0)) {
        if (a1>a2) {
            a1=a1-a2;
        };
        if (a2>=a1) {
            a2=a2-a1;
        };
    }
    p=a1;
    return p;
}

int main ()

{
    int a,b,c,d;
    int m,n;
    int x;
    cin >>a>>b>>c>>d;
    m=(a*d+c*b);
    n=b*d;
    x=nod(m,n);
    m=m/x;
    n=n/x;
    cout <<m<<" "<<n<<'\n';
    return 0;
    
}




