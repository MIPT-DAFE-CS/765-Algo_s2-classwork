#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <string>

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
		for (int j(0); j < _size; ++j) {
			for (auto i : _graph[j]) {
				if (i == vertex)
					vertices.push_back(j);
			}
		}
	}
	void debAg() const {
		for (int i(0); i<_size; ++i) {
			std::cout << i << ": ";
			for (auto g : _graph[i]) {
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
				}
				else if (parent[current] != a) {
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

const int N = 2000;

int main() {
	int graph[N][N];
	int n;
	cin >> n;
	if (n > N)
	{
		cout << "N is too little\n";
		return 0;
	}
	for (int i(0); i < n; ++i)
		for (int j(0); j < n; ++j)
		{
			cin >> graph[i][j];
		}
	vector <int> can_be(n, 1);
	for (int i(0); i < n; ++i)
	{
		if (!can_be[i]) continue;
		for (int j(0); j < n; ++j)
		{
			if (i == j) continue;
			if (graph[i][j] == 1)
			{
				can_be[i] = 0;
				break;
			}
			if (graph[i][j] == 0)
				can_be[j] = 0;
		}
	}
	
	for (int j(0); j < n; ++j)
	{
		if (!can_be[j]) continue;
		for (int i(0); i < n; ++i)
		{
			if (i == j) continue;
			if (graph[i][j] == 0)
			{
				can_be[j] = 0;
				break;
			}
			if (graph[i][j] == 1)
				can_be[i] = 0;
		}
	}
	string ans("NO");
	for (int i(0); i < n; ++i)
	{
		if (can_be[i])
			ans = "YES";
	}
	cout << ans;
	cin.get();
	cin.get();
}
