#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

struct Edge {
	int to, capacity, flow, rev_id;
	Edge() {}
	Edge(int to, int capacity, int flow, int rev_id) :
		to(to), capacity(capacity), flow(flow), rev_id(rev_id) {}
};

bool bfs(vector < vector <Edge> > &graph, int n, vector <pair <int, int> > &parent)
{
	std::queue <int> queue;
	std::vector <bool> visited(graph.size(), false);
	queue.push(0);
	visited[0] = true;
	while (!queue.empty())
	{
		int cur = queue.front();
		visited[cur] = true;
		queue.pop();
		for (int i(0); i < graph[cur].size(); ++i)
		{
			Edge child = graph[cur][i];
			if (visited[child.to] || child.capacity == child.flow) continue;
			queue.push(child.to);
			parent[child.to] = { cur, i };
			if (child.to == n - 1) return true;
		}
	}
	return false;
}

void find(vector < vector <Edge> > &graph, vector <pair <int, int> > &parent, int n, int &min_edge)
// на первом месте вершина, из которой мы идём, а потом номер ребра, мин capacity-flow
{
	int cur(n - 1);
	min_edge = std::numeric_limits<int>::max();
	while (cur != 0)
	{
		if (graph[parent[cur].first][parent[cur].second].capacity - graph[parent[cur].first][parent[cur].second].flow <  min_edge)
			min_edge = graph[parent[cur].first][parent[cur].second].capacity - graph[parent[cur].first][parent[cur].second].flow;
		cur = parent[cur].first;
	}
}

void push_flow(vector < vector <Edge> > &graph, vector <pair <int, int> > &parent, int n, int &min_edge)
{
	int cur(n - 1);
	while (cur != 0)
	{
		graph[parent[cur].first][parent[cur].second].flow += min_edge;
		cur = parent[cur].first;
	}
}

int ford_falkerson(vector < vector <Edge> > &graph, int n)
{
	vector <pair <int, int> > parent(n);
	int min_edge, ans(0);
	bool is_way(false);
	while (true)
	{
		is_way = bfs(graph, n, parent);
		if (!is_way) break;
		find(graph, parent, n, min_edge);
		push_flow(graph, parent, n, min_edge);
		ans += min_edge;
	}
	return ans;
}

int main()
{
	int n, m, a, b, c;
	vector <vector <Edge>> edges;
	cin >> n >> m;
	edges.resize(n);
	for (int i(0); i < m; i++)
	{
		cin >> a >> b >> c;
		edges[a - 1].push_back(Edge(b - 1, c, 0, edges[b - 1].size()) );
		edges[b - 1].push_back(Edge(a - 1, 0, 0, edges[a - 1].size() - 1));
	}
	cout << ford_falkerson(edges, n);
	cin.get();
	cin.get();
	return 0;
}
