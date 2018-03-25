/*input
10
*/

/****************************************************************************
Задача 1_1

Найти, на сколько нулей оканчивается n! = 1 * 2 * 3 * … * n.
n <= 1000.

  in  | out
  ----|-----
  25  | 6
****************************************************************************/



#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std ;
int kolvo5 (int a) {
    int b=0;
    while ((a>=5) and (a%5==0)) {
            a/=5;
            b+=1;
    };
    return b;
}
int main ()

{
    int n=0;
    int ans=0;
    cin >> n;
    for (int i(1);i<=n;++i) {
        ans+=kolvo5(i);
    }
    cout<<ans<<'\n';
    return 0;
    
}

