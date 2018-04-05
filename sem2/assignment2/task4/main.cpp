#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <set>

using namespace std;

const short size = 4; //размер поля

class Field {
public:
    char way=' ';
    short field[size][size];
    pair <short, short> zero_in;
    short graph_d = 0;
    short manh_d = 0;
    pair <short,short> rp (short val) {
        if(val == 0) {
            return make_pair(size-1, size-1);
        } else {
            return make_pair(val/size, val%size);
        }
    }
    Field (short a[size][size]) {
        for (short i(0);i<size;++i) {
            for (short j(0);j<size;++j) {
                short tmp = abs(rp(field[i][j]).first-i)+abs(rp(field[i][j]).second-j);
                manh_d+=tmp;
                if (!field[i][j]) zero_in=make_pair(i,j);
            }
        }
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
    Field R () {
        short tmpfield[size][size];
        for (short i(0);i<size;++i) {
            for (short j(0);j<size;++j) {
                tmpfield[i][j]=field[i][j];
            }
        }
        swap (tmpfield[zero_in.first][zero_in.second], tmpfield[zero_in.first][zero_in.second-1]);
        Field p(tmpfield);
        return p;
    }
    
    /** @pre sero position shouldn't be in 0 column. */
    Field L () {
        short tmpfield[size][size];
        for (short i(0);i<size;++i) {
            for (short j(0);j<size;++j) {
                tmpfield[i][j]=field[i][j];
            }
        }
        swap (tmpfield[zero_in.first][zero_in.second], tmpfield[zero_in.first][zero_in.second+1]);
        Field p(tmpfield);
        return p;
    }
    
    /** @pre sero position shoudn't be in size-1 row. */
    Field U () {
        short tmpfield[size][size];
        for (short i(0);i<size;++i) {
            for (short j(0);j<size;++j) {
                tmpfield[i][j]=field[i][j];
            }
        }
        swap (tmpfield[zero_in.first][zero_in.second], tmpfield[zero_in.first-1][zero_in.second]);
        Field p(tmpfield);
        return p;
    }
    
    /** @pre sero position shoudn't be in 0 row. */
    Field D () {
        short tmpfield[size][size];
        for (short i(0);i<size;++i) {
            for (short j(0);j<size;++j) {
                tmpfield[i][j]=field[i][j];
            }
        }
        swap (tmpfield[zero_in.first][zero_in.second], tmpfield[zero_in.first+1][zero_in.second]);
        Field p(tmpfield);
        return p;
    }
};

ostream& operator << (ostream& os, Field& f) {
    for (short i(0);i<4;++i) {
        os << endl;
        for (short j(0);j<4;++j) {
            os << f.field[i][j]<<" ";
        }
    }
    return os;
}

bool operator > (Field& f1, Field& f2) {return f1.graph_d > f2.graph_d;}
bool operator < (Field& f1, Field& f2) {return f1.graph_d < f2.graph_d;}

template <>
struct hash<Field>
{
    size_t operator()(const Field & x) const {
        return std::hash<uint64_t>()(x.hashize());
    }
};

typedef pair <int, Field> PairIntField;

string AStar(Field& p) {
    unordered_set <Field> visited;
    set<PairIntField> pif;
    pif.emplace(make_pair(p.manh_d,p));
    while (!pif.empty()) {
        Field current = (pif.begin())->second;
        pif.erase(pif.begin());
        
        pair <short,short> zero_index = p.zero_in; //позиция нуля
        if (zero_index.second < size-1) {
            auto right = current.R();
            if (!visited.find(right) && )
                //   pif.emplace(make_pair(right.manh_d + 1 + current.distance, right));
                }
        if (zero_index.second > 0) {
            auto left = current.L();
            // pif.emplace(make_pair(left.manh_d + 1 + current.distance, left));
        }
        if (zero_index.first > 0) {
            auto up = current.U();
            //  pif.emplace(make_pair(up.manh_d + 1 + current.distance, up));
        }
        if (zero_index.first < size-1) {
            auto down = current.D();
            //   pif.emplace(make_pair(down.manh_d + 1 + current.distance, down));
        }
    }
}

int main()
{
    //Field field(short field[S][S]);
    //cin >> field;
    //AStar(field);
    return 0;
}











