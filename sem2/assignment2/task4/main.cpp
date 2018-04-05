#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <string>
#include <set>
#include <unordered_set>

using namespace std;

const short size = 4; //размер поля

class Field {
public:
    const Field* parent = nullptr;
    short field[size][size];
    pair <short, short> zero_in;
    short graph_d = 0;
    short manh_d = 0;
    pair <short,short> rp (short val) {
        if(val == 0) {
            return make_pair(size-1, size-1);
        } else {
            return make_pair((val-1)/size, (val-1)%size);
        }
    }
    Field () {}
    Field (short a[size][size]) {
        for (short i(0); i < size; ++i) {
            for (short j(0); j < size; ++j) {
                field[i][j] = a[i][j];
                short tmp = abs(rp(field[i][j]).first-i) + abs(rp(field[i][j]).second-j);
                manh_d += tmp;
                if (!field[i][j]) zero_in = make_pair(i,j);
            }
        }
        graph_d += manh_d;
    }
    uint64_t hashize() const {
        uint64_t a;
        for (int i(0); i < size; ++i) {
            for (int j(0); j < size; ++j) {
                a |= (field[i][j] & 0xF) << (i + j);
            }
        }
        return a;
    }

    /** @pre sero position shouldn't be in size-1 column. */
    Field R () const {
        short tmpfield[size][size];
        for (short i(0);i<size;++i) {
            for (short j(0);j<size;++j) {
                tmpfield[i][j]=field[i][j];
            }
        }
        swap (tmpfield[zero_in.first][zero_in.second], tmpfield[zero_in.first][zero_in.second-1]);
        Field p(tmpfield);
        p.parent = this;
        return p;
    }

    /** @pre sero position shouldn't be in 0 column. */
    Field L () const {
        short tmpfield[size][size];
        for (short i(0);i<size;++i) {
            for (short j(0);j<size;++j) {
                tmpfield[i][j]=field[i][j];
            }
        }
        swap (tmpfield[zero_in.first][zero_in.second], tmpfield[zero_in.first][zero_in.second+1]);
        Field p(tmpfield);
        p.parent = this;
        return p;
    }

    /** @pre sero position shoudn't be in size-1 row. */
    Field U () const {
        short tmpfield[size][size];
        for (short i(0);i<size;++i) {
            for (short j(0);j<size;++j) {
                tmpfield[i][j]=field[i][j];
            }
        }
        swap (tmpfield[zero_in.first][zero_in.second], tmpfield[zero_in.first-1][zero_in.second]);
        Field p(tmpfield);
        p.parent = this;
        return p;
    }

    /** @pre sero position shoudn't be in 0 row. */
    Field D () const {
        short tmpfield[size][size];
        for (short i(0);i<size;++i) {
            for (short j(0);j<size;++j) {
                tmpfield[i][j]=field[i][j];
            }
        }
        swap (tmpfield[zero_in.first][zero_in.second], tmpfield[zero_in.first+1][zero_in.second]);
        Field p(tmpfield);
        p.parent = this;
        return p;
    }

   bool Checking () { //ПРОВЕРКА НА НАЛИЧИЕ РЕШЕНИЙ У
        int inv(0);
        short mas [size*size];
        for (short i = 0; i < size; ++i)
            for (short j = 0; j < size; ++j)
                mas [i*size+j] = field [i][j];
        for (int i=0; i<size*size; ++i)
            if (mas[i])
                for (int j=0; j<i; ++j)
                    if (mas[j] > mas[i])
                        ++inv;
        if (((inv + zero_in.first) % 2) == 0)
            return false;
        else
            return true;
   }

    std::vector<Field> PossibleWays () const {
        std::vector<Field> pw;
        pw.reserve(4);
        if (zero_in.second < size-1) {
            pw.push_back(L());
        }
        if (zero_in.second > 0) {
            pw.push_back(R());
        }
        if (zero_in.first > 0) {
            pw.push_back(U());
        }
        if (zero_in.first < size-1) {
            pw.push_back(D());
        }
        return pw;
    }

    char Parent () const {
        if (parent == nullptr) return ' ';
        pair <short, short> tmp;
        tmp.first = zero_in.first - parent->zero_in.first;
        tmp.second = zero_in.second - parent->zero_in.second;
        if (tmp.second > 0) return 'L';
        if (tmp.second < 0) return 'R';
        if (tmp.first > 0) return 'D';
        if (tmp.first < 0) return 'U';
        return ' ';
    }
};

ostream& operator << (ostream& os, const Field& f) {
    for (short i(0);i<size;++i) {
        os << endl;
        for (short j(0);j<size;++j) {
            os << f.field[i][j]<<" ";
        }
    }
    return os;
}
bool operator > (const Field& f1, const Field& f2) {return f1.graph_d > f2.graph_d;}
bool operator >= (const Field& f1, const Field& f2) {return f1.graph_d >= f2.graph_d;}
bool operator < (const Field& f1, const Field& f2) {return f1.graph_d < f2.graph_d;}
bool operator <= (const Field& f1, const Field& f2) {return f1.graph_d <= f2.graph_d;}
bool operator != (const Field& f1, const Field& f2) {return f1.graph_d != f2.graph_d;}
bool operator == (const Field& f1, const Field& f2) { return !operator!=(f1, f2);}

template <>
struct hash<Field>
{
    size_t operator()(const Field & x) const {
        return std::hash<uint64_t>()(x.hashize());
    }
};

string AStar(Field& p) {
    unordered_set <Field> visited;
    set <Field> pif;
    pif.emplace(p);
    if (!p.manh_d) return "0";
    while (!pif.empty()) {
        Field current = *pif.begin();
        pif.erase(pif.begin());
        std::vector<Field> pw = current.PossibleWays();
        for (auto child : pw) {
             std::cout << child;
            if (child.manh_d == 0) {
              string ans;
              const Field * thiz = &child;
              while (thiz->parent != nullptr ) {
                ans += thiz->Parent();
                thiz = thiz->parent;
              }
              return ans;
            } else {
              if (visited.find(child) == visited.end() && pif.find(child) == pif.end()) {
                  child.graph_d +=  current.graph_d + 1;
                  pif.emplace(child);
              }
            }
        }
    }
    return "ok";
}

int main()
{
    short a[size][size];
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            cin >> a[i][j];

    Field f (a);
    cout << AStar(f);
    return 0;
}
