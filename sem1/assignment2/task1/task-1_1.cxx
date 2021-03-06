/****************************************************************************
Во всех вариантах данной задачи необходимо реализовать
и использовать **сортировку вставками**.
****************************************************************************/

/****************************************************************************
Задача 1_1. Ящики.

На склад привезли много пустых ящиков. Все ящики пронумерованы по порядку
поступления от 0. Известно, что их все можно сложить один в один (то есть так,
что каждый следующий помещается в предыдущий). Один ящик можно вложить в другой,
если его можно перевернуть так, что размеры одного ящика по всем осям станут
строго меньше размеров другого ящика по соответствующим осям. Требуется
определить, в какой последовательности они будут вложены друг в друга.
Вывести номера ящиков.

in      | out
------- | ---
3       | 1 0 2
2 3 5   |
1 1 1   |
10 4 10 |

****************************************************************************/

//Created by Yaishenka
//Copyright © 2017 Yaishenka. All rights reserved.
#include <iostream>

using namespace std;

struct conteiner {
    int number,s1,s2,s3;
    conteiner() {
        number=s1=s2=s3=0;
    }
    void ps (int n, int x1, int x2, int x3) {
        number=n;
        s1=x1;
        s2=x2;
        s3=x3;
    }
    int maxs () {
        int ans=(s1>s2)? s1:s2;
        ans=(ans>s3)? ans :s3;
        return ans;
    }
    
};
int main () {
    int n,x1,x2,x3,count(0);
    cin>>n;
    conteiner ans[n];
    cin>>x1>>x2>>x3;
    ans[0].ps(count, x1, x2, x3);
    count+=1;
    for (int i(1);i<n;++i) {
        cin>>x1>>x2>>x3;
        ans[i].ps(count, x1, x2, x3);
        conteiner tmp=ans[i];
        int j=i-1;
        for (;j>=0 && tmp.maxs()<ans[j].maxs();--j) {
            ans[j+1]=ans[j];
        }
        ans[j+1]=tmp;
        count+=1;
    }
    for (int i(0);i<n;++i) {
        cout<<ans[i].number<<" ";
    }
    
}





