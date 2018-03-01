/****************************************************************************
Во всех вариантах данной задачи необходимо реализовать
и использовать **сортировку вставками**.
****************************************************************************/

/****************************************************************************
Задача 1_3. Ломаная 2.

Аналогично 1.2, но ломаная должна быть замкнутая. Предполагается, что никакие
три точки не лежат на одной прямой.

Указание: стройте ломаную от точки, имеющей наименьшую координату x. Если таких
точек несколько, то используйте точку с наименьшей координатой y.

Точки на ломаной расположите в порядке убывания углов лучей от начальной точки
до всех остальных точек.

in  | out
--- | ---
4   | 0 0
0 0 | 0 1
1 1 | 1 1
1 0 | 1 0
0 1 |

****************************************************************************/
//Created by Yaishenka
//Copyright © 2017 Yaishenka. All rights reserved.
#include <iostream>
#include <cmath>
using namespace std;
struct dot {
    int x,y;
    double cos;
    double calc (dot bas, dot nul) {
        cos=((long double)(x-nul.x)*bas.x+(y-nul.y)*bas.y)/sqrt((x-nul.x)*(x-nul.x)+(y-nul.y)*(y-nul.y));
        return cos;
    }
};

int main () {
    int n,x,y,j;
    cin>>n;
    dot arr[n];
    cin>>arr[0].x>>arr[0].y;
    
    
    for (int i(1);i<n;++i) {
        cin>>x>>y;
        arr[i].x=x;
        arr[i].y=y;
        dot tmp=arr[i];
        int j=i-1;
        while (( (tmp.x<arr[j].x) || ( (tmp.x==arr[j].x) && (tmp.y<arr[j].y) )) && (j>=0)) {
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=tmp;
    }
    //dot bas=basis(arr, n);
    dot bas;
    bas.x=0;
    bas.y= -10;
    for (int i(2);i<n;++i) {
        j=i-1;
        dot tmp=arr[i];
        while ( tmp.calc(bas,arr[0])<arr[j].calc(bas,arr[0]) && j>=0) {
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=tmp;
    }
    for (int i(0);i<n;++i) {
        cout<<arr[i].x<<" "<<arr[i].y<<endl;
    }
    
    
    /*
     9
     0 2
     0 3
     1 5
     2 5
     3 4
     1 1
     5 3
     4 1
     4 0
     */
    
}

