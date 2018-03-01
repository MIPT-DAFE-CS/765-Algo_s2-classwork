//
// Решение предполагает использование кучи.
//

/****************************************************************************
Задача 6_3. Тупики.

На вокзале есть некоторое количество тупиков, куда прибывают
электрички. Этот вокзал является их конечной станцией. Дано расписание
движения электричек, в котором для каждой электрички указано время ее
прибытия, а также время отправления в следующий рейс. Электрички в
расписании упорядочены по времени прибытия. Когда электричка прибывает,
ее ставят в свободный тупик с минимальным номером. При этом если
электричка из какого-то тупика отправилась в момент времени X, то
электричку, которая прибывает в момент времени X, в этот тупик ставить
нельзя, а электричку, прибывающую в момент X+1 — можно.

В данный момент на вокзале достаточное количество тупиков для работы по
расписанию.

Напишите программу, которая по данному расписанию определяет, какое
минимальное количество тупиков требуется для работы вокзала.

*Формат входных данных.* Вначале вводится n - количество электричек в
расписании. Затем вводится n строк для каждой электрички, в строке -
время прибытия и время отправления. Время - натуральное число от 0 до
10\^9. Строки в расписании упорядочены по времени прибытия.

*Формат выходных данных.* Натуральное число - минимальное количеством
тупиков.

*Максимальное* время: 50мс, память: 5Мб.

  in     | out
  -------|-----
  1      | 1
  10 20  | 

  in     | out
  -------|-----
  2      | 2
  10 20  | 
  20 25  | 

  in     | out
  -------|-----
  3      | 2
  10 20  | 
  20 25  | 
  21 30  | 

****************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std ;
struct Pair {
    int num,t;
    Pair () {
        t=0;
        num=t=0;
    }
    void set (int number,int tim) {
        t=tim;
        num=number;
    }
    
    
    void out () {
        cout<<"num: "<<num<<" time: "<<t;
    }
};

struct HeapTime {
private:
    int size;
    Pair buffer [100];
public:
    HeapTime () {
        size=0;
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
            int min=(buffer[left(index)].t<buffer[right(index)].t)? left(index) : right(index);
            if (buffer[index].t>buffer[min].t) {
                Pair tmp=buffer[index];
                buffer[index]=buffer[min];
                buffer[min]=tmp;
                down(min);
            }
        }
        if (has_left(index)) {
            if (buffer[index].t>buffer[left(index)].t) {
                Pair tmp=buffer[index];
                buffer[index]=buffer[left(index)];
                buffer[left(index)]=tmp;
                down(left(index));
            }
        }
    }
    void up (int index) {
        if (index >1 && buffer[index].t<buffer[parent(index)].t){
            Pair tmp=buffer[parent(index)];
            buffer[parent(index)]=buffer[index];
            buffer[index]=tmp;
            up(parent(index));
        }
    }
    Pair get_min (){
        return buffer[1];
    }
    void pop_min () {
        Pair tmp=buffer[1];
        buffer[1]=buffer[size];
        buffer[size]=tmp;
        size--;
        down(1);
    }
    void push (Pair number) {
        ++size;
        buffer[size]=number;
        up(size);
    }
    void debagger () {
        cout<<"\n"<<"*****************"<<"\n";
        for (int i(1);i<=size;++i) {
            cout<<" pos: "<<i<<" : ";
            buffer[i].out();
        }
        cout<<"\n"<<"*****************"<<"\n";
    }
};

struct HeapNum {
private:
    int size;
    Pair buffer [100];
public:
    HeapNum () {
        size=0;
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
            int min=(buffer[left(index)].num<buffer[right(index)].num)? left(index) : right(index);
            if (buffer[index].num>buffer[min].num) {
                Pair tmp=buffer[index];
                buffer[index]=buffer[min];
                buffer[min]=tmp;
                down(min);
            }
        }
        if (has_left(index)) {
            if (buffer[index].num>buffer[left(index)].num) {
                Pair tmp=buffer[index];
                buffer[index]=buffer[left(index)];
                buffer[left(index)]=tmp;
                down(left(index));
            }
        }
    }
    void up (int index) {
        if (index >1 && buffer[index].num<buffer[parent(index)].num){
            Pair tmp=buffer[parent(index)];
            buffer[parent(index)]=buffer[index];
            buffer[index]=tmp;
            up(parent(index));
        }
    }
    Pair get_min (){
        return buffer[1];
    }
    void pop_min () {
        Pair tmp=buffer[1];
        buffer[1]=buffer[size];
        buffer[size]=tmp;
        size--;
        down(1);
    }
    void push (Pair number) {
        ++size;
        buffer[size]=number;
        up(size);
    }
    void debagger () {
        cout<<"\n"<<"*****************"<<"\n";
        for (int i(1);i<=size;++i) {
            cout<<" pos: "<<i<<" : ";
            buffer[i].out();
        }
        cout<<"\n"<<"*****************"<<"\n";
    }
};


int main () {
    int n,arrive,away,count(1);
    cin>>n;
    cin>>arrive>>away;
    Pair pair;
    pair.set(count, away);
    HeapTime busy;
    HeapTime free;
    busy.push(pair);
    for (int i(1);i<n;++i) {
        cin>>arrive>>away;
        pair.set(count, away);
        while (busy.get_min().t<arrive) {
            free.push(busy.get_min());
            busy.pop_min();
        }
        if (free.give_size()!=0) {
            free.get_min().set(free.get_min().num, away);
            busy.push(free.get_min());
            free.pop_min();
        } else {
            count++;
            Pair tmp;
            tmp.set(count, away);
            busy.push(tmp);
        }
    }
    cout<<count;
}











