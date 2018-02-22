#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std ;
struct dot {
    int coord,type;
    void out () {
        cout<<coord<<" "<<type;
    }
};
bool operator > (dot dot1,dot dot2) {
    if (dot1.coord>dot2.coord) {
        return true;
    } else if (dot1.coord==dot2.coord && dot1.type==1) {
        return true;
    }
    return false;
}
bool operator < (dot dot1,dot dot2) {
    if (dot1.coord<dot2.coord) {
        return true;
    } else if (dot1.coord==dot2.coord && dot1.type==0) {
        return true;
    }
    return false;    return false;
}
bool operator == (dot dot1,dot dot2) {
    if (dot1.coord==dot2.coord) {
        return true;
    }
    return false;
}
bool operator != (dot dot1,dot dot2) {
    return !(dot1==dot2);
}
struct Heap {
    int size;
    dot* buf;
    Heap (dot* arr,int n) {
        buf=arr;
        size=n;
        for (int i=n;i>0;--i) {
            down(i);
        }
    }
    bool hasleft (int i) {
        return 2*i<=size;
    }
    bool hasright (int i) {
        return 2*i+1<=size;
    }
    int left (int i) {
        return 2*i;
    }
    int right (int i) {
        return 2*i+1;
    }
    int par (int i) {
        return i/2;
    }
    void down (int i) {
        if (hasleft(i) && hasright(i)) {
            int maxi=(buf[left(i)]>buf[right(i)])? left(i):right(i);
            if (buf[i]<buf[maxi]) {
                swap(buf[i], buf[maxi]);
                down (maxi);
            }
        }
        if (hasleft(i)) {
            if (buf[i]<buf[left(i)]) {
                swap(buf[i], buf[left(i)]);
                down (left(i));
            }
        }
    }
    void up (int i) {
        if (buf[i]>buf[par(i)] && i>1) {
            swap (buf[i],buf[par(i)]);
            up(par(i));
        }
    }
    void sort()
    {
        int z=size;
        while (size>1)
        {
            swap(buf[1],buf[size]);
            size--;
            down(1);
        }
        size=z;
    }
    void debAg () {
        cout<<"\n"<<"****************"<<"\n";
        for (int i(1);i<=size;++i) {
            buf[i].out();
            cout<<endl;
        }
        cout<<"\n"<<"****************"<<"\n";
    }
    int ans () {
        int ans(0),tmp(0),begin(0);
        for (int i(1);i<=size;++i) {
            if (buf[i].type==0) {
                tmp+=1;
                if (tmp==1) {
                    begin=buf[i].coord;
                }
            } else {
                tmp-=1;
                if (tmp==0) {
                    ans+=buf[i].coord-begin;
                    begin=0;
                }
            }
        }
        return ans;
    }
    
};
int main() {
    int n,x,y;
    cin>>n;
    dot arr[2*n+1];
    for (int i(0);i<n;++i) {
        cin>>x>>y;
        arr[i*2+1].coord=x;
        arr[i*2+1].type=0;
        arr[i*2+2].coord=y;
        arr[i*2+2].type=1;
    }
    Heap heap(arr,2*n);
    heap.sort();
    //heap.debAg();
    cout<<heap.ans()<<endl;
    
}











