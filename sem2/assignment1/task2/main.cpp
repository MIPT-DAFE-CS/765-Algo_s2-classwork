#include <iostream>
#include <vector>
#include <queue>


struct IGraph {
    virtual ~IGraph() {}
    
    virtual void AddEdge(int from, int to) = 0;
    virtual int VerticesCount() const = 0;
    
    virtual void GetNext(int vertex, std::vector<int>& vertices) const = 0;
    virtual void GetPrev(int vertex, std::vector<int>& vertices) const = 0;
};

class CListGraph : public IGraph {
private:
    std::vector<std::vector <int>> _graph; //вектор векторов, каждый из которых содержит вершины, в которые можно попасть из текущей вершины
    int _size;
    
public:
    explicit CListGraph(int size) : _graph(size), _size(size) {} //явные конструктора (explicit - google)
    explicit CListGraph(const IGraph * Graph) :
    _graph(Graph->VerticesCount()), //инициализируем вектор и переменную _size количеством вершин
    _size(Graph->VerticesCount())
    {
        for (int i(0); i < _size; ++i)
            Graph->GetNext(i, _graph[i]); //по каждому индексу вектора записываем вектор, где содержатся все вершины, в которые можно попасть из текущей
    }
    
    int VerticesCount() const override { //возвращает размер графа
        return _size;
    }
    
    void AddEdge(int from, int to) override { //добавляет ребро
        if (from >= _size || to >= _size || from < 0 || to < 0)
            return;
        _graph[from].push_back(to);
        _graph[to].push_back(from); //если граф неориентированный
    }
    
    void GetNext(int vertex, std::vector<int>& vertices) const override { //копирует в вектор vertices все вершины, в которые можно попасть из данной
        if (vertex >= _size || vertex < 0)
            return;
        vertices = _graph[vertex];
    }
    
    void GetPrev(int vertex, std::vector<int>& vertices) const override {//копирует в вектор vertices все вершины, из которых можно попасть в данную
        if (vertex >= _size || vertex < 0)
            return;
        for(int j(0); j < _size; ++j) {
            for(auto i : _graph[j]) {
                if (i == vertex)
                    vertices.push_back(j);
                    }
        }
    }
    void debAg () const { //вывод графа в виде вершина : все ее дети
        for (int i(0); i<_size; ++i) {
            std::cout << i << ": ";
            for (auto g : _graph[i] ) {
                std::cout << g << " ";
            }
            std::cout << std::endl;
        }
    }
    
    
    int bfs(int vertex) {
        std::queue <int> queue; //очередь для bfs
        std::vector<int> distance(_size, 0), parent(_size, -1); //расстояние от исходной вершины до остальных
        std::vector<bool> visited(_size, false); //были ли в вершине?
        queue.push(vertex); //пушим в очередь первый элемент
        distance[vertex] = 0; //расстояние до самого себя 0
        visited[vertex] = true; //мы были в вершине
        while (!queue.empty()) { //пока в очереди есть элементы
            int current = queue.front(); //текущий = первый в очереди
            queue.pop(); //выбрасываем его из очереди
            for (int a : _graph[current]) { //_graph[current] это вектор, содержащий всех детей, проходим по нему итератором a(a по очереди принимает значение каждого элемента вектора)
                if (!visited[a]) { //если не были в а
                    queue.push(a); //пушим в очередь
                    distance[a] = distance[current] + 1; //расстояние до а это расстоение до ее родителя+1
                    parent[a] = current; //родитель а
                    visited[a] = true; //побывали в а
                } else if (parent[current] != a) { //если в вершине были и это не непосредственный предок текущей вершины
                    return distance[a] + distance[current] + 1;  //ответом будет расстоение до а + расстояние до предка + 1
                }
            }
        }
        return std::numeric_limits<int>::max(); //иначе верни самый большой инт
    }
    
    int findMinCycle() { //проходим по всем вершинам и ищем цикл минимальной длины
        int ans = std::numeric_limits<int>::max();
        for (int i(0); i < _size; ++i) {
            ans = std::min(ans, bfs(i));
        }
        return ans;
    }
};

using namespace std;

int main() {
    int n, m, a, b;
    cin >> n >> m;
    
    CListGraph graph(n);
    for (int i(0); i < m; ++i)  {
        cin >> a >> b;
        graph.AddEdge(a, b);
    }
    
    int minCycle = graph.findMinCycle();
    if (minCycle == std::numeric_limits<int>::max()) {
        cout << -1;
    } else {
        cout << minCycle;
    }
}
