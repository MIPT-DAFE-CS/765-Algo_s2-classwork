//yaishenka prod.
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

struct IGraph { //пояснение графа смотри в ass1/task2
    virtual ~IGraph() {}
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual void GetNext(int vertex, std::vector<int>& vertices) const = 0;
    virtual void GetPrev(int vertex, std::vector<int>& vertices) const = 0;
};

class CListGraph : public IGraph {
private:
    vector < vector <int> > graph;
    int* color;
    int n;
public:
    CListGraph (int N) : graph(N), n(N) {}

    CListGraph (const IGraph* Graph) : graph(Graph->VerticesCount()), n(Graph->VerticesCount()) {
        for (int i(0); i < n; ++i)
            Graph->GetNext(i, graph[i]);
    }

    int VerticesCount() const {
        return n;
    }

    void AddEdge(int from, int to) {
        if (from >= n || to >= n || from < 0 || to < 0)
            return;
        graph[from].push_back(to);
        graph[to].push_back(from); //если неориентированный
    }

    void GetNext(int vertex, std::vector<int>& vertices) const {
        if (vertex >= n || vertex < 0)
            return;
        vertices = graph[vertex];
    }

    void GetPrev(int vertex, std::vector<int>& vertices) const {
        if (vertex >= n || vertex < 0)
            return;
        for(int j(0); j < n; ++j) {
            for(auto i : graph[j]) {
                if (i == vertex)
                    vertices.push_back(j);
            }
        }
    }
    void debAg () const {
        for (int i(0); i<n; ++i) {
            cout << i << ": ";
            for (auto g : graph[i] ) {
                cout << g << " ";
            }
            cout << endl;
        }
    }
    int bfs (int from, int to);

};

int CListGraph:: bfs (int from, int to) {
	queue<int> myqueue; //очередь
	int distanse [VerticesCount()]; //расстояние от вершины from до остальных
	int par[VerticesCount()]; //родители 
	int path [VerticesCount()]; //количество путей
	for (int i(0); i<n; ++i){
		distanse[i] = 0;
		path[i] = 0;
	}
    path[from] = 1; //путей из самой себя в саму себя 1
	myqueue.push(from); //пушим в очередь
	while (!myqueue.empty()) { //пока очередь не пустая 
		int u=myqueue.front(); //первый элемент в очереди - текущий
		myqueue.pop(); //выкидываем его из очереди
		for (int a : graph[u]) { //пробегаем итератором а по всем детям вершины u
			if (!path[a]) {//если путей в а было 0
				path[a]=path[u]; //путей в а столько же сколько в ее родителя 
				par[a]=u; //родитель а - текущая
				distanse[a]=distanse[u]+1; //расстояние = родительское + 1
				myqueue.push(a); //нужно проверить детей а пушим ее в очередб
			} else if (distanse[a]==distanse[u]+1) { //если в вершине уже были и расстояние до нее больше чем расстояние до ее родителя "она ниже"
				path[a]+=path[u]; //путей в нее = путей в нее + путей в ее родителя
			}
		}
	}
	return path[to]; //верни кол-во путей до искомой вершины
}

int main () {
    int n, m, a, b;
    cin >> n >> m;
    CListGraph G(n);
    for (int i(0); i < m; ++i)
    {
        cin >> a >> b;
        G.AddEdge(a, b);
    }
    int to,from;
    cin >> from >> to;
    cout << G.bfs(from, to) << endl;
}



