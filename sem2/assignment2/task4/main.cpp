#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <set>

using namespace std;

const short S=4;

class Pole {
public:
    short size = S;
    char hwgh ='';
    short arr[S][S];
    pair <short,short> inz; // позиция нуля
    short distance=0;
    short manh_d=0;
    pair <short,short> rp (short val) {
        if(val == 0) {
            return make_pair(S-1, S-1);
        } else {
            return make_pair(val/S, val%S);
        }
    }
    Pole (short a[S][S]) {
        size = S;
        for (short i(0);i<size;++i) {
            for (short j(0);j<size;++j) {
                arr[i][j]=a[i][j];
                if (!arr[i][j]) inz=make_pair(i,j);
            }
        }
        if (!manh_d) {
            for (short i(0);i<size;++i) {
                for (short j(0);j<size;++j) {
                    short tmp = abs(rp(arr[i][j]).first-i)+abs(rp(arr[i][j]).second-j);
                    manh_d+=tmp;
                }
            }
        }
    }

    uint64_t hashize() const {
        uint64_t a;
        for (int i(0); i < S; ++i) {
            for (int j(0); j < S; ++j) {
              a |= (arr[i][j] & 0xF) << (i + j);
            }
        }
        return a;
    }

    /** @pre sero position shouldn't be in S-1 column. */
    Pole R () {
        short tmparr[S][S];
        for (short i(0);i<size;++i) {
            for (short j(0);j<size;++j) {
                tmparr[i][j]=arr[i][j];
            }
        }
        swap (tmparr[inz.first][inz.second], tmparr[inz.first][inz.second-1]);
        Pole p(tmparr);
        return p;
    }

    /** @pre sero position shouldn't be in 0 column. */
    Pole L () {
        short tmparr[S][S];
        for (short i(0);i<size;++i) {
            for (short j(0);j<size;++j) {
                tmparr[i][j]=arr[i][j];
            }
        }
        swap (tmparr[inz.first][inz.second], tmparr[inz.first][inz.second+1]);
        Pole p(tmparr);
        return p;
    }

    /** @pre sero position shoudn't be in S-1 row. */
    Pole U () {
        short tmparr[S][S];
        for (short i(0);i<size;++i) {
            for (short j(0);j<size;++j) {
                tmparr[i][j]=arr[i][j];
            }
        }
        swap (tmparr[inz.first][inz.second], tmparr[inz.first-1][inz.second]);
        Pole p(tmparr);
        return p;
    }

    /** @pre sero position shoudn't be in 0 row. */
    Pole D () {
        short tmparr[S][S];
        for (short i(0);i<size;++i) {
            for (short j(0);j<size;++j) {
                tmparr[i][j]=arr[i][j];
            }
        }
        swap (tmparr[inz.first][inz.second], tmparr[inz.first+1][inz.second]);
        Pole p(tmparr);
        return p;
    }


};

ostream& operator << (ostream& os, Pole& p) {
    for (short i(0);i<4;++i) {
        os << endl;
        for (short j(0);j<4;++j) {
            os << p.arr[i][j]<<" ";
        }
    }
    return os;
}


template <>
struct hash<Pole>
{
    size_t operator()(const Pole & x) const {
        return std::hash<uint64_t>()(x.hashize());
    }
};


typedef pair <int, Pole> PairIntPole;

string AStar(Pole& p) {
    unordered_set <Pole> visited;
    set<PairIntPole> pip;
    pip.emplace(make_pair(p.manh_d,p));
    while (!pip.empty()) {
        Pole current = (pip.begin())->second;
        pip.erase(pip.begin());

        pair <short,short> zero_index = p.inz; //позиция нуля
        if (zero_index.second < S-1) {
            auto right = current.R();
            if (!visited.find(right) && )
            pip.emplace(make_pair(right.manh_d + 1 + current.distance, right));
        }
        if (zero_index.second > 0) {
            auto left = current.L();
            pip.emplace(make_pair(left.manh_d + 1 + current.distance, left));
        }
        if (zero_index.first > 0) {
            auto up = current.U();
            pip.emplace(make_pair(up.manh_d + 1 + current.distance, up));
        }
        if (zero_index.first < S-1) {
            auto down = current.D();
            pip.emplace(make_pair(down.manh_d + 1 + current.distance, down));
        }
    }
    return way_weight[to];
}

int main()
{
  Pole field(short arr[S][S]);
  cin >> ;
  AStar(field);

  return 0;
}
