#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

struct IGraph {
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to) = 0;
    virtual int VerticesCount() const = 0;

    virtual void GetNext(int vertex, std::vector<int>& vertices) const = 0;
    virtual void GetPrev(int vertex, std::vector<int>& vertices) const = 0;
};

class CListGraph : public IGraph {
    private:
        std::vector<std::vector <int>> _graph;
        int _size;

    public:
        explicit CListGraph(int size) : _graph(size), _size(size) {}
        explicit CListGraph(const IGraph * Graph) :
            _graph(Graph->VerticesCount()),
            _size(Graph->VerticesCount())
        {
            for (int i(0); i < _size; ++i)
                Graph->GetNext(i, _graph[i]);
        }

        int VerticesCount() const override {
            return _size;
        }

        void AddEdge(int from, int to) override {
            if (from >= _size || to >= _size || from < 0 || to < 0)
                return;
            _graph[from].push_back(to);
            //_graph[to].push_back(from);
        }

        void GetNext(int vertex, std::vector<int>& vertices) const override {
            if (vertex >= _size || vertex < 0)
                return;
            vertices = _graph[vertex];
        }

        void GetPrev(int vertex, std::vector<int>& vertices) const override {
            if (vertex >= _size || vertex < 0)
                return;
            for(int j(0); j < _size; ++j) {
                for(auto i : _graph[j]) {
                    if (i == vertex)
                        vertices.push_back(j);
                }
            }
        }
        void debAg () const {
            for (int i(0); i<_size; ++i) {
                std::cout << i << ": ";
                for (auto g : _graph[i] ) {
                    std::cout << g << " ";
                }
                std::cout << std::endl;
            }
        }

        void dfs(int v, std::vector <bool> &visited, std::vector <int> &order)
        {
            visited[v] = true;
            for (int a : _graph[v])
                if (!visited[a])
                    dfs(a, visited, order);
            order.push_back(v);
        }

        void dfs2(int v, std::vector <int> &component, int num)
        {
            component[v] = num;
            for (int a : _graph[v])
                if (!component[a])
                    dfs2(a, component, num);
        }

        void dfs3 (int v, std::vector<bool> &visited, CListGraph &cond, std::vector<int> component)
        {
            visited[v] = true;
            for (int a : _graph[v]) {
                if (!visited[a])
                    dfs3(a, visited, cond, component);
                if (component[a] != component[v] )
                    cond.AddEdge(component[a] - 1, component[v] - 1);
            }
        }
};

using namespace std;

CListGraph Condensed (CListGraph& G, std::vector<int> &component ) {
    int n = G.VerticesCount();
    int condensedSize = *std::max_element(component.begin(), component.end());
    CListGraph Cond(condensedSize);
    vector <bool> visited(n, false);
    for (int i(0); i<n; ++i) {
        if (!visited[i]) {
            G.dfs3(i, visited, Cond, component);
        }
    }
    //debAg
    //Cond.debAg();
    return Cond;
}

CListGraph make_DAG(CListGraph &graph, CListGraph &back)
{
    int n = graph.VerticesCount();
    vector <bool> visited(n, false);
    vector <int> order;
    vector <int> component(n, 0);
    for (int i(0); i < n; ++i)
    {
        if (!visited[i])
            graph.dfs(i, visited, order);
    }
    int current(0);
    /*
    cout << "order: ";
    for (int i(0); i < n; ++i)
        cout << order[i] << ' ';

    cout << "\nvisited: ";
    for (int i(0); i < n; ++i)
        cout << visited[i] << ' ';
    */
    for (int i(n - 1); i >= 0; --i)
    {
        int v = order[i];
        if (!component[v]) {
            current++;
            back.dfs2(v, component, current);
        }
    }
    /*
    cout << "\ncomponent: ";
    for (int i(0); i < n; ++i)
        cout << component[i] << ' ';
        */
    return Condensed(graph, component);
}

int DAG_vertices (CListGraph &graph)
{
    int X{0}, Y{0};
    vector <int> vert;
    for (int i = 0; i < graph.VerticesCount(); ++i)
    {
        graph.GetNext(i, vert);
        if (vert.size() == 0)
            ++Y;
            vert.clear();
        graph.GetPrev(i, vert);
        if (vert.size() == 0)
            ++X;
            vert.clear();
    }
    if (graph.VerticesCount() == 1)
        return 0;
    else return max(X, Y);
}

int main () {
    int n, m, a, b;
    cin >> n >> m;
    CListGraph G(n);
    CListGraph TrG(n);
    for (int i(0); i < m; ++i)
    {
        cin >> a >> b;
        a--, b--;
        G.AddEdge(a, b);
        TrG.AddEdge(b, a);
    }
    CListGraph Cond = make_DAG(G, TrG);
    int result = DAG_vertices(Cond);
    cout << result;
    cin.get();
    cin.get();
}



// Вот тест с ошибкой
// {
//            "testName": "tests/04",
//            "sequenceNumber": 4,
//            "testsetIdx": 1,
//            "verdict": "WrongAnswer",
//            "message": "Answers do not match: out = 1, corr = 6\n",
//            "runningTime": 2,
//            "memoryUsed": 389120,
//            "input": "7\r\n6\r\n1 2\r\n1 3\r\n1 4\r\n1 5\r\n1 6\r\n1 7\r\n",
//            "output": "1",
//            "answer": "6\r\n",
//            "error": "",
//            "checkerError": "Answers do not match: out = 1, corr = 6\n",
//            "sample": false
//        }
