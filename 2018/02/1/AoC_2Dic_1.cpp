#include <bits/stdc++.h>
using namespace std;

string str[500];

pair<bool, bool> conta(string s){
    pair<bool, bool> r = {false, false};
    int occ[50], cont2 = 0, cont3 = 0;
    fill(occ, occ+50, 0);
    for(int i=0; i<s.size(); i++){
        int c = ++occ[s[i] - 'a'];
        if(c == 2) cont2++;
        else if(c == 3){ cont2--; cont3++; }
        else if(c > 3) cont3--;
    }
    //cout << s << " " << cont2 << " " << cont3 << "\n";
    if(cont2) r.first = true;
    if(cont3) r.second = true;
    return r;
}

int main(){
    freopen("input.txt", "r", stdin);

    string s; int i = 0;
    while(cin >> s) str[i++] = s;

    int cont2 = 0, cont3 = 0;
    for(int j=0; j<i; j++){
        pair<bool, bool> r = conta(str[j]);
        if(r.first) cont2++;
        if(r.second) cont3++;
    }
    cout << cont2*cont3;
    return 0;
}
