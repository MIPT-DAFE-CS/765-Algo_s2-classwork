#include <iostream>
#include <string>
using namespace std;
enum Type = {inLine, inTemplate};
class Vertex
{
public:
    char _name;
    short _number;
    int _q_index;
    Type type;
}

class Graph
{
public:
    size_t _size;
    std::vector<std::vector<short>>  _graph;
    vector<Vertex> _vertexes;
    Graph (string s, string p)
    {
        _vertexes.push_back (Vertex ("0", 0, -1, inLine));
        for (int i{0}; i < s.size(); i++) {
            auto ch = s[i];
            if (ch == "?") {
                _size++;
                _vertexes.push_back (Vertex ('?', _size - 1, i, inLine));
            }
        }
        for (int i{0}; i < p.size(); i++) {
            auto ch = p[i];
            if (ch == "?") {
                _size++;
                _vertexes.push_back (Vertex ('?', _size - 1, i, inTemplate));
            }
        }
        _vertexes.push_back (Vertex ("1", _size++, -1, inLine));
        _graph.resize(_size);
        for (auto v : _graph)
            v.resize(_size, 0);

    }
    void fill_weights(strings s, )
    {

    }
}

string solver ()


int main()
{
    string s, p;
    std::cin >> s >> p;


}
