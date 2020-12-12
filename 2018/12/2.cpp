#include <bits/stdc++.h>
using namespace std;

#define dbg_var(x) cout << #x << ": " << x << "\n";

unordered_map<string, char> m;
typedef long long ll;

ll calcola(string s, ll first){
    ll res = 0;
    for(ll i=0; i<s.size(); i++) if(s[i] == '#') res += i - first;
    return res;
}

int main(){
    freopen("input/in.txt", "r", stdin);
    freopen("output/out1.txt", "w", stdout);


    string s, k, tmp; char v;
    cin >> s >> s >> s;

    s = "..." + s + "...";
    ll first = 3;

    while(cin >> k >> tmp >> v){
        m[k] = v;
    }

    set<string> occ;
    for(ll g=0; g<=150; g++){
        if(g >= 125) cout << g << ": " << calcola(s, first) << "\n";

        string actual = "";
        for(ll i=0; i<s.size(); i++){
            actual += s[i];
            if(i >= 4){
                ll middle = i-2;
                s[middle] = (m.count(actual) > 0)? m[actual] : '.';
                actual = actual.substr(1,4);
            }
        }
        for(ll k=s.size()-4; k<s.size(); k++) if(s[k] != '.') s += '.';
        for(ll k=0; k<4; k++) if(s[k] != '.'){ s = '.' + s; first++; }

    }

    /*ll res = 0;
    for(ll i=0; i<s.size(); i++) if(s[i] == '#') res += i - first;

    cout << "res: " << res << "\n";
    return 0;*/
}
