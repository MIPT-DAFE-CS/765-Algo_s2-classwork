//
// Решение предполагает использование кучи.
//

/****************************************************************************
Задача 6_1. Жадина.

Вовочка ест фрукты из бабушкиной корзины. В корзине лежат фрукты разной
массы. Вовочка может поднять не более K грамм. Каждый фрукт весит не
более K грамм. За раз он выбирает несколько самых тяжелых фруктов,
которые может поднять одновременно, откусывает от каждого половину и
кладет огрызки обратно в корзину. Если фрукт весит нечетное число грамм,
он откусывает большую половину. Фрукт массы 1гр он съедает полностью.
Определить за сколько подходов Вовочка съест все фрукты в корзине.

*Формат входных данных.* Вначале вводится n - количество фруктов и n
строк с массами фруктов. n ≤ 50000. Затем K - "грузоподъемность". K ≤ 1000.

*Формат выходных данных.* Неотрицательное число - количество подходов к
корзине.

  in             | out
  ---------------|-----
  3              | 4
  1 2 2          | 
  2              | 

  in             | out
  ---------------|-----
  3              | 5
  4 3 5          | 
  6              | 

  in             | out
  ---------------|-----
  7              | 3
  1 1 1 1 1 1 1  | 
  3              | 

****************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std ;
struct Heap {
private:
    int* buffer;
    int size;
public:
    Heap (int* arr,int size_) {
        buffer=new int [size_+1];
        size=size_;
        for (int i(1);i<=size;++i) {
            buffer[i]=arr[i-1];
        }
        for (int i=size;i>=1;--i) {
            if (has_left(i)) down(i);
        }
    }
    
    int give_size (){
        return size;
    }
    bool has_left (int index) {
        return index*2<=size;
    }
    bool has_right (int index) {
        return index*2 +1<=size;
    }
    int left (int index) {
        return index*2;
    }
    int right (int index) {
        return index*2 +1;
    }
    int parent (int index) {
        return index/2;
    }
    void down (int index) {
        if (has_left(index) && has_right(index)){
            int max=(buffer[left(index)]>buffer[right(index)])? left(index) : right(index);
            if (buffer[index]<buffer[max]) {
                int tmp=buffer[index];
                buffer[index]=buffer[max];
                buffer[max]=tmp;
                down(max);
            }
        }
        if (has_left(index)) {
            if (buffer[index]<buffer[left(index)]) {
                int tmp=buffer[index];
                buffer[index]=buffer[left(index)];
                buffer[left(index)]=tmp;
                down(left(index));
            }
        }
    }
    void up (int index) {
        if (index >1 && buffer[index]>buffer[parent(index)]){
            int tmp=buffer[parent(index)];
            buffer[parent(index)]=buffer[index];
            buffer[index]=tmp;
            up(parent(index));
        }
    }
    int get_max (){
        return buffer[1];
    }
    void pop_max () {
        int tmp=buffer[1];
        buffer[1]=buffer[size];
        buffer[size]=tmp;
        size--;
        down(1);
    }
    void push_half (int number) {
        ++size;
        buffer[size]=number/2;
        up(size);
    }
    void debag () {
        cout<<"\n"<<"****************"<<"\n";
        for (int i=1;i<=size;++i){
            cout<<buffer[i]<<" ";
        }
        cout<<"\n"<<"****************"<<"\n";
    }
};
int main () {
    int ans(0),curw,cur,n,k,arr[50001],curtake[50001];
    cin>>n;
    for (int i(0);i<n;++i) {
        cin>>arr[i];
    }
    cin>>k;
    Heap heap(arr,n);
    
    while (heap.give_size()>0) {
        curw=0;
        cur=0;
        //heap.debag();
        while (heap.give_size()>0 && curw+heap.get_max()<=k) {
            curw+=heap.get_max();
            if (heap.get_max()>1) {
                curtake[cur]=heap.get_max();
                cur++;
            }
            heap.pop_max();
        }
        for (int i(0);i<cur;++i) {
            heap.push_half(curtake[i]);
        }
        //heap.debag();
        ans++;
    }
    cout<<ans;
    
}

















