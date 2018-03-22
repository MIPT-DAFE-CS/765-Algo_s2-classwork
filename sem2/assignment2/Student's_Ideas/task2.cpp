//yaishenka prod.

/*
идея: если инвертироваь исходный граф и делить а не умножать, то наличие отрицательного цикла будет говорить о положительном цикле в исходном графе"
*/
#include <iostream>
#include <queue>
#include <vector>
#include <limits>

using namespace std;

struct edge
{
    int a,b;
    double weight;
    edge (int a1, int b1, double w) {
        a=a1;
        b=b1;
        weight=w;
    }
    edge () {};
};


const double INF = 1000000;

bool Bellman_Ford (std::vector<edge>& g,int n, int from) { //вернет true если есть цикл
    vector<double> d (n, INF); //вектор расстояний (в нашем случае произведений)
    d[from]=1; 
    bool swg=true; //нужно ли продолжать алгоритм
    int it(0);
    while (swg) {
        swg=false; //если на этой итерации мы ничего не поменяли, то проверять еще раз не нужно
        it++;
        if (it>n) { //по определению если мы вышли за n-1 итераций то это отрицательный цикл, но в этой реализации ребра идут не по возрастанию индекса вершин, поэтому требуется лишняя итерация (методом тыка)
            return true;
        }
        for (auto current : g) {
            if (d[current.a]<INF){ //если уже знаем расстояние до нашей вершины
                if (d[current.a]/current.weight<d[current.b]) { //если новое меньше то меняем его
                    d[current.b]=d[current.a]/current.weight;
                    swg=true; //мы что-то поменяли в векторе нужно пройтись еще раз
                }
            }
        }
    }
    return false; //цикл не найден
}

void arb (std::vector<edge>& g,int n) {
    bool swg=true; //нашелся ли уже цикл
    int i=0;
    while (swg && i<=n-1) { //для всех вершин
        swg=!Bellman_Ford(g, n, i); // swg - true значит цикл НЕ нашелся, false - нашелся
        i++;
    }
    if (!swg) cout << "YES"; else cout << "NO";
}

int main () {
    int a,b,n,m;
    double w;
    cin >> n;
    m=n*n-n;
    vector<edge> graph;
    for (int i(0);i<n;++i) {
        for (int j(0);j<n;j++){
            if (i!=j) {
                cin >> w;
                if (w>-1) {
                    graph.push_back(edge(j,i,w)); //инвертируем граф и делим вместо умножения
                }
            }
        }
    }
    arb(graph,n);
}
