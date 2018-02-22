#include <iostream>

#include "IGraph.h"

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
