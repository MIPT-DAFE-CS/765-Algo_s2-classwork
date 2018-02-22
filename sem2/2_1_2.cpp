#include <iostream>

using namespace std;

struct conteiner {
    int x,y;
    conteiner() {
        x=y=0;
    }
    void ps (int x1, int y1) {
        x=x1;
        y=y1;
    }
    
    
};
int main () {
    int n,x,y;
    cin>>n;
    conteiner ans[n];
    cin>>x>>y;
    ans[0].ps(x,y);
    for (int i(1);i<n;++i) {
        cin>>x>>y;
        ans[i].ps(x,y);
        conteiner tmp=ans[i];
        int j=i-1;
        
        while (( (tmp.x<ans[j].x) || ( (tmp.x==ans[j].x) && (tmp.y<ans[j].y) )) && (j>=0)) {
            ans[j+1]=ans[j];
            j--;
        }
        ans[j+1]=tmp;
    }
    for (int i(0);i<n;++i) {
        cout<<ans[i].x<<" "<<ans[i].y<<endl;
    }
    
}




