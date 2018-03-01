/****************************************************************************
Дано число N &lt; 10^6 и последовательность пар целых чисел из [-2^31..2^31]
длиной N.

Построить декартово дерево из N узлов, характеризующихся парами чисел
{Xi, Yi}.

Каждая пара чисел {Xi, Yi} определяет ключ Xi и приоритет Yi в декартовом
дереве.

Добавление узла в декартово дерево выполняйте второй версией алгоритма,
рассказанного на лекции:

- При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим
приоритетом. Затем разбейте найденное поддерево по ключу x так, чтобы в
первом поддереве все ключи меньше x, а во втором больше или равны x.
Получившиеся два дерева сделайте дочерними для нового узла (x, y).
Новый узел вставьте на место узла P.

Построить также наивное дерево поиска по ключам Xi методом из задачи 2.
****************************************************************************/

/****************************************************************************

Задача 2_1 Вычислить разницу глубин наивного дерева поиска и декартового
дерева. Разница может быть отрицательна.

  in    | out
  ----- | ---
  10    |
  5 11  |
  18 8  |
  25 7  |
  50 12 |
  30 30 |
  15 15 |
  20 10 |
  22 5  |
  40 20 |
  45 9  | 2

  in    | out
  ----- | ---
  10    |
  38 19 |
  37 5  |
  47 15 |
  35 0  |
  12 3  |
  0 42  |
  31 37 |
  21 45 |
  30 26 |
  41 6  | 2

****************************************************************************/

//prod. yaishenka
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std ;

#define nptr nullptr

struct Node {
    int key;
    int pr;
    Node* L=nptr;
    Node* R=nptr;
    Node () {
        L=R=nptr;
    }
    Node (int k, int p) {
        key=k;
        pr=p;
    }
    Node (int x) {
        key=x;
    }
    void insert (int k, int p);
    int l_pr () {
        return (L == nptr ? numeric_limits<int>::lowest() : L->pr);
    }
    int r_pr () {
        return (R == nptr ? numeric_limits<int>::lowest() : R->pr);
    }
    void insert_keys(int x);
    
};

Node* Merge (Node* l, Node* r) {
    if (l==nptr || r==nptr) {
        return (l==nptr? r : l);
    }
    if (l->pr < r->pr ) {
        r->L = Merge (l,r->L);
        return r;
    } else {
        r->R = Merge(l, r->L);
        return r;
    }
}

typedef pair <Node*,Node*> pNN;


pNN Split (Node*t, int x) {
    if (t == nullptr)
    {
        return {nptr, nptr};
    } else if (x > t->key)
    {
        pNN tmp=Split(t->R,x);
        t->R=tmp.first;
        return {t,tmp.second};
    } else
    {
        pNN tmp=Split(t->L,x);
        t->L=tmp.second;
        return {tmp.first,t};
        
    }
}


void Node::insert(int k, int p)
{
    if (pr > p)
    {
        if (k<key)
        {
            if (L==nptr)
            {
                Node* tmp = new Node (k,p);
                L=tmp;
            } else
            {
                L->insert(k, p);
            }
        } else
        {
            if (R==nptr)
            {
                Node* tmp = new Node (k,p);
                R=tmp;
            } else
            {
                R->insert(k, p);
            }
        }
    } else
    {
        Node* tmp = new Node (key,pr);
        tmp->L=L;
        tmp->R=R;
        pNN tmp2 = Split(tmp, k);
        L=tmp2.first;
        R=tmp2.second;
        key=k;
        pr=p;
        return;
    }
}

void Node::insert_keys(int x)
{
    if (L != nptr && x < key)
        L->insert_keys(x);
    else if (L == nptr && x < key)
    {
        L = new Node(x);
    }
    else if (R != nptr && x >= key)
        R->insert_keys(x);
    else if (R == nptr && x >= key)
    {
        R = new Node(x);
    }
}

int find_depth(Node* t)
{
    int res1(0), res2(0);
    if (t->L != nptr)
        res1 = find_depth(t->L) + 1;
    if (t->R != nptr)
        res2 = find_depth(t->R) + 1;
    return max(res1, res2);
}

int main()
{
    int n;
    cin >> n;
    int a, b;
    cin >> a >> b;
    Node* root = new Node(a, b);
    Node* naive = new Node(a);
    --n;
    while (n--)
    {
        cin >> a >> b;
        root->insert(a, b);
        naive->insert_keys(a);
    }
    a = find_depth(naive);
    b = find_depth(root);
    cout << find_depth(naive) - find_depth(root) << endl;
    return 0;
}











