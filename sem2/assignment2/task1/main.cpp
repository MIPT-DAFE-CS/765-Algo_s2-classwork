#include <iostream>
#include <queue>
#include <vector>
#include <limits>

using namespace std;

class IWeightedGraph
{
public:
  virtual int VerticesCount() const = 0;
  virtual void AddEdge(int from, int to, short weight)  = 0 ;
  virtual void GetNext(int vertex, std::vector <pair <short, short>>& vertices) const = 0;
  virtual void GetPrev(int vertex, std::vector <pair <short, short>>& vertices) const = 0;
  virtual short GetWeight (int from, int to) const = 0;
};

class CListGraph : public IWeightedGraph
{
    private:
        std::vector<std::vector <pair <short, short>>> _graph;
        int _size;

    public:
        explicit CListGraph(int size) : _graph(size), _size(size)
        {
        }
        explicit CListGraph(const IWeightedGraph * Graph) :
            _graph(Graph->VerticesCount()),
            _size(Graph->VerticesCount())
        {
          for (int i(0); i < _size; ++i)
              Graph->GetNext(i, _graph[i]);
        }

        int VerticesCount() const override
        {
            return _size;
        }

        void AddEdge(int from, int to, short weight) override
        {
            if (from >= _size || to >= _size || from < 0 || to < 0)
                return;
            _graph[from].push_back(make_pair(to,weight));
            _graph[to].push_back(make_pair(from,weight));
            //_graph[to].push_back(from);
        }

        void GetNext(int vertex, std::vector<pair <short,short>>& vertices) const override
        {
            if (vertex >= _size || vertex < 0)
                return;
            vertices = _graph[vertex];
        }

        void GetPrev(int vertex, std::vector<pair <short,short>>& vertices) const override
        {
            /*if (vertex >= _size || vertex < 0)
                return;
            for(int j(0); j < _size; ++j)
            {
                for(auto i : _graph[j])
                {
                    if (i.first == vertex)
                        vertices.push_back(j);
                }
            }*/
        }

        short GetWeight (int from, int to) const override
        {
          for (auto i : _graph[from]) {
            if (i.first==to) return i.second;
          }
          return -1;
        }
        void debAg () const
        {
            //ПОМЕНЯТЬ
        }
};

typedef pair<int, short> pid;

short deijkstra(const IWeightedGraph & graph, int from, int to)
{
  auto compare = [](pid p1, pid p2){ return p1.second > p2.second; };
  std::priority_queue <pid, std::vector<pid>, decltype( compare )> pq(compare);
  vector<short> way_weight(graph.VerticesCount(), 20000);
  vector<bool> attendence(graph.VerticesCount(), false);
  pq.push(make_pair(from,0));
  way_weight[from] = 0;
  while (!pq.empty()) {
    int current = pq.top().first;
    pq.pop();
    vector<pair <short,short>> next;
    graph.GetNext(current,next);
    attendence[current]=true;
    for (auto child : next ) {
      if (!attendence[child.first]) {
        if (way_weight[child.first] > way_weight[current]+child.second)
        {
          way_weight[child.first] = way_weight[current]+child.second;
        }
        pq.push(make_pair(child.first, way_weight[child.first]));
      }
    }
  }
  return way_weight[to];
}

int main()
{
  int n, m, a, b, w;
  cin >> n >> m;
	CListGraph graph(n);
  for (int i(0); i < m; ++i)
	{
		cin >> a >> b >> w;
    if (w < graph.GetWeight(a, b)||graph.GetWeight(a, b)==-1)
    {
  		graph.AddEdge(a, b, w);
    }
	}


  int from, to;
  cin >> from >> to;

  cout << deijkstra(graph, from, to);

  return 0;
}
