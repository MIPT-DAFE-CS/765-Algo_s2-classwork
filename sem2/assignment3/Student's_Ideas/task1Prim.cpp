//yaishenka prod.
#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <set>

class Edge {
public:
    int v1, v2, weight;
    Edge () {}
    Edge (int v_1, int  v_2, int w) {
        v1 = v_1;
        v2 = v_2;
        weight = w;
    }
};

bool operator < (const Edge& e1, const Edge& e2) {return e1.weight < e2.weight;}
bool operator > (const Edge& e1, const Edge& e2) {return e1.weight > e2.weight;}
bool operator != (const Edge& e1, const Edge& e2) {return e1.weight != e2.weight;}
bool operator == (const Edge& e1, const Edge& e2) {return !operator!=(e1, e2);}

int Prim (std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge> > pq, int n) {
    std::vector<bool> visited (n, false);
    Edge current;
    current = pq.top();
    pq.pop();
    int weight = current.weight;
    visited[current.v1] = true;
    visited[current.v2] = true;
    while (!pq.empty()) {
        current = pq.top();
        pq.pop();
        if ( (visited[current.v1] && !visited[current.v2]) | (!visited[current.v1] && visited[current.v2]) ) {
            weight += current.weight;
            visited[current.v1] = true;
            visited[current.v2] = true;
        }
    }
    return weight;
}

int main () {
    int n, m;
    int v1, v2, w;
    std::cin >> n >> m;
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge> > pq;
    for (int i(0); i<m; ++i) {
        std::cin >> v1 >> v2 >> w;
        Edge e (v1, v2 ,w);
        pq.push (e);
    }
    std::cout << Prim(pq, n) << std::endl;
}
/*
 4 4
 1 2 1
 2 3 2
 3 4 5
 4 1 4
*/
