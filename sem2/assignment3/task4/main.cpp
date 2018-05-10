#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
using namespace std;
enum Type {inLine, inTemplate, cons};

struct Edge {
    int from, to;
    int capacity;
    int flow;
};

class Graph {
private:
    std::vector<std::vector<Edge>> _adjacency;
    size_t _size;

public:
    Graph (size_t s) : _size(s) {
      _adjacency.resize(s, std::vector<Edge>(s, Edge{0,0,0,0}));
      for(int i=0; i<_size; ++i) {
          for(int j=0; j<_size; ++j) {
              _adjacency[i][j].from = i;
              _adjacency[i][j].to = j;
              _adjacency[j][i].from = j;
              _adjacency[j][i].to = i;
          }
      }
    }

    void increaseEdgeCapacity(int i, int j) {
      _adjacency[i][j].capacity++;
      _adjacency[j][i].capacity++;
    }

    void increaseEdgeFlow(int i, int j, int flow) {
      _adjacency[i][j].capacity+= flow;
      _adjacency[j][i].capacity+= flow;
    }

    int possibleFlow(int i, int j) {
        return _adjacency[i][j].capacity - _adjacency[i][j].flow;
    }

    size_t size() {return _size; }

    const Edge & operator()(int i, int j) const {
        return _adjacency[i][j];
    }

    void debug () {
        for (int i{0}; i < _size; ++i) {
            for (int j{0}; j < _size; ++j) {
                std::cout << "from: " << i << " to: " << j << " capacity: " << _adjacency[i][j].capacity << " flow: " << _adjacency[i][j].flow << std::endl;
            }
        }
    }
};

bool bfs(Graph & graph, int from, int to, vector<int> & parent)
{
	queue <int> queue;
    vector <bool> visited(graph.size(), false);
	queue.push(from);
	visited[from] = true;
	while (!queue.empty())
	{
		int cur = queue.front();
		visited[cur] = true;
		queue.pop();
		for (int i(0); i < graph.size(); ++i)
		{
            auto edge = graph(cur, i);
            if (visited[edge.to] || edge.capacity == edge.flow) continue;
			queue.push(edge.to);
			parent[edge.to] = i;
			if (edge.to == to) return true;
		}
	}
	return false;
}

int find(Graph & graph, int from, int to, vector<int> &parent) {
    int min_edge{numeric_limits<int>::max()};
	int cur{to};
	while (cur != from) {
        int possibleFlow = graph.possibleFlow(parent[cur], cur);
		if (possibleFlow <  min_edge)
			min_edge = possibleFlow;
		cur = parent[cur];
	}
    return min_edge;
}

void push_flow(Graph & graph, int from, int to, vector<int> &parent, int min_edge) {
	int cur(to);
	while (cur != from) {
        graph.increaseEdgeFlow(min_edge, from, to);
		cur = parent[cur];
	}
}

int ford_falkerson(Graph & graph, int from, int to) {
	vector<int> parent(graph.size());
	int min_edge, ans(0);
	bool is_way(false);
	while (true)
	{
		is_way = bfs(graph, from, to, parent);
		if (!is_way) break;
		min_edge = find(graph, from, to, parent);
		push_flow(graph, from, to, parent, min_edge);
		ans += min_edge;
	}
	return ans;
}

int solver (string & s, string & t) {
    int qInS(0);
    int qInT(0);
    int index{2};
    int distance{0};
    std::map <int, std::pair<Type, int>> conteiner1;
    std::map <std::pair<Type, int>, int> conteiner2;
    for ( int i{0}; i<s.size(); ++i)  {
        if (s[i] == '?') {
            qInS++;
            conteiner1[index] = std::make_pair (Type::inLine, i);
            conteiner2[std::make_pair (Type::inLine, i)] = index++;
        }
    }
    for ( int i{0}; i<t.size(); ++i)  {
        if (t[i] == '?') {
            qInT++;
            conteiner1[index] = std::make_pair (Type::inTemplate, i);
            conteiner2[std::make_pair (Type::inTemplate, i)] = index++;
        }
    }
    Graph _graph(qInS + qInT + 2);

    for (int i{0}; i + t.size() <= s.size(); ++i) {
        string tmp = s.substr(i, t.size());
        for (int j{0}; j < t.size(); ++j) {
            if (tmp[j]!='?' && t[j]!='?' && tmp[j]!=t[j]) distance++;
            switch (tmp[j]) {
                case '?':
                    switch (t[j]) {
                        case '?':
                            _graph.increaseEdgeCapacity(conteiner2[std::make_pair(Type::inLine,i+j)], conteiner2[std::make_pair(Type::inTemplate,j)]);
                            break;
                        case '0':
                            _graph.increaseEdgeCapacity(conteiner2[std::make_pair(Type::inLine,i+j)], 0);
                            break;
                        case '1':
                            _graph.increaseEdgeCapacity(conteiner2[std::make_pair(Type::inLine,i+j)], 1);
                            break;
                    }
                    break;
            }
            switch (t[j]) {
                case '?':
                    switch (tmp[j]) {
                        case '0':
                            _graph.increaseEdgeCapacity(conteiner2[std::make_pair(Type::inTemplate,j)], 0);
                            break;
                        case '1':
                            _graph.increaseEdgeCapacity(conteiner2[std::make_pair(Type::inTemplate,j)], 1);
                            break;
                    }
                    break;
            }
        }
    }
    _graph.debug();
    std::cout<<std::endl<<std::endl;
    distance += ford_falkerson(_graph, 0, 1);
    _graph.debug();
    vector<int> parent(_graph.size());
    for (int i(2); i < _graph.size(); ++i) {
        if (bfs(_graph, i, 0, parent)) {
            if (conteiner1[i].first == Type::inLine) {
                s[conteiner1[i].second] = '0';
            } else {
                t[conteiner1[i].second] = '0';
            }
        } else {
            if (conteiner1[i].first == Type::inLine) {
                s[conteiner1[i].second] = '1';
            } else {
                t[conteiner1[i].second] = '1';
            }
        }
    }
    return distance;
}

int main ()
{
     string s,t;
     cin >> s >> t;
     cout << solver(s,t) << endl << s << endl << t;
}
