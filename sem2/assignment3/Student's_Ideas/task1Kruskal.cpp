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

class DSU {
private:
    std::vector<int> parent;
    std::vector<int> size;
public:
    DSU (int n) {
        parent.resize(n);
        size.resize(n);
        for (int i(0); i<n; ++i)
            make_set(i);
    }
    void make_set (int v) {
        parent[v] = v;
        size[v] = 1;
    }
    int find_set (int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }
    void union_sets (int a, int b) {
        a = find_set (a);
        b = find_set (b);
        if (a != b) {
            if (size[a] < size[b])
                std::swap (a,b);
            parent[b] = a;
            size[a] += size[b];
        }
    }
};

int Kruskal (std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge> > pq, int n) {
    DSU dsu(n+1);
    Edge current;
    current = pq.top();
    pq.pop();
    int weight = current.weight;
    dsu.union_sets(current.v1, current.v2);
    while (!pq.empty()) {
        current = pq.top();
        pq.pop();
        if (dsu.find_set(current.v1) != dsu.find_set(current.v2)) {
            dsu.union_sets(current.v1, current.v2);
            weight += current.weight;
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
    std::cout << Kruskal(pq, n) << std::endl;
}
/*
 4 4
 1 2 1
 2 3 2
 3 4 5
 4 1 4
 */
