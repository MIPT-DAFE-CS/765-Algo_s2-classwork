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
            _graph[to].push_back(from);
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

        /** Do breadth first search starting from @a vertex until finding vertex form search front.
         *  @retval min length cycle that contains @a vertex or std::numeric_limits<int>::max() if there is no cycle. */
        int bfs(int vertex) {
            std::queue <int> queue;
            std::vector<int> distance(_size, 0), parent(_size, -1);
            std::vector<bool> visited(_size, false);

            queue.push(vertex);
            distance[vertex] = 0;
            visited[vertex] = true;
            while (!queue.empty()) {
                int current = queue.front();
                queue.pop();
                for (int a : _graph[current]) {
                    if (!visited[a]) {
                        queue.push(a);
                        distance[a] = distance[current] + 1;
                        parent[a] = current;
                        visited[a] = true;
                    } else if (parent[current] != a) {
                        return distance[a] + distance[current] + 1;
                    }
                }
            }
            return std::numeric_limits<int>::max();
        }

        int findMinCycle() {
            int ans = std::numeric_limits<int>::max();
            for (int i(0); i < _size; ++i) {
                ans = std::min(ans, bfs(i));
            }
            return ans;
        }

        bool find_way(int from, int to)
        {
            std::queue <int> queue;
            std::vector <bool> visited(_size, false);

            queue.push(from);
            visited[from] = true;
            while (!queue.empty()) {
                int current = queue.front();
                queue.pop();
                for (int a : _graph[current]) {
                    if (!visited[a]) {
                        queue.push(a);
                        visited[a] = true;
                    } else if (a == to) {
                        return true;
                    }
                }
            }
            return false;
        }
};

using namespace std;

double const eps = 0.0001;

double distance (pair <int, int> First , pair <int, int> Second){
    return hypot(First.first - Second.first, First.second - Second.second);
}

double binary_search(int lwall, int rwall, int R, vector < pair <int, int> > &columns)
{
    double l(0), r(rwall - lwall), d;
    int n = columns.size();
    while (r - l > eps)
    {
        d = (l + r) / 2.0;
        CListGraph graph(n + 2);
        for (int i(0); i < n; ++i) {
            if (abs(lwall - columns[i].first) - R - d < eps)
                graph.AddEdge(0, i + 1); // ребро между левой стеной и колонной
            if (abs(rwall - columns[i].first) - R - d < eps)
                graph.AddEdge(i + 1, n + 1); // ребро между правой стеной и колонной
        }

        for (int i(0); i < n; ++i)
            for (int j(0); j < n; ++j)
                if (abs(distance(columns[i], columns[j]) - 2 * R - d) < eps)
                    graph.AddEdge(i + 1, j + 1);

        if (graph.find_way(0, n + 1))
            r = d;
        else
            l = d;
    }
    return d;
}


int main () {
    int XL, XR, r, n, x, y;
    cin >> XL >> XR >> r >> n;
    vector <pair <int, int> > columns(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> columns[i].first >> columns[i].second;
    }
    fixed(cout);
    double ans = round(1000 * binary_search (XL, XR, r, columns));
    cout << setprecision(3) << ans / 1000.0;
    cin.get();
    cin.get();
}
