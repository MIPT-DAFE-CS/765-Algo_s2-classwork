/****************************************************************************
Дано число N &lt; 10^6 и последовательность целых чисел из [-2^31..2^31]
длиной N. Требуется построить бинарное дерево, заданное наивным порядком
вставки. Т.е., при добавлении очередного числа K в дерево с корнем root, если
root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое
поддерево root.
****************************************************************************/

/****************************************************************************

Задача 1_1 Выведите элементы в порядке in-order (слева направо).

  in    | out
  ----- | ---
  3     |
  2 1 3 | 1 2 3

  in    | out
  ----- | ---
  3     |
  1 2 3 | 1 2 3

  in    | out
  ----- | ---
  3     |
  3 1 2 | 1 2 3

****************************************************************************/


#include <iostream>
#include <algorithm>
using namespace std ;
struct Node {
    int key;
    Node* left=nullptr;
    Node* right=nullptr;
    Node (int k) {
        key=k;
    }
    void insert (int k) {
        if (k>=key) {
            if (right==nullptr) {
                right= new Node(k);
            } else right->insert(k);
        } else {
            if (left==nullptr) {
                left= new Node(k);
            } else left->insert(k);
        }
    }
    void debAg (){
        if (left!=nullptr) left->debAg();
        cout<<key<<" ";
        if (right!=nullptr) right->debAg();
    }
};
int main () {
    int n, a;
    cin>>n;
    cin>>a;
    Node root(a);
    for (int i(1);i<n;++i) {
        cin>>a;
        root.insert(a);
    }
    root.debAg();
}
















