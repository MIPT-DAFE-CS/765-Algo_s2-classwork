#include <iostream>
#include <queue>
#include <vector>
#include <limits>

using namespace std;

int main() {
    int n, m, a, b, w;
    std::cin >> n >> m;
    vector < vector < pair<int,int> > > g (n);
    for (int i(0); i < m; ++i)
    {
        std::cin >> a >> b >> w;
        g[a].push_back(make_pair(b, w));
        g[b].push_back(make_pair(a, w));
    }
    int from, to;
    cin >> from >> to;
    int s = from;
    vector<int> d (n, INF),  p (n);
    d[s] = 0;
    vector<bool> u (n);
    for (int i=0; i<n; ++i) {
        int v = -1;
        for (int j=0; j<n; ++j)
            if (!u[j] && (v == -1 || d[j] < d[v]))
                v = j;
        if (d[v] == INF)
            break;
        u[v] = true;
        
        for (size_t j=0; j<g[v].size(); ++j) {
            int to = g[v][j].first,
            len = g[v][j].second;
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
            }
        }
    }
    std::cout << d[to] <<endl;
}