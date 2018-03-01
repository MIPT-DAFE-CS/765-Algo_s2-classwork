#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector <long long int> mass;
    vector <long long int> power;
    long long m,p;
    while (cin) {
        cin >> m >> p;
        mass.push_back(m);
        power.push_back(p);
    }
    sort (mass.begin(),mass.end());
    sort (power.begin(),power.end());
    long long currmass=mass[0];
    int currh=1;
    for (int i(1);i<mass.size();++i) {
        if (power[i]>=currmass) {
            currmass+=mass[i];
            currh++;
        }
    }
    cout << currh << endl;
}
