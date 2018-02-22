#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std ;
struct event {
    int day,month,year,type;
    void out () {
        cout<<day<<" "<<month<<" "<<year<<" "<<type;
    }
};
bool operator > (event event1,event event2) {
    if (event1.year>event2.year) {
        return true;
    } else if (event1.year==event2.year) {
        if (event1.month>event2.month) {
            return true;
        }
        else if (event1.month==event2.month) {
            if (event1.day>event2.day) {
                return true;
            } if (event1.day==event2.day) {
                if (event1.type==1) {
                    return true;
                }
            }
        }
    }
    return false;
}
bool operator < (event event1,event event2) {
    if (event1.year<event2.year) {
        return true;
    } else if (event1.year==event2.year) {
        if (event1.month<event2.month) {
            return true;
        }
        else if (event1.month==event2.month) {
            if (event1.day<event2.day) {
                return true;
            } if (event1.day==event2.day) {
                if (event1.type==0) {
                    return true;
                }
            }
        }
    }
    return false;
}
bool operator == (event event1,event event2) {
    if (event1.year==event2.year && event1.month==event2.month && event1.day==event2.day) {
        return true;
    }
    return false;
}
bool operator != (event event1,event event2) {
    return !(event1==event2);
}
struct Heap {
    int size;
    event* buf;
    Heap (event* arr,int n) {
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
        int ans(0);
        int t(0);
        for (int i(1);i<size;++i) {
            if (buf[i].type==0) {
                t+=1;
            } else {
                t-=1;
            }
            if (t>ans) {
                ans=t;
            }
        }
        if (ans<=1) {
            return 1;
        } else return ans;
    }
    
};
int main() {
    int n,count(0);
    event mature;
    event born;
    event death;
    event old;
    born.type=mature.type=0;
    death.type=old.type=1;
    cin>>n;
    event arr[2*n+1];
    for (int i(0);i<n;++i) {
        cin>>born.day>>born.month>>born.year;
        cin>>death.day>>death.month>>death.year;
        mature=born;
        mature.year+=18;
        old=born;
        old.year+=80;
        old.day-=1;
        death.day-=1;
        old.type=1;
        if (death<old) {
            old=death;
        }
        if (!(death<mature || death==mature)) {
            arr[count*2+1]=mature;
            arr[count*2+2]=old;
            count+=1;
        }
    }
    Heap heap (arr,count*2);
    heap.sort();
    //heap.debAg();
    cout<<heap.ans()<<endl;
}
/* 3
 2  5  1980  13  11  2055 1  1  1982  1  1  2030 2  1  1920  2  1  2000
 */










