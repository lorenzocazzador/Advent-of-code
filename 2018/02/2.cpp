#include <bits/stdc++.h>
using namespace std;

string str[500];

typedef pair<int, string> pis;
#define F first
#define S second

pis diff(string s1, string s2){
    pis r = { 0 , "" };
    for(int i=0; i<(int)s1.size(); i++){
        if(s1[i] != s2[i]) r.F++;
        else r.S += s1[i];
    }
    //cout << s1 << " " << s2 << " " << r.F << " " << r.S << "\n";
    return r;
}

int main(){
    freopen("input/in.txt", "r", stdin);
    freopen("output/out2.txt", "w", stdout);

    string s; int i = 0;
    while(cin >> s) str[i++] = s;

    sort(str, str+i);

    pis best = { INT_MAX, "" };
    for(int j=0; j<i-1; j++){
        pis r = diff(str[j], str[j+1]);
        if(best.F > r.F) best = r;
    }
    cout << best.S;
    return 0;
}
